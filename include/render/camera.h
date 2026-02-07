#ifndef camera_h
#define camera_h

class Camera {
public:
    Camera() {};
    Camera(double viewport_height, double viewport_width, double image_height, double image_width ,double focal_length, vec3 center) : viewport_height(viewport_height), viewport_width(viewport_height * (double(image_width) / image_height)), image_height(image_height), image_width(image_width), focal_length(focal_length), center(center) {
        v = vec3(0, -viewport_height, 0); // negative bc we are going down
        u = vec3(viewport_width, 0, 0);
        delta_v = v / image_height; // img is a 2d array, we need to have a 3d 'step' to move one pixel, 
        delta_u = u / image_width;
    };

    void render(Hittable& obj) { 
        initialize();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rLines left: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                vec3 pixel_center = upperLeftPixelCenter + (i * delta_u) + (j * delta_v);
                vec3 ray_direction = pixel_center - center;

                Ray r = Ray(center, ray_direction);
                color pixel_color = ray_color(r, obj);
                writeSinglePixel(std::cout, pixel_color);
            }
        }
        std::clog << "\rDone\n";
    }

private:
    void initialize() {
        // viewport
        vec3 viewport_upper_left = center - vec3(0, 0, focal_length) - u / 2 - v / 2;
        vec3 upperLeftPixelCenter = viewport_upper_left + 0.5 * (delta_u + delta_v); // middle from left to right and middle from top to bottom
    }
    
    vec3 ray_color(const Ray& r, const Hittable& world) {
        hit_record rec;
        if (world.hit(r, Interval(0, infinity), rec)) {
            return 0.5 * (rec.normal + color(1,1,1));
        }

        vec3 unit_direction = unit_vector(r.direction());
        double a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0,1.0,1.0) + a * color(0.5, 0.7, 1.0);
    }
    
    double focal_length; // length of camera to viewport
    double viewport_height;
    double viewport_width;
    double image_height;
    double image_width;
    vec3 center;
    vec3 u; // left edge to right edge
    vec3 v; // upper edge to bottom edge
    vec3 delta_u;
    vec3 delta_v;

};

#endif