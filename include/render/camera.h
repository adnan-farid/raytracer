#ifndef camera_h
#define camera_h

class Camera {
public:
    Camera() {};
    Camera(double aspect_ratio, int image_width, double viewport_height, double focal_length) : aspect_ratio(aspect_ratio), image_width(image_width), viewport_height(viewport_height), focal_length(focal_length) {};

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
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;
        viewport_width = viewport_height * (double(image_width) / image_height);

        v = vec3(0, -viewport_height, 0); // negative bc we are going down
        u = vec3(viewport_width, 0, 0);
        delta_v = v / image_height; // img is a 2d array, we need to have a 3d 'step' to move one pixel, 
        delta_u = u / image_width;
        // viewport
        vec3 viewport_upper_left = center - vec3(0, 0, focal_length) - u / 2 - v / 2;
        upperLeftPixelCenter = viewport_upper_left + 0.5 * (delta_u + delta_v); // middle from left to right and middle from top to bottom
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
    int image_height;
    int image_width;
    double aspect_ratio;
    vec3 upperLeftPixelCenter;
    vec3 center;
    vec3 u; // left edge to right edge
    vec3 v; // upper edge to bottom edge
    vec3 delta_u;
    vec3 delta_v;

};

#endif