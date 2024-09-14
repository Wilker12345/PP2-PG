#ifndef HITTABLE_H
#define HITTABLE_H

#include <rtweekend.h>
/*
Essa classe "hittable" é a classe que diz o que o raio pode bater ou não. Se a gente quer criar uma esfera que seja batível, então a gente cria uma classe esfera e
faz ela herdar as característica dessa classe "hittable"
*/


class hit_record {
  public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
  public:
    virtual ~hittable() = default;

    // virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif