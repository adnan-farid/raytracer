#ifndef bvh_h
#define bvh_h

#include "render/hittable.h"
#include "math/aabb.h"
#include "render/hittable_list.h"
#include <algorithm>

class BVH_Node : public Hittable {
public:
    BVH_Node(Hittable_List hl) : BVH_Node(hl.objects, 0, hl.objects.size()) {}; // dont pass hl by reference because we dont want to modify the original list, we only sort during the construction of BVH and destroy the copied list

    BVH_Node(std::vector<shared_ptr<Hittable>>& objects, size_t start, size_t end) {
        int axis = random_int(0, 2);

        auto comparator = box_z_compare; // use auto because comparator is a function
        if (axis == 0) { comparator = box_x_compare; }
        else if (axis == 1) { comparator = box_y_compare; } 

        size_t object_span = end - start;
        if (object_span == 1) { // length 1
           left = right = objects[start];
        } else if (object_span == 2) { // length 2
            left = objects[start]; 
            right = objects[start + 1];
        } else { // length greater than 3
            std::sort(std::begin(objects) + start, std::begin(objects) + end, comparator); // pass in the comparator function
            size_t mid = start + object_span / 2;

            left = make_shared<BVH_Node>(objects, start, mid);
            right = make_shared<BVH_Node>(objects, mid, end); // split into two subtrees
        }
        bbox = AABB(left->bounding_box(), right->bounding_box());
    }

     bool hit(const Ray& r, Interval t, hit_record& rec) const override {
        if (!bbox.hit(r, t)) { return false; } 
        
        bool hit_left = left->hit(r,t,rec);
        bool hit_right = right->hit(r, Interval(t.min, hit_left ? rec.t : t.max), rec);

        return hit_left || hit_right;
    }

    AABB bounding_box() const override { return bbox; }


private:
    shared_ptr<Hittable> left;
    shared_ptr<Hittable> right;
    AABB bbox;

    static bool box_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable>b, int axis_index) {
        Interval a_axis_interval = a->bounding_box().axis_interval(axis_index);
        Interval b_axis_interval = b->bounding_box().axis_interval(axis_index);
        return a_axis_interval.min < b_axis_interval.min;
    }

    static bool box_x_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable>b) {
        return box_compare(a,b,0);
    }
    
    static bool box_y_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable>b) {
        return box_compare(a,b,1);
    }

    static bool box_z_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable>b) {
        return box_compare(a,b,2);
    }
};




#endif 