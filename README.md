# Listas-PG-Gabrielle

Nome: Gabrielle Bussolo

Esse repositório contém as listas de exercícios da disciplina de Processamento Gráfico realizada em 2024/1.

## Especificação
Os códigos foram elaborados na linguagem C++, utilizando o Visual Studio Code. 
Além disso, o ambiente utilziado foi um macOS. Dessa forma, se o seu ambiente for Windows, a parte do código ``main.cpp`` de todos os exercícios que se encontra a seguir, pode ser comentada da seguinte forma:

```C++
//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
```

Outro cuidado importante é que abaixo dessa linha há outro código que depende de cada ambiente de execução. Aqui, foram utilizados parâmetros para o meu ambiente de execução. Se não funcionar no seu, tente comentar as linhas e ajustar os parâmetros conforme o seu ambiente.

```C++
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
```

## Como rodar
Para executar os códigos, basta baixar o repositório e abrí-lo, de preferência no Visual Studio Code.

Cada Lista possui um diretório para cada exercício, com o arquivo .cpp que será executado.

<img width="200" alt="imagem do diretório do projeto com as pastas específicas de cada exercício" src="https://github.com/gabriellebussolo/Listas-PG-Gabrielle/assets/86787630/7900ed4f-afe1-414f-b13a-047fade1314b">

Dessa forma, para executar cada exercício, deve-se ajustar o arquivo ``tasks.json`` com o número do exercício que deseja-se executar:

<img width="700" alt="imagem demonstrando a parte do código que deve ser modificada para executar cada exercício" src="https://github.com/gabriellebussolo/Listas-PG-Gabrielle/assets/86787630/755f61dd-50b6-4e6a-9ae7-6bf57eab4b7f">

Depois de ajustar o arquivo ``tasks.json`` com o exercício específico, basta clicar no botão ``Run C/C++ file``:

<img width="152" alt="imagem demonstrando o botão Run C/C++ file" src="https://github.com/gabriellebussolo/Listas-PG-Gabrielle/assets/86787630/549b59ff-2ca1-40ed-a42b-00212262c1fc">

## Observações sobre os exercícios

### Lista 1
- Os exercícios 1 ao 4 não precisavam ser entregues então não estão nesse repositório.
- Restante dos exercícios estão no repositório.
- Exercício 8:
  - a)
    - VBO -> criarei o VBO de forma que o array fique com as posicoes e as cores de cada vertice, ou seja, (X,Y,Z,R,G,B).
      Com base no triangulo proposto, ficaria assim o array do VBO:
      ```C++
      {   //x   y     z    r   g    b
      	0.0, 0.6, 0.0, 1.0, 0.0, 0.0,// P1 - vermelho
      	-0.6, -0.5, 0.0, 0.0, 1.0, 0.0,//P2 - verde
      	0.6, -0.3, 0.0, 0.0, 0.0, 1.0,//P3 - azul
      };
      ```
    - VAO -> Já no VAO, chamarei o glVertexAttribPointer duas vezes, uma para cara atributo que define, ou seja, um para a posicao e o outro para a cor.
      A chamada da posicao ficaria assim:
      ```C++
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
      ```
      Sendo:
      - Atributo 1 (0) - defino o atributo que estou linkando. Aqui o atributo será a posicao, entao coloco 0. Este atributo estará no vertex shader com o (location = 0).
      - Atributo 2 (3)- especifica o tamanho do atributo, no caso 3, pois é xyz
      - Atributo 3 (GL_FLOAT) - especifica o tamanho de cada dado
      - Atributo 4 (GL_FALSE) - especifica se os dados precisam ser normalizados. Nesse caso já está
      - Atributo 5 (6 * sizeof(GLfloat)) - tamanho do buffer, nesse caso coloco 6* porque tem xyzrgb
      - Atributo 6 ((GLvoid*)0) - deslocamento inicial do buffer, no caso é nenhum
        
      A chamada da cor ficaria bem parecida com a mudança de alguns atributos:
      
      ```C++
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
      ```
      - Atributo 1 (1) - Aqui o atributo será a cor, entao coloco 1. Este atributo estará no vertex shader com o (location = 1).
      - Atributo 2 (3)- especifica o tamanho do atributio, no caso 3, pois é rgb
      - Atributo 6 ((GLvoid*)0) - deslocamento inicial do buffer, no caso é 3 porque quero pegar o rgb e nao o xyz

    - EBO -> não será usado porque tenho apenas um triângulo
  - b) O atributo da posição seria identificado no vertex shader com o (location = 0) e o atributo da cor com o (location = 1), da seguinte forma:
    ```
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    
    out vec3 vertexColor;
    
    void main()
    {
    	vertexColor = color;
    	//...pode ter mais linhas de código aqui!
    	gl_Position = vec4(position.x, position.y, position.z, 1.0);
    }
    ```
- No exercício 9, eu desenhei uma casinha de cachorro e repliquei ele utilizando OpenGL.

## Lista 2
- Exercícios 1, 2, 4 e 5 estão no repositório
- Exercício 3: Com base no exercício 2, o desenho não vai ficar mais centralizado com essa nova viewport. Além disso, o tamanho do desenho deverá ser ajustado. No meu caso, eu aumentei os valores dos vértices para que o desenho ficasse maior e pudesse ser visto com mais facilidade, já que agora a proporção da tela está maior.

## Lista 3
- Exercício 1 e 2 estão no repositório.
- O exercício 2 eu não consegui testar no meu ambiente, pois estava recebendo um erro de que os comandos da biblioteca ``stb_image`` não eram válidos para a minha arquitetura. Porém eu tentei fazer da mesma forma.
