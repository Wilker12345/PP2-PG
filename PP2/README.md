# PP2-Ray Tracing
Projeto elaborado para a disciplina de Processamento Gráfico. 

### Diretórios:
- **imagens:** contém as imagens e a animação geradas.
- **src:** contém os arquivos do projeto.

### Objetos
Os objetos presentes na cena são: esferas de diversos materiais (metálica, lambertiana, dielétrica) e raios, representando inúmeros elementos da cena: chão, corpo do boneco, olhos, flocos de neve, etc.

### Câmera

A câmera está afastada do boneco em 2 posições no eixo Z e, então, passa a rotacionar em torno dele. O lookat (para onde a câmera olha) foi mantido fixo, garantindo sempre a visão dos objetos da cena. O Field of View (FOV) foi mantido em 90. 

### Cena
A cena retrata um boneco de neve em meio a um ambiente nevado, enquanto a câmera realiza uma suave rotação ao redor dele. Com o desenrolar do vídeo, as esferas que compõem o boneco começam a se afastar lentamente, transmitindo a sensação de desmontagem gradual.

O boneco é construído a partir de diferentes materiais: a esfera inferior é metálica, a do meio é feita de um material dielétrico, e a cabeça e os olhos também possuem uma superfície metálica. As esferas menores que formam a boca, o nariz e os botões são de material lambertiano, conferindo a elas uma aparência menos reflexiva.


### Execução
**Acessar diretório src:**
```cd src ```

**Compilar arquivo main.cc:**
```g++ -std=c++17 -o pp2 main.cc```

**Executar projeto:**
```./pp2```

**Também é possível renderizar apenas um intervalo de frames:**
```./pp2 0 10```

Executar o seguinte comando, dentro diretório imagens, para gerar a animação:
```ffmpeg -framerate 30 -start_number 0 -i "image%d.ppm" animation.mp4```
