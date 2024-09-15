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


int main() {
    hittable_list world;


    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.8));
    auto material_lower = make_shared<metal>(color(1, 1, 1), 0.0);
    auto material_upper = make_shared<lambertian>(color(1, 1, 1));
    auto material_head = make_shared<metal>(color(1, 1, 1), 1);
    auto material_eye = make_shared<metal>(color(0, 0, 0), 1.0);
    auto material_nose = make_shared<lambertian>(color(1, 0.45, 0));
    auto material_mouth = make_shared<lambertian>(color(0, 0, 0));

    auto material_buttons = make_shared<lambertian>(color(0, 0, 0));

    auto material_shoulder = make_shared<metal>(color(1, 1, 1), 0.0);
    auto material_biceps = make_shared<dielectric>(1.50);
    auto material_arm = make_shared<lambertian>(color(1, 1, 1));


    auto material_ballA = make_shared<lambertian>(color(1, 0, 1));
    auto material_ballB = make_shared<lambertian>(color(0.56, 0, 1));
    auto material_ballC = make_shared<lambertian>(color(0, 1, 1));


    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    cam.vfov = 90;

    ///////////////////////////////////////////////////////////////////////////////////////
    // IMAGEM 1

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -2.0), 100.0, material_ground)); //esfera que representa mundo
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -2.0),   0.8, material_lower)); //primeira esfera do boneco.
    world.add(make_shared<sphere>(point3(0.0,    1.1, -2.0),   0.5, material_upper)); //segunda esfera do boneco 
    world.add(make_shared<sphere>(point3(0.0,    1.90, -2.0),   0.35, material_head));//cabeça do boneco

    // olhos e naris do boneco
    world.add(make_shared<sphere>(point3(-0.1, 1.8, -1.5), 0.05, material_eye));
    world.add(make_shared<sphere>(point3(0.1, 1.8, -1.5), 0.05, material_eye));
    world.add(make_shared<sphere>(point3(0.0, 1.7, -1.5), 0.03, material_nose));

    
    // boca do boneco
    world.add(make_shared<sphere>(point3(-0.10, 1.60, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.09, 1.59, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.08, 1.59, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.07, 1.58, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.06, 1.58, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.05, 1.57, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.04, 1.57, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.03, 1.56, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.02, 1.56, -1.5), 0.01, material_mouth));
    
    world.add(make_shared<sphere>(point3(-0.01, 1.55, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0, 1.55, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.01, 1.55, -1.5), 0.01, material_mouth));

    world.add(make_shared<sphere>(point3(0.02, 1.56, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.03, 1.56, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.04, 1.57, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.05, 1.57, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.06, 1.58, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.07, 1.58, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.08, 1.59, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.09, 1.59, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.10, 1.60, -1.5), 0.01, material_mouth));



    // botões do boneco
    world.add(make_shared<sphere>(point3(0.0, 1.3, -1.5), 0.03, material_buttons));
    world.add(make_shared<sphere>(point3(0.0, 1.15, -1.5), 0.03, material_buttons));
    world.add(make_shared<sphere>(point3(0.0, 1, -1.5), 0.03, material_buttons));

    // braços do boneco
    world.add(make_shared<sphere>(point3(-0.55, 1.4, -2.0), 0.15, material_shoulder));
    world.add(make_shared<sphere>(point3(0.55, 1.4, -2.0), 0.15, material_shoulder));
    world.add(make_shared<sphere>(point3(-0.75, 1.3, -2.0), 0.10, material_biceps));
    world.add(make_shared<sphere>(point3(0.75, 1.3, -2.0), 0.10, material_biceps));
    world.add(make_shared<sphere>(point3(-0.88, 1.25, -2.0), 0.08, material_arm));
    world.add(make_shared<sphere>(point3(0.88, 1.25, -2.0), 0.08, material_arm));

    srand(42);

    // inserie mais esferas na imagem
    for (int a = -3; a < 3; a++) {
        for (int b = -3; b < 1; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.5*random_double(), 0, b - 0.5*random_double());

            if ((center - point3(0, 0, -2)).length() > 1.2) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }
    
    cam.lookfrom = point3(0,1,1.18);
    cam.lookat   = point3(0,1,-1);
    cam.vup      = vec3(0,1,0);

    cam.render(world, "image1.ppm");

    ///////////////////////////////////////////////////////////////////////////////////////

     world.clear();
    // IMAGEM 2

    int deslocamento = 2;

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -2.0), 100.0, material_ground)); //esfera que representa mundo
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -2.0),   0.8, material_lower)); //primeira esfera do boneco.
    world.add(make_shared<sphere>(point3(0.0,    1.1, -2.0),   0.5, material_upper)); //segunda esfera do boneco 
    world.add(make_shared<sphere>(point3(0.0,    1.90, -2.0),   0.35, material_head)); //cabeça do boneco

    world.add(make_shared<sphere>(point3(-0.1, 1.8, -1.5), 0.05, material_eye));
    world.add(make_shared<sphere>(point3(0.1, 1.8, -1.5), 0.05, material_eye));
    world.add(make_shared<sphere>(point3(0.0, 1.7, -1.5), 0.03, material_nose));

    
    world.add(make_shared<sphere>(point3(-0.10, 1.60, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.09, 1.59, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.08, 1.59, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.07, 1.58, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.06, 1.58, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.05, 1.57, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.04, 1.57, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.03, 1.56, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(-0.02, 1.56, -1.5), 0.01, material_mouth));
    
    world.add(make_shared<sphere>(point3(-0.01, 1.55, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0, 1.55, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.01, 1.55, -1.5), 0.01, material_mouth));

    world.add(make_shared<sphere>(point3(0.02, 1.56, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.03, 1.56, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.04, 1.57, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.05, 1.57, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.06, 1.58, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.07, 1.58, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.08, 1.59, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.09, 1.59, -1.5), 0.01, material_mouth));
    world.add(make_shared<sphere>(point3(0.10, 1.60, -1.5), 0.01, material_mouth));

    world.add(make_shared<sphere>(point3(0.0, 1.3, -1.5), 0.03, material_buttons));
    world.add(make_shared<sphere>(point3(0.0, 1.15, -1.5), 0.03, material_buttons));
    world.add(make_shared<sphere>(point3(0.0, 1, -1.5), 0.03, material_buttons));

    world.add(make_shared<sphere>(point3(-0.55, 1.4, -2.0), 0.15, material_shoulder));
    world.add(make_shared<sphere>(point3(0.55, 1.4, -2.0), 0.15, material_shoulder));

    world.add(make_shared<sphere>(point3(-0.75, 1.5, -2.0), 0.10, material_biceps));
    world.add(make_shared<sphere>(point3(0.75, 1.5, -2.0), 0.10, material_biceps));

    world.add(make_shared<sphere>(point3(-0.88, 1.55, -2.0), 0.08, material_arm));
    world.add(make_shared<sphere>(point3(0.88, 1.55, -2.0), 0.08, material_arm));

    srand(42);

    for (int a = -3; a < 3; a++) {
        for (int b = -3; b < 1; b++) {
            auto choose_mat = random_double();
            point3 center(deslocamento + a + 0.5*random_double(), 0, b - 0.5*random_double());

            if ((center - point3(0, 0, -2)).length() > 1.2) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }


    cam.lookfrom = point3(0, 1, 2); // aumento da distância da câmera ao objeto (aumento de Z)
    cam.lookat   = point3(0, 1, -1); 
    cam.vup      = vec3(2,1,0); // alterar vetor de direção up. Provocou rotação da câmera (+2 no eixo X)

    // Segunda renderização para "image2.ppm"
    cam.render(world, "image2.ppm");


}