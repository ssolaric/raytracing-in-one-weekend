//
// Created by ssolaric on 19/12/18.
//

#ifndef RAYTRACING_IN_A_WEEKEND_HITABLE_LIST_H
#define RAYTRACING_IN_A_WEEKEND_HITABLE_LIST_H


#include "hitable.h"

class hitable_list: public hitable {
public:
    hitable_list() = default;
    hitable_list(hitable** l, int n) {
        list = l;
        list_size = n;
    }

    bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;

    hitable** list;
    int list_size;
};

bool hitable_list::hit(const ray &r, float tmin, float tmax, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = tmax;
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(r, tmin, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}


#endif //RAYTRACING_IN_A_WEEKEND_HITABLE_LIST_H
