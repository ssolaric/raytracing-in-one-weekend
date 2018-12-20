//
// Created by ssolaric on 19/12/18.
//

#ifndef RAYTRACING_IN_A_WEEKEND_MATERIAL_H
#define RAYTRACING_IN_A_WEEKEND_MATERIAL_H

struct hit_record;

#include "ray.h"
#include "hitable.h"

#include <cmath>


bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n * dt) - n * std::sqrt(discriminant);
        return true;
    }
    return false;
}

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    }
    while (p.squared_length() >= 1.0);
    return p;
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};


#endif //RAYTRACING_IN_A_WEEKEND_MATERIAL_H
