//
// Created by ssolaric on 19/12/18.
//

#ifndef RAYTRACING_IN_A_WEEKEND_SPHERE_H
#define RAYTRACING_IN_A_WEEKEND_SPHERE_H

#include <cmath>
#include "hitable.h"

class sphere: public hitable {
public:
    sphere() = default;
    sphere(vec3 cen, float r): center(cen), radius(r) {};

    bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;

    vec3 center;
    float radius;
};

bool sphere::hit(const ray &r, float tmin, float tmax, hit_record &rec) const {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0) {
        float temp = (-b - std::sqrt(b*b - a*c)) / a;
        if (temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + std::sqrt(b*b - a*c)) / a;
        if (temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}


#endif //RAYTRACING_IN_A_WEEKEND_SPHERE_H
