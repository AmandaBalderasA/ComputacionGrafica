/*

	Práctica 1 Dibujo de primitivas 2D
	Amanda Balderas Arias
	Fecha del día que subes la práctica
*/

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D Amanda", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		-0.44f, 0.27f, 0.0f,    0.4275f, 0.7804f, 0.8118f,  // A 0
		0.0f, 0.4f, 0.0f,    0.4275f, 0.7804f, 0.8118f,  // B 1
		0.7f, 0.0f, 0.0f,   0.4275f, 0.7804f, 0.8118f,  // E 2
		0.2f, 0.6f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // F 3
		0.13f, 0.32f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // G 4
		0.0f, 0.04f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // D 5
		-0.58f, 0.18f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // I 6
		-0.6f, 0.0f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // J 7
		-0.65f, 0.05f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // K 8
		-0.65f, 0.0f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // L 9
		-0.59f, 0.08f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // M 10 
		0.0f, -0.3f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // N 11
		0.7f, 0.1f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // P 12
		0.56f, 0.08f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // Q 13
		0.7f, -0.2f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // R 14
		0.56f, 0.01f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // S 15
		0.9f, 0.2f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // T 16
		-0.31f, 0.02f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // C 17
		-0.2f, 0.03f, 0.0f,   0.4275f, 0.7804f, 0.8118f, // H 18
	};
	unsigned int indices[] = {  // note that we start from 0!
		1,3,4, // aleta arriba
		2,1,5, // parte cuerpo
		1,5,18, // parte cuerpo
		1,2,15,5,17,7,6,0, // cuerpo completo
		8,9,7,10, //hocico
		5,18,11, //aleta
		13,12,16,2, // aleta
		15,2,14, //aleta
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glBindVertexArray(VAO);

		glPointSize(10);
		glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_INT, (GLvoid*)(0 * sizeof(GLfloat)));
		glDrawElements(GL_POLYGON, 8, GL_UNSIGNED_INT, (GLvoid*)(9 * sizeof(GLfloat)));
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, (GLvoid*)(17 * sizeof(GLfloat)));
		glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_INT, (GLvoid*)(21 * sizeof(GLfloat)));
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, (GLvoid*)(24 * sizeof(GLfloat)));
		glDrawElements(GL_POLYGON, 3, GL_UNSIGNED_INT, (GLvoid*)(28 * sizeof(GLfloat)));
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}