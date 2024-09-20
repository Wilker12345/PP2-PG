# P2-WebGL
Projeto elaborado para a disciplina de Processamento Gráfico. 

### Arquivos:
- **index.html:** arquivo html inclui um elemento canvas para renderização gráfica e links para bibliotecas JavaScript, como TWGL e utilitários WebGL.
- **styles.css:** arquivo css de estilização da página.
- **main.js:** arquivo javascript contendo a renderização da cena, com seus objetos, suas texturas e iluminação e a câmera.

### Objetos
Os objetos presentes na cena são: um olho, contendo um arquivo .obj, .mtl (arquivo para definição dos de cor, brilho, mapa de textura) e a textura; uma mesa, contendo .obj, .mtl e textura. Ambos os objetos estão contidos no repositório.

### Cena
A cena é composta por dois objetos (olho e mesa), cada um apresentando seu próprio movimento. A mesa, primeiro, sofreu uma translação, adotando um movimento oscilatório na vertical. Na sequência, foi realizada uma rotação em 90 graus, conferindo uma melhor visualização da mesa na cena.
Para o olho, foi aplicada uma translação, reposicionando o objeto mais acima no eixo Y. Depois, foi aplicada a rotação, com o movimento de rotação no próprio eixo do objeto.

### Câmera
A câmera aponta para o ponto [0, 1.5, 0], onde fica o objeto criado. A posição da câmera no plano são os pontos [0, radius, radius]. Temos duas variáveis que limitam o processamento da imagem, sendo elas o zNear e o zFar, no qual fazem o limite para quando  objeto está muito perto ou quando está muito longe, respectivamente. Temos um Field Of View (FOV) de 120 graus, usada em radianos. Também temos uma variável up, que define a direção "para cima", garantindo uma orientação correta. Por fim, usamos a função lookat() para fazer a câmera olhar para os pontos onde estão os objetos.

### Execução
O projeto foi desenvolvido em JavaScript, HTML e CSS e utiliza a biblioteca TWGL.
Para a execução do index.html, é necessário configurar o servidor - no caso, foi utilizado o comando python3 -m http.server 8000 no diretório do projeto.