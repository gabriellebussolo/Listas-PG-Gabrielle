/*

VBO -> criarei o VBO de forma que o array fique com as posicoes e as cores de cada vertice, ou seja, (X,Y,Z,R,G,B).
Com base no triangulo proposto, ficaria assim o array do VBO:
{   //x   y     z    r   g    b
	0.0, 0.6, 0.0, 1.0, 0.0, 0.0,// P1 - vermelho
	-0.6, -0.5, 0.0, 0.0, 1.0, 0.0,//P2 - verde
	0.6, -0.3, 0.0, 0.0, 0.0, 1.0,//P3 - azul
};

VAO -> Já no VAO, chamarei o glVertexAttribPointer duas vezes, uma para cara atributo que define, ou seja,
um para a posicao e o outro para a cor

* A chamada da posicao ficaria assim:
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
atributo 1 (0) - defino o atributo que estou linkando. Aqui o atributo será a posicao, entao coloco 0.
Este atributo estará no vertex shader com o (location = 0).
atributo 2 (3)- especifica o tamanho do atributo, no caso 3, pois é xyz
atributo 3 (GL_FLOAT) - especifica o tamanho de cada dado
atributo 4 (GL_FALSE) - especifica se os dados precisam ser normalizados. Nesse caso já está
atributo 5 (6 * sizeof(GLfloat)) - tamanho do buffer, nesse caso coloco 6* porque tem xyzrgb
atributo 6 ((GLvoid*)0) - deslocamento inicial do buffer, no caso é nenhum

* A chamada da cor ficaria bem parecida com a mudança de alguns atributos:
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
atributo 1 (1) - Aqui o atributo será a cor, entao coloco 1. Este atributo estará no vertex shader com o (location = 1).
atributo 2 (3)- especifica o tamanho do atributio, no caso 3, pois é rgb
atributo 6 ((GLvoid*)0) - deslocamento inicial do buffer, no caso é 3 porque quero pegar o rgb e nao o xyz

EBO -> não será usado porque tenho apenas um triângulo
*/

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

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
	Shader shader("../shaders/exercicio8.vs", "../shaders/exercicio8.fs");

	// Gerando um buffer simples
	GLuint VAO = setupGeometry();

	shader.Use();
	
	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		glBindVertexArray(VAO); //Conectando ao buffer de geometria

		//Contorno de um triangulo em azul
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Vertices do triangulo
		glDrawArrays(GL_POINTS, 0, 3);

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
		0.0, 0.6, 0.0, 1.0, 0.0, 0.0,// P1 - vermelho
		-0.6, -0.5, 0.0, 0.0, 1.0, 0.0,//P2 - verde
		0.6, -0.3, 0.0, 0.0, 0.0, 1.0,//P3 - azul
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