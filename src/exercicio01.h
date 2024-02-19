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



void configurar_exercicio01() {
	glGenBuffers(1, &VBO_triangulos);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_triangulos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangulos), vertices_triangulos, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO_triangulos);
	glBindVertexArray(VAO_triangulos);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
}



void configurar_shaders_exercicio01() {

}



void desenhar_exercicio01() {
	glBindVertexArray(VAO_triangulos);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}