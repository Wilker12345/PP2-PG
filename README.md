## Passos para Compilação e Execução

**Criar o diretório de build:**
```mkdir build ```

**Acessar diretório build:**
```cd build```

**Gerar arquivos de compilação:**
```cmake ..```

**Compilar projeto:**
```cmake --build .```

**Executar projeto:**
```./pp2```


**Anmação foi gerada utilizando o FFmpeg**
```.ffmpeg -framerate 30 -i frame%d.ppm -vf "scale=1200:675" -c:v libx264 -pix_fmt yuv420p animation.mp4```
