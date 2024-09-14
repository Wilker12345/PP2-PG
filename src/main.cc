/*
Para rodar o projeto, tive que instalar o CMake, colocar o caminho do compilador dos compiladores nas variáveis de ambiente,

depois criei o arquivo CMakeLists.txt, escrevi cmake_minimum_required(VERSION 3.30.3) para dizer qual versão minima do cmake deveria rodar,

project(projeto_pratico2) para dizer qual o nome do meu projeto e por fim adicionei add_executable(projeto_pratico2 pp2.cpp).

Depois rodei os comandos cmake -B build -G "MingW Makefiles" para rodar os códigos do cmake usando o gerador de makefile do MingW

Rodei o comando cmake --build build

Por fim, executei o arquivo pp2.exe e mandei ele para a saida imagem.ppm com o comando ".\pp2.exe > image.ppm"

Deu errado, comecei a rodar com cmake -B build e cmake --build build

Também fiz .\build\projeto_pratico2.exe > image.ppm
*/ 


#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"



//verifica se o raio intersectou ou não a esfera
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

// color ray_color(const ray& r, const hittable& world) {
//     hit_record rec;
//     if (world.hit(r, interval(0, infinity), rec)) {
//         return 0.5 * (rec.normal + color(1,1,1));
//     }

//     vec3 unit_direction = unit_vector(r.direction());
//     auto a = 0.5*(unit_direction.y() + 1.0);
//     return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
// }

