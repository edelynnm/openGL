#include<filesystem>
namespace fs = std::filesystem;
#include <string>
using namespace std;
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"Shader.h"
#include"Texture.h"
#include"VBO.h"
#include"EBO.h"
#include"VAO.h"

float zoomlvl = 1.0f;

// Define vertices in 3D format
GLfloat vertices[] =
{
	// positions			// colors				// texture coords
	0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f, // top right 
	0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // bottom right 
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f, // bottom left 
	-0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 1.0f, // top left
};

unsigned int indices[] = {
	3, 0, 1, // first triangle
	1, 2, 3  // second triangle
};

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
		std::cout << "Failed to initialize GLAD" << std::endl; 
		return -1;
	}


	// Create shader program
	Shader shaderProgram("shader.vs", "shader.fs");

	VAO VAO1;
	VAO1.Bind();
	
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texPath = "/Assets/";

	// TEXTURE
	Texture wall((parentDir + texPath + "wall.jpg").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE, GL_REPEAT, GL_NEAREST);
	
	wall.texUnit(shaderProgram, "texture1", 0);
	
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

		shaderProgram.SetFloat("zoomlvl", zoomlvl);

		// Draw triangle
		wall.Bind(GL_TEXTURE0);

		shaderProgram.Use();
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	wall.Delete();

	shaderProgram.Remove();

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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { 
		glfwSetWindowShouldClose(window, true); 
	}


	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		zoomlvl += 0.01f;
	} 
	
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && zoomlvl > 0.2) {
		zoomlvl -= 0.01f;
	}
}
