//
// Created by ssolaric on 19/12/18.
//

#ifndef RAYTRACING_IN_A_WEEKEND_LAMBERTIAN_H
#define RAYTRACING_IN_A_WEEKEND_LAMBERTIAN_H


#include "material.h"

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    }
    while (p.squared_length() >= 1.0);
    return p;
}

class lambertian: public material {
public:
    lambertian(const vec3& a): albedo(a) {}

    bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override {
        // Sobre el punto de choque entre el rayo y la esfera, se ubica una esfera imaginaria de radio 1.
        // Esta esfera tiene como centro p + N, donde N es el vector normal al punto de choque.
        // Se elige un punto S aleatorio dentro de la esfera unitaria imaginaria.

        // Se envía un rayo desde p hasta el punto S
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

    vec3 albedo;
};


#endif //RAYTRACING_IN_A_WEEKEND_LAMBERTIAN_H