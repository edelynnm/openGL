#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {

	// Initialize GLFW to use its functionality
	glfwInit();

	// Tell glfw the version of openGL and profile to use
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create glfw window
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL 01", NULL, NULL);

	// Catch null window
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Use window as part of the current context
	glfwMakeContextCurrent(window);

	// Resize window callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Load glad to use OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl; return -1;
	}

	// Define vertices in 3D format
	GLfloat vertices[] =
	{
		-0.5f, -0.5, 0.0f, // bottom left
		0.5f, -0.5, 0.0f, // bottom right
		0.0f, 0.5, 0.0f, // top
	};

	GLuint VAO, VBO;

	// Generate VBA & VBO with 2 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//// Triangle
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Create shader program
	Shader shaderProgram("shader.vs", "shader.fs");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// While GLFW window is not terminated
	while (!glfwWindowShouldClose(window))
	{
		// Listen for input
		processInput(window);

		// RENDER

		// Set color of background in RGBA format
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clear back buffer and assign the new color
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw triangle
		shaderProgram.use();
		shaderProgram.setFloat("offset", 0.5f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	shaderProgram.remove();

	// Delete window before ending program
	glfwDestroyWindow(window);

	// Terminal glfw
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}
