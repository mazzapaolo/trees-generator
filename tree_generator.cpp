#include "yocto-gl/yocto/yocto_gl.h"

using namespace ygl;

scene* init_scene() {
    auto scn = new scene();
    auto mat = new material{"floor"};
    mat->kd = {0.2f, 0.2f, 0.2f};
    scn->materials.push_back(mat);
    auto shp = new shape{"floor"};
    shp->pos = {{-10, 0, -10}, {10, 0, -10}, {10, 0, 10}, {-10, 0, 10}};
    shp->norm = {{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}};
    shp->texcoord = {{-10, -10}, {10, -10}, {10, 10}, {-10, 10}};
    shp->triangles = {{0, 1, 2}, {0, 2, 3}};
    scn->shapes.push_back(shp);
    scn->instances.push_back(new instance{"floor", identity_frame3f, shp});
    auto lshp = new shape{"light"};
    lshp->pos = {{1.4f, 8, 6}, {-1.4f, 8, 6}};
    lshp->points = {0, 1};
    scn->shapes.push_back(lshp);
    auto lmat = new material{"light"};
    lmat->ke = {100, 100, 100};
    scn->materials.push_back(lmat);
    scn->instances.push_back(
            new instance{"light", identity_frame3f, lshp});
    auto cam = new camera{"cam"};
    cam->frame = lookat_frame3f({0, 4, 10}, {0, 1, 0}, {0, 1, 0});
    cam->yfov = 15 * pif / 180.f;
    cam->aspect = 16.0f / 9.0f;
    cam->aperture = 0;
    cam->focus = length(vec3f{0, 4, 10} - vec3f{0, 1, 0});
    scn->cameras.push_back(cam);
    return scn;

}

int main(int argc, char * argv []) {
    auto scn = init_scene();
    auto opts = new save_options;
    make_sphere()
    save_scene("out.obj", scn, *opts);
    delete scn;
    return 0;
}
