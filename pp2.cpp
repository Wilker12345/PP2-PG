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


#include <rtweekend.h>

#include <hittable.h>
#include "hittable_list.h"
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

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {
    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // World

    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera

    // distância focal da imagem é a distância no eixo z, ou seja, da câmera para o viewport no eixo z, (não no x, horizontal, e nem no y, vertical)
    auto focal_length = 1.0; 
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    //cria os vetores viewport_u e v, eles marcam o tamanho do viewport
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    //calcula a distÇancia entre pixels
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    //tem uma diferença dos centros dos sistema de coordenadas da câmera para a matriz de imagem que a gente produz, então esses passos aqui são para ajeitar isso
    //ou seja, unificar os centros dos dois sistemas de coordeanas. A câmera está no centro e o pixel superior esquerdo deve ficar no centro (da câmera)
    //tem outros problemas além dos centros estarem diferentes, como por exemplo, a matriz cresce para baixo, no sistema de coordenadas da câmera, ir para baixo diminui
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) /*faz o ajuste no eixo z*/ - viewport_u/2 /*faz ajuste no eixo x*/ - viewport_v/2 /*faz ajuste no eixo y*/;

    //pega a pixel central no novo sistema de coordenas da câmera
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            //itera por todos os pixels da imagem.
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            //pega a direção do centro da camera para o pixel central (atual)
            auto ray_direction = pixel_center - camera_center;
            //faz a colorização do raio
            ray r(camera_center, ray_direction);

            //pinta o raio?
            color pixel_color = ray_color(r, world);

            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}