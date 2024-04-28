
#include <iostream>
#include <string>
#include <assert.h>

//Vector
#include <vector>

//CMath -> do C++
#include <cmath>

using namespace std;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Classe para manipulação dos shaders
#include "shader.h"

// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipos das funções
int setupGeometry();

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;

// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	//Muita atenção aqui: alguns ambientes não aceitam essas configurações
	//Você deve adaptar para a versão do OpenGL suportada por sua placa
	//Sugestão: comente essas linhas de código para desobrir a versão e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ola Triangulo! -- Gabrielle", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros de funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informações de versão
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;
	
	// Compilando e buildando o programa de shader
	Shader shader("../shaders/helloTriangle.vs", "../shaders/helloTriangle.fs");

	// Gerando um buffer simples
	GLuint VAO = setupGeometry();
	
	// Enviando a cor desejada (vec4) para o fragment shader
	// Utilizamos a variáveis do tipo uniform em GLSL para armazenar esse tipo de info
	// que não está nos buffers
	GLint colorLoc = glGetUniformLocation(shader.ID, "inputColor");
	
	shader.Use();
	
	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glLineWidth(10);
		glPointSize(20);

		glBindVertexArray(VAO); //Conectando ao buffer de geometria

		// Chamada de desenho - drawcall

		// Desenha telhado vermelho
		glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f); //enviando cor para variável uniform inputColor
		glDrawRangeElements(GL_TRIANGLES, 0, 0, 3, GL_UNSIGNED_INT, 0);

		//Desenha parede marrom
		glUniform4f(colorLoc, 0.59f, 0.29f, 0.0f, 1.0f); //enviando cor para variável uniform inputColor
		glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, 1);
		glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, 2);
		
		//Desenha a porta branca
		glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f); //enviando cor para variável uniform inputColor
		glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, 6);
		glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, 5);
		
		glBindVertexArray(0); //Desconectando o buffer de geometria

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Função de callback de teclado - só pode ter uma instância (deve ser estática se
// estiver dentro de uma classe) - É chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int  setupGeometry(){

	GLfloat vertices[] = {
		0.0, 1.0, 0.0, // topo telhado (0)
		-0.5, 0.5, 0.0, // parede topo esquerda (1)
		0.5, 0.5, 0.0, //parede topo direita (2)
		-0.5, -0.5, 0.0, //parede baixo esquerda (3)
		0.5, -0.5, 0.0, //parede baixo direita (4)
		-0.25, -0.5, 0.0, //porta baixo esquerda (5)
		0.25, -0.5, 0.0, //porta baixo direita (6)
		-0.25, 0.25, 0.0, //porta topo esquerda (7)
		0.25, 0.25, 0.0, //porta topo direita (8)
	};

	GLuint indices[] ={
		0, 1, 2, //telhado
		1, 3, 4, // triangulo 1 da parede
		1, 2, 4, // triangulo 2 da parede
		7, 5, 6, // triangulo 1 da porta
		7, 8, 6 // triangulo 2 da porta
	};

	//Configuracao dos buffers VBO e VAO
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}