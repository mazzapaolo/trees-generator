#include "yocto-gl/yocto/yocto_gl.h"

using namespace ygl;
using namespace std;

void generate_attraction_points(int n, vector<vec3f> pos, vector<vec3f>* points) {
    auto ps = n/(pos.size()/2) +1;
    int i = 0;
    init_rng(time(NULL));
    rng_pcg32 rang;
    seed_rng(rang, time(NULL));
    int j = 0;

    while (i < pos.size()/2  and points->size() <= n) {
        auto f1 = next_rand1i(rang, pos.size());
        auto f2 = next_rand1i(rang, pos.size());
        while(j < ps and points->size() < n) {
            auto f3 = next_rand1f(rang, ygl::min(pos.at(f1).x, pos.at(f2).x), ygl::max(pos.at(f1).x, pos.at(f2).x));
            auto f4 = next_rand1f(rang, ygl::min(pos.at(f1).y, pos.at(f2).y), ygl::max(pos.at(f1).y, pos.at(f2).y));
            auto f5 = next_rand1f(rang, ygl::min(pos.at(f1).z, pos.at(f2).z), ygl::max(pos.at(f1).z, pos.at(f2).z));
            points->push_back(vec3f{f3,f4,f5});
            j++;
        }
        i++;
        j = 0;
    }
}

float build_branch_rec(float n, int c, float r, vector<vec3f>* nodes, scene* scn, vector<vector<int>>* children,
                        vector<int>* parent, vector<vec3f>* norm) {
    float ray = 0.0f;
    for (auto i = 0; i < children->at(c).size(); i++) {
        ray += pow(build_branch_rec(n, children->at(c).at(i), r, nodes, scn, children, parent, norm),n);
    }

    if (ray == 0.0f) { ray = r; }
    else { ray = pow(ray, 1.0f/n); }
    auto i = 0.0f;
    if (parent->at(c) != c) {
        auto shp_group = new shape_group;
        auto shp = new shape{to_string(c)};
        shp_group->shapes.push_back(shp);

        auto frame_child = make_frame_fromz(nodes->at(c), norm->at(c));
        auto frame_parent = make_frame_fromz(nodes->at(parent->at(c)), norm->at(c));
        float d_x = cos(i)*ray;
        float d_y = sin(i)*ray;
        auto first_point = vec3f{d_x, 0.0f, d_y};
        auto first_child = transform_point(frame_child, first_point);
        auto first_parent = transform_point(frame_parent, first_point);

        shp->pos.push_back(first_child);
        shp->pos.push_back(first_parent);
        auto second_child = vec3f{0.0f, 0.0f, 0.0f};
        auto second_parent = vec3f{0.0f, 0.0f, 0.0f};
        auto count = 0;
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
            i += 6.28f/60.0f;
        }
        shp->triangles.push_back(vec3i{0,1,count});
        shp->norm.push_back(triangle_normal(shp->pos.at(0),shp->pos.at(1),shp->pos.at(count)));
        shp->triangles.push_back(vec3i{1,count,count+1});
        shp->norm.push_back(triangle_normal(shp->pos.at(1),shp->pos.at(count),shp->pos.at(count+1)));
        auto inst = new instance();
        inst->name = to_string(c);
        inst->shp = shp_group;
        scn->instances.push_back(inst);
        scn->shapes.push_back(shp_group);
    }
    return ray;
}

void build_branches(float n, int c, float r, vector<vec3f>* nodes, scene* scn,
                    vector<vector<int>>* children, vector<int>* parent, vector<vec3f>* norm) {
    build_branch_rec(n, c, r, nodes, scn, children, parent, norm);
}

obj_mesh* load_envelope(const string &filename) {
    auto obj_envelope = load_obj(filename);
    return get_mesh(obj_envelope, *obj_envelope->objects[0], true);
}

void generate_nodes(float Di, float D, float Dk, vector<vec3f>* att_points, vector<vec3f>* nodes, vector<vector<int>>* children,
                    vector<int>* parents, vector<vec3f>* nodes_norms) {
    float min_dist;
    auto flag = true;
    float node_point_distance = -1.0f;

    while (flag) {
        printf("%lu %lu\n", nodes->size(), att_points->size());
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
        vector<int>* parents, vector<vec3f>* nodes_norms) {
    nodes->push_back(node);
    nodes_norms->push_back(norm);
    vector<int> row;
    children->push_back(row);
    parents->push_back(int(nodes->size())-1);

}

int main(int argc, char * argv []) {
    auto envelope = load_envelope("untitled.obj");
    auto obj_envelope = load_obj("untitled.obj");
    float D = 0.1f;        // distance between adjacent nodes
    auto N = 12000;          // number of attraction points
    auto Di = 8.0f*D;         // radius of influence
    auto Dk = 5.0f*D;         // kill distance

    auto att_points = new vector<vec3f>();

    generate_attraction_points(N, envelope->shapes[0].pos, att_points);
    generate_attraction_points(N, obj_envelope->objects[0]->groups[0]->verts, att_points);
    printf("att_points\n");

    auto nodes = new vector<vec3f>();
    auto nodes_norms = new vector<vec3f>();
    auto parents = new vector<int>();
    auto children = new vector<vector<int>>();

    add_base_node(vec3f{0.0f, 0.0f, 0.0f}, vec3f{0.0f,1.0f,0.0f}, nodes, children, parents, nodes_norms);
    generate_nodes(Di, D, Dk, att_points, nodes, children, parents, nodes_norms);

    printf("nodes! %lu\n\n", nodes->size());

    auto scn_out = new scene();
    auto opts_out = new save_options;
    float r = 0.004f;
    float n = 2.5f;
    build_branches(n, 0, r, nodes, scn_out, children, parents, nodes_norms);
    printf("branches\n\n");

    printf("shapes = %lu\n", scn_out->shapes.size());
    save_scene("out1.obj", scn_out, *opts_out);
    delete scn_out;

    return 0;
}
