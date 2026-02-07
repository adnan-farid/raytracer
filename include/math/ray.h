#ifndef ray_h
#define ray_h

#include "math/vec3.h"

class Ray {
public:
    Ray () {};
    Ray (const vec3& origin, const vec3& direction) : orig(origin), dir(direction) {}; // Ray = A + tb
    vec3 at(double t) const {
        return orig + dir * t;
    }

    const vec3& direction() const {
        return dir;
    }

    const vec3& origin() const {
        return orig;
    }

private:
    vec3 orig;
    vec3 dir;
};


#endif