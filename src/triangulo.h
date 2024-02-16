#pragma once
#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>



// os tr�s pontos do tri�ngulo
float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

// vertex buffer memory - colocar as v�rtices da figura na memoria
// da GPU
unsigned int VBO;

// vari�vel para salvar o c�digo GLSL para pegar a posi��o dos vertex
const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main(){\n"
	"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

// objeto GL para salvar o ID do vertexShader
unsigned int vertexShader;

// verificar o status da compila��o dos shaders
int success;
// salvar a string de log de erro das shaders
char infoLog[512];

// c�digo do GLSL para renderizar cor
const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main(){\n"
	"FragColor = vec4(0.33f, 0.69f, 0.33f, 1.0f);\n"
	"}\0";

// objeto GL para salvar o ID do fragmentShader
unsigned int fragmentShader;

// objeto GL para salvar o ID do shaderProgram
// esse ID que � respons�vel por juntar ambos os shaders para renderizar
unsigned int shaderProgram;
	
unsigned int VAO;



void configurarShader() {
	// gerando o ID do VBO para o openGL
	glGenBuffers(1, &VBO);

	// definindo o tipo de buffer do VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// copiando os dados do vertices para o buffer VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_COPY);



	// gerando o ID do objeto GL para o shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// conectando o c�digo para o ID GL
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// compilar o c�digo
	glCompileShader(vertexShader);



	// pegar o status da compila��o do shader vertexShader
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		// salvar o erroLog na vari�vel
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Erro na compila��o do vertex shader\n" << infoLog << "\n";
	}



	// gerar o ID do fragmentShader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// conectar o ID do GL com o c�digo
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// compilar o c�digo GLSL
	glCompileShader(fragmentShader);

	// pegar o status da compila��o do fragmentShader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		// salvar o erroLog na vari�vel
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Erro na compila��o do fragment shader\n" << infoLog << "\n";
	}



	// criar o ID do shaderProgram
	shaderProgram = glCreateProgram();

	// linkando cada um dos shaders no shaderProgram
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// mesmo processo para verificar o status da compila��o e
	// imprimir o erroLog
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Erro na compila��o do shader\n" << infoLog << "\n";
	}
	// ativar nosso programa com os shaders
	glUseProgram(shaderProgram);



	// limpando a mem�ria dos shaders antigos
	// j� est�o linkadas ent�o n�o h� porque continuar na mem�ria
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// utilizado para explicar como estar a estrutura do nosso vetor
	// com os vertices
	// o openGL precisa disso para conseguir fazer as opera��es de mem�ria
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}



// renderiza��o
void desenharTriangulo() {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}