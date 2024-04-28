# Listas-PG-Gabrielle
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
