#include <iostream>
#include <cmath>
#include <cfloat>
#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    }
    while (p.squared_length() >= 1.0);
    return p;
}

// Para visualizar las normales, se mapea cada componente  al intervalo [0, 1] (normalizar) y luego
// se mapea (x, y, z) a (r, g, b).
vec3 color(const ray& r, hitable* world) {
    hit_record rec;
    if (world->hit(r, 0.001f, FLT_MAX, rec)) {
        // Sobre el punto de choque entre el rayo y la esfera, se ubica una esfera imaginaria de radio 1.
        // Esta esfera tiene como centro p + N, donde N es el vector normal al punto de choque.
        // Se elige un punto S aleatorio dentro de la esfera unitaria imaginaria.

        // Se envía un rayo desde p hasta el punto S
        vec3 target = rec.p + rec.normal + random_in_unit_sphere(); // punto S
        // Absorber 50% de la energía en cada rebote
        return 0.5 * color(ray(rec.p, target - rec.p), world); // ¡Es recursivo!
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5f * (unit_direction.y() + 1.0f);
        // Interpolación de colores
        return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    // Estos vectores no necesitan ser unitarios.
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    // El origen es la esquina inferior izquierda de la pantalla.
    vec3 origin(0.0, 0.0, 0.0);

    hitable* list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);
    hitable* world = new hitable_list(list, 2);
    camera cam;
    // Estos for recorren la imagen de tal forma que los ejes coordenados X e Y empiezan en la esquina
    // inferior derecha y apuntan hacia la derecha y hacia arriba, respectivamente.
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world);
            }
            col /= float(ns);
            // Corrección gamma 2
            col = vec3(std::sqrt(col[0]), std::sqrt(col[1]), std::sqrt(col[2]));
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}