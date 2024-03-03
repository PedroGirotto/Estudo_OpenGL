#pragma once
#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>



/* 
* ANOTAÇÕES TEÓRICAS
*	VBO: Vertex buffer object
*		VBO é um buffer quer guarda valores das vertices;
*		É mais eficiente do que mandar esses valores toda hora para a GPU
*		(isso é por causa da VBO ser armazenada na memória da GPU)
*	Alocando VBO:
*		glGenBuffers(1, &NOME_VARIAVEL); <-- gera um ponteiro para o VBO
*		glBindBuffer(TIPO_BUFFER, NOME_VARIAVEL); <-- conectar ponteiro com o tipo do buffer
*	Desalocando VBO:
		glBindBuffer(TIPO_BUFFER, 0);
* 
*	VAO: Vertex array object
*		VAO guarda a configuração dos atributos dos vertices e sua assossiação com VBO
*		Permite configurar todos os ponteiros e configurações para a renderização
*		Excelente para organizar e gerenciar os atributos dos vertices
*	Alocando VAO:
*		glGenVertexArrays(1, &NOME_VARIAVEL); <-- gera um ponteiro para o VAO
*		glBindVertexArray(NOME_VARIAVEL); <-- conectar ponteiro com o tipo do buffer
*	Desalocando VAO:
		glBindVertexArray(0);
* 
*	EBO: Element buffer object
*		EBO é utilizado para indexar dados de vertice, reduz duplicidade pois pode
*		reutilizar os mesmos pontos
*		Muito bom para otimização de dados da GPU
*	Alocando EBO:
*		glGenBuffers(1, &NOME_VARIAVEL); <-- gera um ponteiro para o EBO
*		glBindBuffer(TIPO_BUFFER, NOME_VARIAVEL); <-- conectar ponteiro com o tipo do buffer
*	Desalocando EBO:
		glBindBuffer(TIPO_BUFFER, 0);


*	SHADERS
*		Programa executado na GPU para controlar partes da pipeline de renderização
*	
*	VERTEX SHADER
*		É um estágio do pipeline de renderização com o objetivo de processas as vertices individuais
*		Transformar as coordenadas do espaço digital para o espaço da camera normalizado
*		Utilizado para fazer calculos nos vertex do objeto
*	FRAGMENT SHADER
*		Processa os fragmentos do VERTEX SHADER
*		Faz o processo de rasterizing e cor para os pixels
*		
*/



/*
* 1° Exercício
*	Try to draw 2 triangles next to each other using glDrawArrays 
	by adding more vertices to your data.
*/

float vertices_triangulos[] = {
	// 1° triangulo
	-0.5f, 0.5f, 0.0f, // canto direito superior
	0.5f, 0.5f, 0.0f, // canto direito inferior
	0.5f, -0.5f, 0.0f, // canto esquerdo superior
	-0.5f, 0.5f, 0.0f, // canto esquerdo superior
	-0.5f, -0.5f, 0.0f, // canto esquerdo inferior
	0.5, -0.5f, 0.0f // canto direito inferior
};

unsigned int VBO_triangulos;

unsigned int VAO_triangulos;

const char *vertex_sharder_codigo_triangulos = "#version 330 core\n"
	"layout (location = 0) in vec3 posicao;\n"
	"void main(){\n"
	"gl_Position = vec4(posicao, 1.0);\n"
	"}\0";

unsigned int vertex_shader_triangulos;

const char* fragment_shader_codigo_triangulo = "#version 330 core\n"
"out vec4 cor;\n"
"void main(){\n"
"cor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

unsigned int fragment_shader_triangulo;

unsigned int program_shader_triangulo;



void configurar_exercicio01() {
	glGenVertexArrays(1, &VAO_triangulos);
	glGenBuffers(1, &VBO_triangulos);

	glBindVertexArray(VAO_triangulos);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_triangulos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangulos), vertices_triangulos, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



int configurar_shaders_exercicio01() {
	vertex_shader_triangulos = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_triangulos, 1, &vertex_sharder_codigo_triangulos, NULL);
	glCompileShader(vertex_shader_triangulos);

	int sucesso_compilacao;
	char log_erro[512];
	glGetShaderiv(vertex_shader_triangulos, GL_COMPILE_STATUS, &sucesso_compilacao);
	if (!sucesso_compilacao) {
		glGetShaderInfoLog(vertex_shader_triangulos, 512, NULL, log_erro);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log_erro << "\n";

		glDeleteShader(vertex_shader_triangulos);
		return -1;
	}

	fragment_shader_triangulo = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_triangulo, 1, &fragment_shader_codigo_triangulo, NULL);
	glCompileShader(fragment_shader_triangulo);

	glGetShaderiv(fragment_shader_triangulo, GL_COMPILE_STATUS, &sucesso_compilacao);
	if (!sucesso_compilacao) {
		glGetShaderInfoLog(fragment_shader_triangulo, 512, NULL, log_erro);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log_erro << "\n";

		glDeleteShader(vertex_shader_triangulos);
		glDeleteShader(fragment_shader_triangulo);
		return -1;
	}

	program_shader_triangulo = glCreateProgram();
	glAttachShader(program_shader_triangulo, vertex_shader_triangulos);
	glAttachShader(program_shader_triangulo, fragment_shader_triangulo);
	glLinkProgram(program_shader_triangulo);

	glGetProgramiv(program_shader_triangulo, GL_LINK_STATUS, &sucesso_compilacao);
	if (!sucesso_compilacao) {
		glGetProgramInfoLog(program_shader_triangulo, 512, NULL, log_erro);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << log_erro << "\n";

		glDeleteShader(vertex_shader_triangulos);
		glDeleteShader(fragment_shader_triangulo);
		glDeleteProgram(program_shader_triangulo);
		return -1;
	}

	glDeleteShader(vertex_shader_triangulos);
	glDeleteShader(fragment_shader_triangulo);

	return 1;
}



void desenhar_exercicio01() {
	glUseProgram(program_shader_triangulo);
	glBindVertexArray(VAO_triangulos);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}



void limpar_exercicio01() {
	glDeleteVertexArrays(1, &VAO_triangulos);
	glDeleteBuffers(1, &VBO_triangulos);
	glDeleteProgram(program_shader_triangulo);
}