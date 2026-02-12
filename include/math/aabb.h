#ifndef AABB_h
#define AABB_h

struct AABB {
    Interval x, y, z; // bounding box 3d

    AABB() {};

    AABB(const Interval& x, const Interval& y, const Interval& z) : x(x), y(y), z(z) {};

    AABB(const vec3& a, const vec3& b) {
        x = (a[0] <= b[0]) ? Interval(a[0], b[0]) : Interval(b[0], a[0]);
        y = (a[1] <= b[1]) ? Interval(a[1], b[1]) : Interval(b[1], a[1]);
        z = (a[2] <= b[2]) ? Interval(a[2], b[2]) : Interval(b[2], a[2]);
    }

    AABB(const AABB& a, const AABB& b) {
        x = Interval(a.x, b.x);
        y = Interval(a.y, b.y);
        z = Interval(a.z, b.z);
    }

    const Interval& axis_interval(int n) const {
        if (n == 1) {
            return z;
        } 

        if (n == 2) {
            return y;
        }

        return x;
    }

    bool hit(const Ray& r, Interval t) const {
        const vec3& ray_origin = r.origin();
        const vec3& ray_direction = r.direction();

        for (int axis = 0; axis < 3; axis++) {
            const Interval& ax = axis_interval(axis);
            const double adinv = 1.0 / ray_direction[axis];

            double t0 = (ax.min - ray_origin[axis]) * adinv;
            double t1 = (ax.max - ray_origin[axis]) * adinv;
            
            if (t0 < t1) {
                if (t0 > t.min) { t.min = t0; }
                if (t1 < t.max) { t.max = t1; }
            } else {
                if (t1 > t.min) { t.min = t1; }
                if (t0 < t.max) { t.max = t0; }
            }

            if (t.max <= t.min) { return false; }
        }
        return true;
    }


};




#endif 