## Passos para Compilação e Execução

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


A cena retrata um boneco de neve em meio a um ambiente nevado, enquanto a câmera realiza uma suave rotação ao redor dele. Com o desenrolar do vídeo, as esferas que compõem o boneco começam a se afastar lentamente, transmitindo a sensação de desmontagem gradual.
 
O boneco é construído a partir de diferentes materiais: a esfera inferior é metálica, a do meio é feita de um material dielétrico, e a cabeça e os olhos também possuem uma superfície metálica. As esferas menores que formam a boca, o nariz e os botões são de material lambertiano, conferindo a elas uma aparência menos reflexiva. 

As imagens são armazenadas no diretório "imagens". Para a construção da animação, foram geradas 90 imagens, a 30 quadros por segundo, totalizando 3 segundos de animação.