int main() {
    hittable_list world;

    // auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    // auto material_head = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    // // auto material_upperBody   = make_shared<dielectric>(1.50);
    // auto material_lowerBody = make_shared<dielectric>(1.00 / 1.50);
    // auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);



    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.8));
    auto material_center = make_shared<lambertian>(color(1, 1, 1));
    auto material_top = make_shared<lambertian>(color(1, 1, 1));
    auto material_head = make_shared<metal>(color(1, 1, 1), 1.0);
    auto material_eye = make_shared<metal>(color(0, 0, 0), 1.0);
    auto material_nose = make_shared<lambertian>(color(1, 0.45, 0));
    auto material_mouth = make_shared<lambertian>(color(0, 0, 0));

    auto material_buttons = make_shared<lambertian>(color(0, 0, 0));

    auto material_shoulder = make_shared<metal>(color(1, 1, 1), 0.0);
    auto material_biceps = make_shared<dielectric>(1.50);
    auto material_arm = make_shared<lambertian>(color(1, 1, 1));


    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    cam.vfov = 90;

    ///////////////////////////////////////////////////////////////////////////////////////
    // IMAGEM 1


    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 98.0, material_ground)); //faz a bola do chão. O mundo
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.8, material_center)); //faz a bola do meio.
    world.add(make_shared<sphere>(point3(0.0,    1.1, -1.0),   0.5, material_top));
    world.add(make_shared<sphere>(point3(0.0,    1.95, -1.0),   0.35, material_head));

    world.add(make_shared<sphere>(point3(-0.1, 1.8, -0.5), 0.05, material_eye));
    world.add(make_shared<sphere>(point3(0.1, 1.8, -0.5), 0.05, material_eye));
    world.add(make_shared<sphere>(point3(0.0, 1.7, -0.5), 0.03, material_nose));
    
    world.add(make_shared<sphere>(point3(-0.10, 1.60, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.09, 1.59, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.08, 1.59, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.07, 1.58, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.06, 1.58, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.05, 1.57, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.04, 1.57, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.03, 1.56, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.02, 1.56, -0.5), 0.01, material_mouth));
    
    world.add(make_shared<sphere>(point3(-0.01, 1.55, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0, 1.55, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.01, 1.55, -0.5), 0.01, material_mouth));

    world.add(make_shared<sphere>(point3(0.02, 1.56, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.03, 1.56, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.04, 1.57, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.05, 1.57, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.06, 1.58, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.07, 1.58, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.08, 1.59, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.09, 1.59, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.10, 1.60, -0.5), 0.01, material_mouth));




    world.add(make_shared<sphere>(point3(0.0, 1.3, -0.5), 0.03, material_buttons));
    world.add(make_shared<sphere>(point3(0.0, 1.15, -0.5), 0.03, material_buttons));
    world.add(make_shared<sphere>(point3(0.0, 1, -0.5), 0.03, material_buttons));

    world.add(make_shared<sphere>(point3(-0.55, 1.4, -1.0), 0.15, material_shoulder));
    world.add(make_shared<sphere>(point3(0.55, 1.4, -1.0), 0.15, material_shoulder));

    world.add(make_shared<sphere>(point3(-0.75, 1.3, -1.0), 0.10, material_biceps));
    world.add(make_shared<sphere>(point3(0.75, 1.3, -1.0), 0.10, material_biceps));

    world.add(make_shared<sphere>(point3(-0.88, 1.25, -1.0), 0.08, material_arm));
    world.add(make_shared<sphere>(point3(0.88, 1.25, -1.0), 0.08, material_arm));

    

    // cam.focus_dist = 10;

    cam.lookfrom = point3(0,1,1.18);
    cam.lookat   = point3(0,1,-1);
    cam.vup      = vec3(0,1,0);
    // cam.vfov     = 90;
    // cam.lookfrom = point3(-2,2,1);
    // cam.lookat   = point3(0,0,-1);
    // cam.vup      = vec3(0,1,0);

    cam.render(world, "image1.ppm");


    ///////////////////////////////////////////////////////////////////////////////////////

     world.clear();
    // IMAGEM 2

   


    // world.add(make_shared<sphere>(point3( 2, -100.5, -1.0), 98.0, material_ground)); //faz a bola do chão. O mundo
    // world.add(make_shared<sphere>(point3( 2,    0.0, -1.0),   0.8, material_center)); //faz a bola do meio.
    // world.add(make_shared<sphere>(point3(2,    1.1, -1.0),   0.5, material_top));
    // world.add(make_shared<sphere>(point3(2,    1.8, -1.0),   0.25, material_head));

    // world.add(make_shared<sphere>(point3(1.5, 1.7, -0.5), 0.05, material_eye));
    // world.add(make_shared<sphere>(point3(1.7, 1.7, -0.5), 0.05, material_eye));

    // world.add(make_shared<sphere>(point3(2, 1.5, -0.5), 0.05, material_nose));



    // world.add(make_shared<sphere>(point3(1.45, 1.4, -1.0), 0.15, material_shoulder));
    // world.add(make_shared<sphere>(point3(2.55, 1.4, -1.0), 0.15, material_shoulder));

    // world.add(make_shared<sphere>(point3(1.25, 1.5, -1.0), 0.10, material_biceps));
    // world.add(make_shared<sphere>(point3(2.75, 1.5, -1.0), 0.10, material_biceps));

    // world.add(make_shared<sphere>(point3(1.12, 1.55, -1.0), 0.08, material_arm));
    // world.add(make_shared<sphere>(point3(2.88, 1.55, -1.0), 0.08, material_arm));

    int translacao = 2;

    world.add(make_shared<sphere>(point3(translacao + 0.0, -100.5, -1.0), 98.0, material_ground)); //faz a bola do chão. O mundo
    world.add(make_shared<sphere>(point3(translacao + 0.0,    0.0, -1.0),   0.8, material_center)); //faz a bola do meio.
    world.add(make_shared<sphere>(point3(translacao + 0.0,    1.1, -1.0),   0.5, material_top));
    world.add(make_shared<sphere>(point3(translacao + 0.0,    1.9, -1.0),   0.35, material_head));

    world.add(make_shared<sphere>(point3(translacao + -0.1, 1.8, -0.5), 0.05, material_eye));
    world.add(make_shared<sphere>(point3(translacao + 0.1, 1.8, -0.5), 0.05, material_eye));
    world.add(make_shared<sphere>(point3(translacao + 0.0, 1.7, -0.5), 0.03, material_nose));
    
    world.add(make_shared<sphere>(point3(translacao + -0.10, 1.60, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + -0.09, 1.59, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + -0.08, 1.59, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + -0.07, 1.58, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + -0.06, 1.58, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + -0.05, 1.57, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + -0.04, 1.57, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + -0.03, 1.56, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + -0.02, 1.56, -0.5), 0.01, material_mouth));
    
    world.add(make_shared<sphere>(point3(translacao + -0.01, 1.55, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + 0, 1.55, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + 0.01, 1.55, -0.5), 0.01, material_mouth));

    world.add(make_shared<sphere>(point3(translacao + 0.02, 1.56, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + 0.03, 1.56, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + 0.04, 1.57, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + 0.05, 1.57, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + 0.06, 1.58, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + 0.07, 1.58, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + 0.08, 1.59, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + 0.09, 1.59, -0.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(translacao + 0.10, 1.60, -0.5), 0.01, material_mouth));




    world.add(make_shared<sphere>(point3(translacao + 0.0, 1.3, -0.5), 0.03, material_buttons));
    world.add(make_shared<sphere>(point3(translacao + 0.0, 1.15, -0.5), 0.03, material_buttons));
    world.add(make_shared<sphere>(point3(translacao + 0.0, 1, -0.5), 0.03, material_buttons));

    world.add(make_shared<sphere>(point3(translacao + -0.55, 1.4, -1.0), 0.15, material_shoulder));
    world.add(make_shared<sphere>(point3(translacao + 0.55, 1.4, -1.0), 0.15, material_shoulder));

    world.add(make_shared<sphere>(point3(translacao + -0.75, 1.3, -1.0), 0.10, material_biceps));
    world.add(make_shared<sphere>(point3(translacao + 0.75, 1.3, -1.0), 0.10, material_biceps));

    world.add(make_shared<sphere>(point3(translacao + -0.88, 1.25, -1.0), 0.08, material_arm));
    world.add(make_shared<sphere>(point3(translacao + 0.88, 1.25, -1.0), 0.08, material_arm));


    cam.lookfrom = point3(2, 1, 1.18); // mover câmera +2 no eixo X
    cam.lookat   = point3(1, 1, -1); // modificar visão da câmera, movendo +1 no eixo X
    cam.vup      = vec3(0,1,3); // alterar vetor de direção up. Provocou rotação da câmera.

    // Segunda renderização para "image2.ppm"
    cam.render(world, "image2.ppm");


}