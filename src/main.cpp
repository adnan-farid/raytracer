#include <iostream>

#include "utils/util.h"
#include "render/sphere.h"
#include "render/hittable.h"
#include "render/hittable_list.h"
#include "render/camera.h"


int main() { 
    double aspect_ratio = 16.0 / 9.0; // ideal ratio
    int image_width = 400;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height; // if image height > 1: else 1

    Camera camera = Camera();

    // world

    Hittable_List world;

    world.add(make_shared<Sphere>(vec3(0,0,-1), 0.5));
    world.add(make_shared<Sphere>(vec3(0,-100.5,-1), 100));
    
}