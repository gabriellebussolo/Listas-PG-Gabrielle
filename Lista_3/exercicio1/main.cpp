
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Compilando e buildando o programa de shader
	Shader shader("../shaders/ortho.vs", "../shaders/ortho.fs");

	// Gerando um buffer simples, com a geometria de um triângulo
	GLuint VAO = setupGeometry();

	shader.Use();
	
	//Matriz de projecao paralela ortografica
	glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	shader.setMat4("projection", glm::value_ptr(projection));

	// Matriz de transformacao do objeto (matriz de modelo)
	glm::mat4 model1 = glm::mat4(1);
	model1 = glm::translate(model1, glm::vec3(400.0, 300.0, 0.0));
	model1 = glm::rotate(model1, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	model1 = glm::scale(model1, glm::vec3(300.0, 300.0, 0.0));
	shader.setMat4("model", glm::value_ptr(model1));
	
	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		// Limpa o buffer de cor
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		glBindVertexArray(VAO); //Conectando ao buffer de geometria

		// Matriz de transformacao do objeto (matriz de modelo)
		glm::mat4 model1 = glm::mat4(1);
		model1 = glm::translate(model1, glm::vec3(400.0, 300.0, 0.0));
		model1 = glm::rotate(model1, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		model1 = glm::scale(model1, glm::vec3(300.0, 300.0, 0.0));
		shader.setMat4("model", glm::value_ptr(model1));

		// quadrante superior direito
		glViewport(width/2, height/2, width/2, height/2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Matriz de transformacao do objeto (matriz de modelo)
		glm::mat4 model2 = glm::mat4(1);
		model2 = glm::translate(model2, glm::vec3(400.0, 300.0, 0.0));
		model2 = glm::rotate(model2, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
		model2 = glm::scale(model2, glm::vec3(400.0, 400.0, 0.0));
		shader.setMat4("model", glm::value_ptr(model2));

		//quadrante inferior esquerdo
		glViewport(0, 0, width/2, height/2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Matriz de transformacao do objeto (matriz de modelo)
		glm::mat4 model3 = glm::mat4(1);
		model3 = glm::translate(model3, glm::vec3(400.0, 300.0, 0.0));
		model3 = glm::rotate(model3, glm::radians(270.0f), glm::vec3(0.0, 0.0, 1.0));
		model3 = glm::scale(model3, glm::vec3(200.0, 200.0, 0.0));
		shader.setMat4("model", glm::value_ptr(model3));

		//quadrante superior esquerdo
		glViewport(0, height/2, width/2, height/2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

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

int setupGeometry()
{
	
	GLfloat vertices[] = {
		//x   y     z    r   g    b
		0.0, 0.5, 0.0, 1.0, 0.0, 0.0,// P1 - vermelho
		-0.5, -0.5, 0.0, 0.0, 1.0, 0.0,//P2 - verde
		0.5, -0.5, 0.0, 0.0, 0.0, 1.0,//P3 - azul
	};

	GLuint VBO, VAO;
	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 
	
	//Atributo 0 - posição
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo 1 - cor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}