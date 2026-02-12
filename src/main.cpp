#include <iostream>

#include "utils/util.h"
#include "render/sphere.h"
#include "render/hittable.h"
#include "render/hittable_list.h"
#include "render/camera.h"
#include "render/material.h"
#include "math/bvh.h"

int main() { 
    double aspect_ratio = 16.0 / 9.0; // ideal ratio
    int image_width = 800;
    int viewport_height = 2.0;
    int samples_per_pixel = 10; // anti aliasing
    int max_depth = 10; // maximum amt of ray bounces 
    double vfov = 50;



    Camera camera = Camera(aspect_ratio, image_width, viewport_height, samples_per_pixel, max_depth, vfov);

    camera.lookat   = vec3(0, 0, -1);
    camera.lookfrom = vec3(0, 0,  3);
    camera.vup      = vec3(0, 1,  0);

    Hittable_List world;

    auto material_ground = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Dielectric>(1.00 / 1.33);
    auto material_right  = make_shared<Metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<Sphere>(vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(vec3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<Sphere>(vec3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<Sphere>(vec3( 1.0,    0.0, -1.0),   0.5, material_right));
    
    world = Hittable_List(make_shared<BVH_Node>(world));

    camera.render(world);
}