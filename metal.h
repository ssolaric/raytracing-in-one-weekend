//
// Created by ssolaric on 19/12/18.
//

#ifndef RAYTRACING_IN_A_WEEKEND_METAL_H
#define RAYTRACING_IN_A_WEEKEND_METAL_H


#include "material.h"

class metal: public material {
public:
    explicit metal(const vec3& a): albedo(a) {}

    bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        // Añadir fuzziness para randomizar la dirección del rayo reflejado
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }

    vec3 albedo;
    float fuzz = 0.3;
};


#endif //RAYTRACING_IN_A_WEEKEND_METAL_H
