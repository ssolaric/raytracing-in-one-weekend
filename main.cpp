#include <iostream>
#include <cmath>
#include "vec3.h"
#include "ray.h"

// Devuelve el primer punto en donde el rayo choca a la esdera, -1.0f si no la choca.
float hit_sphere(const vec3& center, float radius, const ray& r) {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0f * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0f;
    }
    else {
        return (-b - std::sqrt(discriminant)) / (2.0f * a);
    }
}

// Para visualizar las normales, se mapea cada componente  al intervalo [0, 1] (normalizar) y luego
// se mapea (x, y, z) a (r, g, b).
vec3 color(const ray& r) {
    float t = hit_sphere(vec3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
        return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5f * (unit_direction.y() + 1.0f);
    // Interpolación de colores
    return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    // Estos vectores no necesitan ser unitarios.
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    // El origen es la esquina inferior izquierda de la pantalla.
    vec3 origin(0.0, 0.0, 0.0);

    // Estos for recorren la imagen de tal forma que los ejes coordenados X e Y empiezan en la esquina
    // inferior derecha y apuntan hacia la derecha y hacia arriba, respectivamente.
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}