//
// Created by ssolaric on 19/12/18.
//

#ifndef RAYTRACING_IN_A_WEEKEND_MATERIAL_H
#define RAYTRACING_IN_A_WEEKEND_MATERIAL_H


#include "ray.h"
#include "hitable.h"

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};


#endif //RAYTRACING_IN_A_WEEKEND_MATERIAL_H
