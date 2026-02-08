#ifndef material_h
#define material_h

#include "hittable.h"


class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray&r, const hit_record& rec, vec3& attenuation, Ray& scattered) const { return false; }
};

class Lambertian : public Material {
public:    
    Lambertian(const vec3& albedo) : albedo(albedo) {};

    bool scatter(const Ray&r, const hit_record& rec, vec3& attenuation, Ray& scattered) const override {
        vec3 scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.near_zero()) { scatter_direction = rec.normal; }

        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
private:
    vec3 albedo;
};

class Metal : public Material {
public:
    Metal(const vec3& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {};

    bool scatter(const Ray&r, const hit_record& rec, vec3& attenuation, Ray& scattered) const override {
        vec3 reflected = reflect(r.direction(), rec.normal);
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
        scattered = Ray(rec.p,  reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
private:
    vec3 albedo;
    double fuzz;
};


#endif material_h