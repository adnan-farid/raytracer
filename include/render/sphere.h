#ifndef sphere_h
#define sphere_h

#include "render/hittable.h"


class Sphere : public Hittable{
public:
    Sphere() {};
    Sphere(vec3 center, double radius, shared_ptr<Material> mat) : center(center), radius(std::fmax(0, radius)), mat(mat) {
        vec3 rvec = vec3(radius, radius, radius);
        bbox = AABB(center - rvec, center + rvec);
    }
    const vec3& get_center() const {
        return center;
    }

    bool hit(const Ray& r, Interval t, hit_record& rec) const override {
        vec3 oc = r.origin() - center;
        vec3 ray_direction = r.direction();
        double a = ray_direction.length_squared();
        double h = dot(r.direction(), oc);
        double c = oc.length_squared() - radius*radius;
        double discriminant = h*h - a*c;

        if (discriminant < 0) {
            return false;
        }

        double sqrt_d = std::sqrt(discriminant);

        double root = (-h - sqrt_d) / a;
        
        // find the nearest root within range
        if (!t.surrounds(root)) {
            root = (-h + sqrt_d) / a;
            if (!t.surrounds(root)) {
                return false;
            }
        };
        
        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;

        return true;
    }

    AABB bounding_box() const override { return bbox; }
    
private:
    vec3 center;
    double radius;
    shared_ptr<Material> mat;
    AABB bbox; 
};


#endif sphere_h