#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

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

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

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
