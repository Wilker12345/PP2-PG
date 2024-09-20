#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include <math.h>


// Verifica se o raio intersectou ou não a esfera
double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = h*h - a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant)) / a;
    }
} 

point3 random_snow_position() {
    double x = random_double(-5, 5);
    double y = random_double(2, 5);  // Flocos começando acima do boneco
    double z = random_double(-3, 4);
    return point3(x, y, z);
}

int main(int argc, char* argv[]) {
    hittable_list world;
    int num_snowflakes = 100;  // Número de flocos de neve
    std::vector<point3> snow_positions;

    // Materiais
    auto material_ground = make_shared<metal>(color(1, 1, 1), 0.8); // Mundo metálico, com reflexos difusos
    auto material_lower = make_shared<metal>(color(1.0, 1.0, 1.0), 0.0);
    auto material_upper = make_shared<dielectric>(1.5);
    auto material_head = make_shared<metal>(color(1, 1, 1), 0.5);
    auto material_eye = make_shared<metal>(color(0, 0, 0), 1.0);  // Olhos pretos
    auto material_nose = make_shared<lambertian>(color(1, 0.65, 0));  // Nariz laranja
    auto material_mouth = make_shared<lambertian>(color(0, 0, 0));  // Boca preta
    auto material_buttons = make_shared<lambertian>(color(0, 0, 0));  // Botões pretos

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 300;
    cam.max_depth = 50;

    int total_frames = 90;  // Número de frames na animação

    int frame_inicial = 0;
    int frame_final = total_frames;

    if (argc == 3) {
        frame_inicial = std::atoi(argv[1]);
        frame_final = std::atoi(argv[2]);
    }

    for (int frame = frame_inicial; frame < frame_final; frame++) {
        world.clear();
        double t = double(frame) / total_frames;  // Fator de tempo

        // Movimento da câmera (girando ao redor do boneco)
        double angle = 2 * M_PI * t + M_PI/4;
        cam.lookfrom = point3(2 * cos(angle), 2, -2 + 2 * sin(angle));  // Posição da câmera
        cam.lookat = point3(0, 1, -2);  // ponto para o qual a câmera aponta

        // Movimentos do boneco
        ////////////////////////////////////////////////////////////////////////
        double mov_head= 0.2 * t;

        // Parte do meio do boneco realiza movimentos nos eixos X e Y
        double mov_upper_y = pow(t,2);
        double mov_upper_x = 0.5 * t;

        double mov_lower_x = 1.5 * t;

        // Limitar velocidade do movimento da parte inferior
        if(mov_lower_x > 4) {
            mov_lower_x = 4;
        }

        if(mov_lower_x > 4) {
            mov_lower_x = 4;
        }
        ////////////////////////////////////////////////////////////////////////

        // Corpo do boneco (esferas)
        world.add(make_shared<sphere>(point3(0.0, -100.5, -2.0), 100.0, material_ground)); //esfera que representa mundo
        world.add(make_shared<sphere>(point3( 0 - mov_lower_x, 0.0, -2.0),   0.8, material_lower)); //base do boneco
        world.add(make_shared<sphere>(point3(0 + mov_upper_x, 1.1 - mov_upper_y, -2),   0.5, material_upper)); //meio do boneco
        world.add(make_shared<sphere>(point3(0.0, 1.85 + mov_head, -2.0),   0.35, material_head));//cabeça do boneco

        // Olhos e nariz do boneco
        world.add(make_shared<sphere>(point3(-0.1, 1.90 + mov_head, -1.68), 0.05, material_eye));
        world.add(make_shared<sphere>(point3(0.1, 1.90 + mov_head, -1.68), 0.05, material_eye));
        world.add(make_shared<sphere>(point3(0.0, 1.80 + mov_head, -1.68), 0.05, material_nose));

        // Boca
        world.add(make_shared<sphere>(point3(-0.10, 1.70 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(-0.09, 1.69 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(-0.08, 1.69 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(-0.07, 1.68 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(-0.06, 1.68 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(-0.05, 1.67 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(-0.04, 1.67 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(-0.03, 1.66 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(-0.02, 1.66 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(-0.01, 1.65 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(0, 1.65 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(0.01, 1.65 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(0.02, 1.66 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(0.03, 1.66 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(0.04, 1.67 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(0.05, 1.67 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(0.06, 1.68 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(0.07, 1.68 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(0.08, 1.69 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(0.09, 1.69 + mov_head, -1.68), 0.01, material_mouth));
        world.add(make_shared<sphere>(point3(0.10, 1.70 + mov_head, -1.68), 0.01, material_mouth));

        // Botões
        world.add(make_shared<sphere>(point3(0 + mov_upper_x, 1.3 - mov_upper_y, -1.50), 0.05, material_buttons));
        world.add(make_shared<sphere>(point3(0 + mov_upper_x, 1.15 - mov_upper_y, -1.5), 0.05, material_buttons)); 
        world.add(make_shared<sphere>(point3(0 + mov_upper_x, 1.0 - mov_upper_y, -1.5), 0.05, material_buttons)); 
        world.add(make_shared<sphere>(point3(0 - mov_lower_x, 0.60, -1.38), 0.05, material_buttons));
        world.add(make_shared<sphere>(point3(0 - mov_lower_x, 0.45, -1.32), 0.05, material_buttons));


        // Gerar posições iniciais dos flocos de neve
        for (int i = 0; i < num_snowflakes; i++) {
            snow_positions.push_back(random_snow_position());
        }

        // Adicionar os flocos de neve com movimento descendente
        for (int i = 0; i < num_snowflakes; i++) {
            // Simular movimento de queda
            point3 snowflake_position = snow_positions[i];
            snowflake_position[1] -= 0.1 * t;  // Movimento de queda
            snow_positions[i] = snowflake_position;  // Atualizar posição


            // Reposicionar floco de neve se ele cair abaixo de uma certa altura
            if (snowflake_position.y() < -1.0) {
                snowflake_position = random_snow_position();
            }

            // Inserir flocos de neves de diferentes materiais
            auto choose_mat = random_double(0, 1);
            if (choose_mat < 0.3) {
                auto material_snow = make_shared<lambertian>(color(1, 1, 1));
                world.add(make_shared<sphere>(snowflake_position, 0.04, material_snow));
            }
            else if (choose_mat < 0.7) {
                auto material_snow = make_shared<metal>(color(1, 1, 1), 1.0);
                world.add(make_shared<sphere>(snowflake_position, 0.04, material_snow));
            }
           else {
                auto material_snow = make_shared<dielectric>(1.50);
                world.add(make_shared<sphere>(snowflake_position, 0.04, material_snow));
            }
        }

        // Renderizar o frame
        cam.render(world, "image" + std::to_string(frame) + ".ppm");
    }

}