# PP2-Ray Tracing
Projeto elaborado para a disciplina de Processamento Gráfico. 

### Diretórios:
- **imagens:** contém as imagens e a animação geradas.
- **src:** contém os arquivos do projeto.

### Mudanças:
- **camera.h:** adaptação da função render para receber o nome do arquivo de saída
- **main.cc:** código para gerar os objetos e cenas aqui descritas.

### Objetos
Os objetos presentes na cena são: esferas de diversos materiais (metálica, lambertiana, dielétrica) e raios, representando inúmeros elementos da cena: chão, corpo do boneco, olhos, flocos de neve, etc.

### Cena
A cena retrata um boneco de neve em meio a um ambiente nevado, enquanto a câmera realiza uma suave rotação ao redor dele. Com o desenrolar do vídeo, as esferas que compõem o boneco começam a se afastar lentamente, transmitindo a sensação de desmontagem gradual.

O boneco é construído a partir de diferentes materiais: a esfera inferior é metálica, a do meio é feita de um material dielétrico, e a cabeça e os olhos também possuem uma superfície metálica. As esferas menores que formam a boca, o nariz e os botões são de material lambertiano, conferindo a elas uma aparência menos reflexiva.

Passando a uma descrição mais detida da cena:

A câmera olha para a posição (0, 1, -2). Comparando com o boneco, a câmera está observando com uma leve inclinação no eixo Y.

### Esfera do Solo:
 Representa o chão e está posicionada em (0.0, -100.5, -2.0), tendo um raio de 100.0.

### Boneco de neve:
- Base do boneco: posição inicial (0, 0, -2), com raio = 0.8;
- Parte superior do boneco: posição inicial (0, 1,1, -2), com raio = 0.5;
- Base do boneco: posição inicial (0, 1,85, -2), com raio = 0.35;
- olho do boneco: posição inicial (-0.1, 1,90, -1,68), com raio - 0.05 - um pouco à frente do corpo do boneco;
- olho do boneco: posição inicial (0.1, 1,90, -1,68), com raio = 0.05 - um pouco à frente do corpo do boneco;
- nariz do boneco: posição inicial (0.0, 1,80, -1,68), com raio = 0.05 - um pouco à frente do corpo do boneco;
- boca do boneco: 20 esferas de raio 0.01, com a posição central sendo (0, 1.65, -1,68);
- botões do boneco: 5 esferas de raio 0.05, com a primeira na posição inicial (0, 1.3, -1,5);

### Flocos de neve:
- 100 flocos de neve, com raio = 0.04, gerados em posições aleatórias no seguinte espaço:
  - x = (-5, 5);
  - y = (2, 5); ==> acima do boneco
  - z = (-3, 4);

### Câmera
A câmera está afastada do boneco em 2 posições no eixo Z e, então, passa a rotacionar em torno dele. O lookat (para onde a câmera olha) foi mantido fixo, garantindo sempre a visão dos objetos da cena. O Field of View (FOV) foi definido como 90. 

### Execução
**Acessar diretório src:**
```cd src ```

**Compilar arquivo main.cc:**
```g++ -std=c++17 -o pp2 main.cc```

**Executar projeto:**
```./pp2```

**Também é possível renderizar apenas um intervalo de frames:**
```./pp2 0 10```

**Executar o seguinte comando, dentro diretório imagens, para gerar a animação:**
```ffmpeg -framerate 30 -start_number 0 -i "image%d.png" -c:v libx264 -pix_fmt yuv420p animation.mp4```
