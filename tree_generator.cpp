#include "yocto-gl/yocto/yocto_gl.h"
#include "yocto-gl/yocto/yocto_gl.cpp"

using namespace ygl;
using namespace std;

struct tree_node {
    vec3f pos;
    vec3f norm;
    vector<tree_node *> *children;
    tree_node *parent;

    tree_node(vec3f pos, vec3f norm) {
        this->pos = pos;
        this->norm = norm;
        this->parent = this;
        children = new vector<tree_node*>();
    }

    void set_parent(tree_node* parent) {
        this->parent = parent;
    }

    void add_child(tree_node* child) {
        children->push_back(child);
    }
};

/// given a vector of points, generate a random distribution of n attraction points inside the convex hull of the points
/// \param n
/// \param pos
/// \param points
void generate_attraction_points(int n, vector<vec3f> pos, vector<vec3f>* points) {
    auto ps = n/(pos.size()/2) +1;
    init_rng(time(NULL));
    rng_pcg32 rang;
    seed_rng(rang, time(NULL));

    int counter = 0;
    for(auto i = 0; i < pos.size()/2 and counter <= n; i++) {
        auto f1 = next_rand1i(rang, pos.size());
        auto f2 = next_rand1i(rang, pos.size());
        for (auto j = 0; j < ps and counter <= n; j++) {
            auto f3 = next_rand1f(rang, ygl::min(pos.at(f1).x, pos.at(f2).x), ygl::max(pos.at(f1).x, pos.at(f2).x));
            auto f4 = next_rand1f(rang, ygl::min(pos.at(f1).y, pos.at(f2).y), ygl::max(pos.at(f1).y, pos.at(f2).y));
            auto f5 = next_rand1f(rang, ygl::min(pos.at(f1).z, pos.at(f2).z), ygl::max(pos.at(f1).z, pos.at(f2).z));
            points->push_back(vec3f{f3,f4,f5});
            counter++;
        }
    }
}

/// TO-CHECK given the set of attraction points, generates base nodes for the tree
/// \param att_points
/// \param nodes
/// \param influence
/// \param distance

void generate_base_nodes(vector<vec3f>* att_points, vector<tree_node *>* nodes, float influence, float distance) {
    auto min = -1.0f;
    auto lowest = vec3f{0.0f, 0.0f, 0.0f};

    for (auto point : *att_points) {
        if ((min == -1.0 or min <  point.y) and point.y >= 0) {
            min = point.y;
            lowest = point;
        }
    }
    auto base = new tree_node{vec3f{lowest.x, 0.0f, lowest.z}, vec3f{0.0f,1.0f,0.0f}};
    base->parent = base;
    nodes->push_back(base);
    auto base_y = 0.0f;
    while (base_y < lowest.y - influence) {
        auto new_node = new tree_node(vec3f{lowest.x, base_y+distance, lowest.z}, vec3f{0.0f,1.0f,0.0f});
        new_node->parent = nodes->back();
        nodes->push_back(new_node);
        base_y += distance;
    }
}

void add_base_node(vec3f node, vec3f norm, vector<vec3f>* nodes, vector<vector<int>>* children,
                   vector<int>* parents, vector<vec3f>* nodes_norms, vector<int>* base_nodes, int parent, int child, bool is_base) {
    nodes->push_back(node);
    nodes_norms->push_back(norm);
    vector<int> row;
    children->push_back(row);
    if (child != -1) {
        children->at(int(nodes->size())-1).push_back(child);
    }
    if (is_base) {
        base_nodes->push_back(parent);
    }
    parents->push_back(parent);
}

