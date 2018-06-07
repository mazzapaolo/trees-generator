#include "yocto-gl/yocto/yocto_gl.h"
#include "yocto-gl/yocto/yocto_gl.cpp"

using namespace ygl;
using namespace std;

/// given a vector of points, generate a random distribution of n attraction points inside the convex hull of the points
/// \param n
/// \param pos
/// \param points
void generate_attraction_points(int n, vector<vec3f> pos, vector<vec3f>* points) {
    auto ps = n/(pos.size()/2) +1;
    int i = 0;
    init_rng(time(NULL));
    rng_pcg32 rang;
    seed_rng(rang, time(NULL));
    int j = 0;
    int counter = 0;
    while (i < pos.size()/2  and counter <= n) {
        auto f1 = next_rand1i(rang, pos.size());
        auto f2 = next_rand1i(rang, pos.size());
        while(j < ps and counter < n) {
            auto f3 = next_rand1f(rang, ygl::min(pos.at(f1).x, pos.at(f2).x), ygl::max(pos.at(f1).x, pos.at(f2).x));
            auto f4 = next_rand1f(rang, ygl::min(pos.at(f1).y, pos.at(f2).y), ygl::max(pos.at(f1).y, pos.at(f2).y));
            auto f5 = next_rand1f(rang, ygl::min(pos.at(f1).z, pos.at(f2).z), ygl::max(pos.at(f1).z, pos.at(f2).z));
            points->push_back(vec3f{f3,f4,f5});
            counter++;
            j++;
        }
        i++;
        j = 0;
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



float build_branch_rec(float n, int c, float r, vector<vec3f>* nodes, vector<vector<int>>* children,
                        vector<int>* parent, vector<vec3f>* norm, material* mat, shape_group* shp_group) {
    float ray = 0.0f;
    for (auto i = 0; i < children->at(c).size(); i++) {
        ray += pow(build_branch_rec(n, children->at(c).at(i), r, nodes, children, parent, norm, mat, shp_group),n);
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
    build_branch_rec(n, c, r, nodes, children, parent, norm, mat, shp_group);
}

void generate_nodes(float Di, float D, float Dk, vector<vec3f>* att_points, vector<vec3f>* nodes, vector<vector<int>>* children,
                    vector<int>* parents, vector<vec3f>* nodes_norms) {
    float min_dist;
    auto flag = true;
    float node_point_distance = -1.0f;

    while (flag) {
        flag = false;
        min_dist = -1.0f;
        int closest [att_points->size()] = {0};
        vec3f new_nodes [nodes->size()];

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

int main(int argc, char * argv []) {
    auto parser = make_parser(argc, argv, "trees-generator", "create tree");
    auto env = parse_opt<string>(parser, "--envelope", "-e", "filename of the envelope", "empty", true);
    auto N = parse_opt<int>(parser, "--points", "-p", "number of attraction points", 1000);
    auto D = parse_opt<float>(parser, "--distance", "-d", "distance between adjacent nodes", 0.06f, true);
    auto Di = parse_opt<float>(parser, "--influence", "-i", "radius of influence", 7.0f, true)*D;
    auto Dk = parse_opt<float>(parser, "--kill", "-k", "kill distance", 4.0f, true)*D;
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
        printf("%d\n", i);
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
    //delete scn_out;

    return 0;
}
