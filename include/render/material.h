#ifndef material_h
#define material_h

#include "hittable.h"


class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray&r, const hit_record& rec, vec3& attenuation, Ray& scattered) const { return false; }
};


#endif material_h