/// TO-FIX replacing the vectors of parameters for the nodes with a vector of tree_node
/// TO-ADD the direction of the growth can be biased by a vector representing a combined effect of branch weight and
/// tropisms
/// bulk of the space colonization algorithm, in each iteration of the outer while it adds new nodes:
///     - an attraction point may influence the tree node that is closest to it. This influence occurs if the distance
///       between the point and the closest node is less then the radius of influence Di
///     - there may be several attraction points that influence a single tree node v
///       the first inner "for" calculates for each node the set of its attraction points and sums over this set the
///       difference between the attraction point and the node, all normalized
///     - in the last inner "for", it calculates the position of the new node, using the formula
///       new_node = node + normalize(direction)*D, with D equals the distance between two adjacent nodes
///     - after a new node is added, it verifies if it is inside the kill distance of any remaining attraction point,
///       if it is, then the attraction point is removed
/// \param Di
/// \param D
/// \param Dk
/// \param att_points
/// \param nodes
/// \param children
/// \param parents
/// \param nodes_norms
void generate_nodes(float Di, float D, float Dk, vector<vec3f>* att_points,
                    vector<vec3f>* nodes, vector<vector<int>>* children, vector<int>* parents, vector<vec3f>* nodes_norms) {
    float min_dist;
    auto flag = true;
    float node_point_distance = -1.0f;

    while (flag) {
        flag = false;
        min_dist = -1.0f;
        int closest [att_points->size()] = {0};
        vec3f new_nodes [nodes->size()];

        /*
         * vector of directions for each new node of the current iteration
         */
        for (auto i = 0; i < att_points->size(); i++) {
            for (auto j = 0; j < nodes->size(); j++) {
                if (overlap_point(att_points->at(i), Di, nodes->at(j), 0.0f, node_point_distance)) {
                    if (min_dist < 0 or node_point_distance < min_dist) {
                        closest[i] = j+1;
                        min_dist = node_point_distance;
                    }
                }
            }
            if (closest[i] > 0) {
                new_nodes[closest[i]-1] += normalize(att_points->at(i) - nodes->at(closest[i]-1));
            }
        }

        /*
         * for each node generates a new node, if any, and removes the attraction points
         */

        auto len_nodes_old = nodes->size();
        int n = 0;
        for (auto i = 0; i< len_nodes_old; i++) {
            auto novo = nodes->at(i) + D*normalize(new_nodes[i]);
            if (new_nodes[i] != vec3f{0.0f, 0.0f, 0.0f} and find(nodes->begin(), nodes->end(), novo) == nodes->end()) {
                flag = true;
                parents->push_back(i);
                vector<int> row;
                children->push_back(row);
                nodes->push_back(novo);
                nodes_norms->push_back(normalize(new_nodes[i]));
                children->at(i).push_back(int(nodes->size())-1);

                while (n < att_points->size()) {
                    if (overlap_point(att_points->at(n), 0.0f, novo, Dk, node_point_distance)) {
                        att_points->erase(att_points->begin()+n);
                        n--;
                    }
                    n++;
                }
                n = 0;
            }
        }
    }
}

material* make_material(const std::string& name, const vec3f& kd,
                        const std::string& kd_txt, const vec3f& ks = {0.04f, 0.04f, 0.04f},
                        float rs = 0.01f) {
    auto* mt = new material;
    mt->name = name;
    mt->kd = kd;
    mt->ks = ks;
    mt->rs = rs;
    mt->kd_txt =  new texture;
    mt->kd_txt->path = kd_txt;
    return mt;
}

///
/// \param c
/// \param node
/// \param r
/// \param mat
/// \param shp_group

void refine_branch_fork(int c, vec3f node, float r, material* mat, shape_group* shp_group) {

    auto shp = new shape{to_string(c+20000)};
    shp_group->shapes.push_back(shp);
    auto usteps = 32;
    auto vsteps = 16;
    for(auto m = 0; m < vsteps; m++) {
        for (auto n = 0; n < usteps; n++) {
            int i = (usteps+1)*m + n;
            int j = i+usteps+1;
            shp->quads.push_back(vec4i{i,i+1,j+1, j});
        }
    }
    for (auto i = 0; i <= vsteps; i++) {
        for (auto j = 0; j <= usteps; j++) {
            auto u = j/float(usteps);
            auto v = i/float(vsteps);
            shp->texcoord.push_back(vec2f{u,v});
        }
    }
    auto frame = make_frame_fromz(node, vec3f{0.0f,1.0f,0.0f});

    for (auto uv : shp->texcoord) {
        auto uu = float(2*M_PI*uv.x);
        auto vv = float(M_PI*(1-uv.y));
        auto point = transform_point(frame, vec3f{r*sin(vv)*cos(uu), r*sin(vv)*sin(uu), r*cos(vv)});
        shp->pos.push_back(point);
    }
    compute_normals(shp);
    shp->mat = mat;
}

///
/// \param n
/// \param c
/// \param r
/// \param nodes
/// \param children
/// \param parent
/// \param norm
/// \param mat
/// \param shp_group
/// \return

