#include <iostream>

#include "utils/util.h"
#include "render/sphere.h"
#include "render/hittable.h"
#include "render/hittable_list.h"
#include "render/camera.h"


int main() { 
    double aspect_ratio = 16.0 / 9.0; // ideal ratio
    int image_width = 800;
    int viewport_height = 2.0;
    double focal_length =  1.0;   
    int samples_per_pixel = 10; // anti aliasing
    int max_depth = 10; // maximum amt of bounces 



    Camera camera = Camera(aspect_ratio, image_width, viewport_height, focal_length, samples_per_pixel, max_depth);

    Hittable_List world;

    world.add(make_shared<Sphere>(vec3(0,0,-1), 0.5));
    world.add(make_shared<Sphere>(vec3(0,-100.5,-1), 100));
    
    camera.render(world);
}