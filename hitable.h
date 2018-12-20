//
// Created by ssolaric on 19/12/18.
//

#ifndef RAYTRACING_IN_A_WEEKEND_HITABLE_H
#define RAYTRACING_IN_A_WEEKEND_HITABLE_H

#include "vec3.h"
#include "ray.h"
#include "material.h"

struct hit_record {
    float t{};
    vec3 p;
    vec3 normal;
    material* mat_ptr;
};

class hitable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};


#endif //RAYTRACING_IN_A_WEEKEND_HITABLE_H
