#ifndef hittable_list_h
#define hittable_list_h

#include "render/hittable.h"
#include "math/aabb.h"

#include <vector>

using std::make_shared; // dont need to use std::
using std::shared_ptr;

class Hittable_List : public Hittable {
public:
    std::vector<std::shared_ptr<Hittable>> objects;

    Hittable_List() {};
    Hittable_List(std::shared_ptr<Hittable> obj) { add(obj); };

    void clear() {
        objects.clear();
    }

    void add(std::shared_ptr<Hittable> obj) {
        objects.push_back(obj);
        bbox = AABB(bbox, obj->bounding_box());
    };

    bool hit(const Ray& r, Interval t, hit_record& rec) const override {
        hit_record temp_rec;
        bool collided = false;

        double closest_intersection = t.max;

        for (const std::shared_ptr<Hittable>& obj : objects) {
            if (obj->hit(r, Interval(t.min, closest_intersection), temp_rec)) {
                collided = true;
                closest_intersection = temp_rec.t;
                rec = temp_rec;
            }
        }
        return collided;
    }

    

    AABB bounding_box() const override { return bbox; }
private:
    AABB bbox;
};



#endif