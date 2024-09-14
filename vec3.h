#ifndef VEC3_H
#define VEC3_H

#include <rtweekend.h>

class vec3{
    public:
        double e[3];
        
        //  cria um construtor (uma função que é chamada assim que o objeto vec3 é criado). Esse construtor é chamado quando o objeto é declarado sem
        //  nenhum parâmetro, ou seja, vazio

        vec3() : /*inicialização*/ e{0,0,0} {/*o que o construtor faz, no caso, nada*/}

        // mesma coisa que o anterior, mas é um construtor que é chamado quando o objeto é declarado com valores, insere esses valores recebidos
        // nas variaveis respectivas
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        // retorna o eixo x, especificamente
        double x() const {
            return e[0];
        }
        
        // retorna o eixo y, especificamente
        double y() const {
            return e[1];
        }
        
        // retorna o eixo z, especificamente
        double z() const {
            return e[2];
        }

        // faz uma sobrecarga no operador - , o que essa função faz é inverter os valores dos eixos x,y,z do vetor desse objeto
        vec3 operator-() const {
            return vec3(-e[0], -e[1], -e[2]); 
        }

        // faz uma sobrecarga no operador [] , o que essa função faz é permitir com que a gente faca o acesso a um eixo "i" do vetor desse objeto
        double operator[](int i) const {
            return e[i];
        }

        // faz uma sobrecarga no operador [] , o que essa função faz é permitir com que a gente faca o acesso a um eixo "i" do vetor desse objeto
        double& operator[](int i) {
            return e[i];
        }

        // recebe um veotr v, soma com os valores x,y,z do vetor desse objeto e retorna esse novo vetor
        vec3& operator+=(const vec3& v){
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        // recebe um double t, multiplica com os valores x,y,z do vetor dessa classe e retorna esse novo vetor
        vec3& operator*=(double t){
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        //divide cada operador do vetor por 
        vec3& operator/=(double t){
            return *this *= 1/t;
        }

        // retorna o comprimento do vetor 3D
        double length() const{
            return std::sqrt(length_squared());
        }

        // retorna a magnitudo do vetor 3D
        double length_squared() const{
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
};

// cria um apelido (alias) para o vetor vec3, isso ajuda na legibilidade do código
using point3 = vec3;

// Funções de utilidade de vetor

//as funções a seguir fazer sobrecargas de funções ja existentes no C++
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

// produto escalar
inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

// produto vetorial
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// pega o vetor unitário (vetor que apenas mostra a direção)
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

#endif