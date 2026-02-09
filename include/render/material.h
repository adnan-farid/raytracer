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

class Dielectric : public Material {
public:
    Dielectric(double refraction_index) : refraction_index(refraction_index) {};

    bool scatter(const Ray&r, const hit_record& rec, vec3& attenuation, Ray& scattered) const override {
        attenuation = vec3(1.0,1.0,1.0);
        double refraction_index_2 = rec.front_face ? (1.0 / refraction_index) : refraction_index;

        vec3 unit_direction = unit_vector(r.direction());
        double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1 - cos_theta * cos_theta);

        bool cannot_refract = refraction_index_2 * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta, refraction_index_2) > random_uniform_dist_num()) {
            direction = reflect(unit_direction, rec.normal);
        } else {
            direction = refract(unit_direction, rec.normal, refraction_index_2);
        }   

        scattered = Ray(rec.p, direction);
        return true;
    }
private:
    double refraction_index;
    static double reflectance(double cosine, double refraction_index) {
        double r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0 * r0;
        return r0 + (1-r0) * std::pow((1-cosine), 5);
    }
};

#endif material_h