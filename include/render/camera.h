#ifndef camera_h
#define camera_h

#include "render/material.h"

class Camera {
public:
    Camera() {};
    Camera(double aspect_ratio, int image_width, double viewport_height, int samples_per_pixel, int max_depth, double vfov) : aspect_ratio(aspect_ratio), image_width(image_width), viewport_height(viewport_height), samples_per_pixel(samples_per_pixel), max_depth(max_depth), vfov(vfov) {};

    void render(Hittable& obj) { 
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (int j = 0; j < image_height; j++) {
            std::clog << "\rLines left: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0,0,0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    Ray r = get_ray(i,j);
                    pixel_color += ray_color(r, obj, max_depth);
                }

                writeSinglePixel(std::cout, pixel_color * pixel_samples_scale);
            }
        }
        std::clog << "\rDone\n";
    }

    int samples_per_pixel;
    vec3 lookfrom = vec3(0,0,0);
    vec3 lookat = vec3(0,0,-1);
    vec3 vup = vec3(0,1,0); // up dir relative to camera 

private:
    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;
        focal_length = (lookfrom - lookat).length();

        double theta = degrees_to_rads(vfov);
        double h = std::tan(theta / 2); 

        viewport_height = 2 * h * focal_length;
        viewport_width = viewport_height * (double(image_width) / image_height);

        // antialiasing
        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = lookfrom;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        // viewport
        vec3 viewport_u = viewport_width * u;
        vec3 viewport_v = viewport_height * -v; // down vertical

        delta_v = viewport_v / image_height; // img is a 2d array, we need to have a 3d 'step' to move one pixel, 
        delta_u = viewport_u / image_width;

        vec3 viewport_upper_left = center - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
        upperLeftPixelCenter = viewport_upper_left + 0.5 * (delta_u + delta_v); // middle from left to right and middle from top to bottom
    }
    
    vec3 ray_color(const Ray& r, const Hittable& obj, int depth) {
        hit_record rec;
        if (depth <=0) { return color(0,0,0); }

        if (obj.hit(r, Interval(0.001, infinity), rec)) {
            Ray scattered;
            color attenuation;

            if (rec.mat->scatter(r, rec, attenuation, scattered)) {
                return attenuation * ray_color(scattered, obj, depth - 1);
            }
            vec3 dir =rec.normal + random_unit_vector(); 
            return 0.5 * ray_color(Ray(rec.p, dir), obj, depth - 1); // keep bouncing ray 
        }

        vec3 unit_direction = unit_vector(r.direction());
        double a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0,1.0,1.0) + a * color(0.5, 0.7, 1.0);
    }

    Ray get_ray(int i, int j) const {
        // construct a camera ray originating from the origin and directed at randomly sampled point around pixel location i, j
        vec3 offset = sample_square();
        vec3 sample = upperLeftPixelCenter + ((i + offset.x()) * delta_u) + ((j + offset.y()) * delta_v);

        vec3 ray_origin = center;
        vec3 ray_direction = sample - ray_origin;

        return Ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // return a point in a random square

        return vec3(random_uniform_dist_num() - 0.5, random_uniform_dist_num() - 0.5, 0); 
    }
    
    double vfov;
    double focal_length; // length of camera to viewport
    double viewport_height;
    double viewport_width;
    int image_height;
    int image_width;
    double aspect_ratio;
    double pixel_samples_scale;
    int max_depth;
    vec3 upperLeftPixelCenter;
    vec3 center;
    vec3 u; // left edge to right edge
    vec3 v; // upper edge to bottom edge
    vec3 w;
    vec3 delta_u;
    vec3 delta_v;

};

#endif