float build_branch(float n, int c, float r, vector<vec3f> *nodes, vector<vector<int>> *children,
                   vector<int> *parent, vector<vec3f> *norm, material *mat, shape_group *shp_group) {
    float ray = 0.0f;
    for (auto i = 0; i < children->at(c).size(); i++) {
        ray += pow(build_branch(n, children->at(c).at(i), r, nodes, children, parent, norm, mat, shp_group),n);
    }

    if (ray == 0.0f) { ray = r; }
    else { ray = pow(ray, 1.0f/n); }
    auto i = 0.0f;
    if (parent->at(c) != c) {
        refine_branch_fork(c, nodes->at(c), ray, mat, shp_group);
        auto shp = new shape{to_string(c)};
        shp_group->shapes.push_back(shp);

        auto frame_child = make_frame_fromz(nodes->at(c), norm->at(c));
        auto frame_parent = make_frame_fromz(nodes->at(parent->at(c)), norm->at(c));
        float d_x = cos(i)*ray;
        float d_y = sin(i)*ray;

        auto first_point = vec3f{d_x, d_y, 0.0f};
        auto first_child = transform_point(frame_child, first_point);
        auto first_parent = transform_point(frame_parent, first_point);

        shp->pos.push_back(first_child);
        shp->pos.push_back(first_parent);
        auto second_child = vec3f{0.0f, 0.0f, 0.0f};
        auto second_parent = vec3f{0.0f, 0.0f, 0.0f};
        auto count = 0;
        i = 6.28f/360.0f;
        while (i < 6.28f) {
            auto c_x = cos(i)*ray;
            auto c_y = sin(i)*ray;
            auto point = vec3f{c_x, c_y, 0.0f};
            second_child = transform_point(frame_child, point);
            second_parent = transform_point(frame_parent, point);
            shp->pos.push_back(second_child);
            shp->pos.push_back(second_parent);
            shp->triangles.push_back(vec3i{count, count+1, count+2});
            shp->norm.push_back(triangle_normal(shp->pos.at(count),shp->pos.at(count+1),shp->pos.at(count+2)));
            shp->triangles.push_back(vec3i{count+1, count+2, count+3});
            shp->norm.push_back(triangle_normal(shp->pos.at(count+1),shp->pos.at(count+2),shp->pos.at(count+3)));
            count += 2;
            i += 6.28f/360.0f;
        }
        shp->triangles.push_back(vec3i{0,1,count});
        shp->norm.push_back(triangle_normal(shp->pos.at(0),shp->pos.at(1),shp->pos.at(count)));
        shp->triangles.push_back(vec3i{1,count,count+1});
        shp->norm.push_back(triangle_normal(shp->pos.at(1),shp->pos.at(count),shp->pos.at(count+1)));
        shp->mat = mat;
    }
    return ray;
}

void build_branches(float n, int c, float r, vector<vec3f>* nodes,
                    vector<vector<int>>* children, vector<int>* parent, vector<vec3f>* norm, material* mat, shape_group* shp_group) {
    build_branch(n, c, r, nodes, children, parent, norm, mat, shp_group);
}


int main(int argc, char * argv []) {
    auto parser = make_parser(argc, argv, "trees-generator", "create tree");
    auto env = parse_opt<string>(parser, "--envelope", "-e", "filename of the envelope", "empty", true);
    auto N = parse_opt<int>(parser, "--points", "-p", "number of attraction points", 1000);
    auto D = parse_opt<float>(parser, "--distance", "-d", "distance between adjacent nodes", 0.05f, true);
    auto Di = parse_opt<float>(parser, "--influence", "-i", "radius of influence", 7.0f, true)*D;
    auto Dk = parse_opt<float>(parser, "--kill", "-k", "kill distance", 2.0f, true)*D;
    auto output = parse_opt<string>(parser, "--output", "-o", "output filename", "out.obj", true);

    auto opts_in = new load_options;
    auto envelope = load_obj_scene(env, *opts_in);

    auto att_points = new vector<vec3f>();

    for(auto* env_shp : envelope->shapes) {
        generate_attraction_points(N, env_shp->shapes[0]->pos, att_points);
    }


    auto nodes = new vector<vec3f>();
    auto nodes_norms = new vector<vec3f>();
    auto parents = new vector<int>();
    auto base_nodes = new vector<int>();
    auto children = new vector<vector<int>>();

    add_base_node(vec3f{0.0f, 0.0f, 0.0f}, vec3f{0.0f,1.0f,0.0f}, nodes, children, parents, nodes_norms, base_nodes, 0, 1, true);
    add_base_node(vec3f{0.0f, 0.1f, 0.0f}, vec3f{0.0f,1.0f,0.0f}, nodes, children, parents, nodes_norms, base_nodes, 0, -1, false);

    generate_nodes(Di, D, Dk, att_points, nodes, children, parents, nodes_norms);

    printf("nodes = %lu\n", nodes->size());

    float r = 0.004f;
    float n = 2.5f;

    auto scn_out = new scene();

    auto bark = make_material("bark", vec3f{1, 1, 1}, "bark.jpg");
    scn_out->textures.push_back(bark->kd_txt);
    scn_out->materials.push_back(bark);

    for (auto i : *base_nodes) {
        auto shp_group = new shape_group;
        build_branches(n, i, r, nodes, children, parents, nodes_norms, bark, shp_group);
        auto* inst = new instance;
        inst->name = to_string(20000+i);
        inst->shp = shp_group;
        inst->frame = make_frame_fromz(vec3f{-1.25f, 1, 0}, vec3f{0, 0, 1});
        scn_out->instances.push_back(inst);
        scn_out->shapes.push_back(shp_group);
    }

    auto opts_out = new save_options;
    save_scene(output, scn_out, *opts_out);
    return 0;
}
