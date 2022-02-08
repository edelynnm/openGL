#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.988f, 0.427f, 0.149f, 1.0f);\n"
"}\n\0";


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
		0.0f, -0.95, 0.0f, // 0
		-0.95f, -0.1, 0.0f, // 1
		-0.850f, 0.25f, 0.0f, //2
		-0.65f, 0.95f, 0.0f, // 3
		-0.315f, 0.25f, 0.0f, // 4 
		0.315f, 0.25f, 0.0f, // 5
		0.65f, 0.95f, 0.0f, // 6
		0.850f, 0.25f, 0.0f, // 7
		0.95f, -0.1f, 0.0f, // 8
	};

	GLuint indices[] = {
		0, 1, 2,
		0, 2, 7,
		0, 2, 3,
		0, 8, 7,
		0, 7, 6 
	};

	//Create vertex shader object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach vertex shader source to vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile vertex shader into machine code
	glCompileShader(vertexShader);

	int success; 
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); 
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Create fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach fragment shader source to vertex shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile fragment shader into machine code
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	// handle error
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create shader program
	GLuint shaderProgram = glCreateProgram();

	// Attach shader objects to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//Link all shaders into shader program
	glLinkProgram(shaderProgram);

	// handle errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete shaders since they are now in the shaders program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	 
	// Create reference containers for VBA & VBO
	GLuint VAO, VBO, EBO;

	// Generate VBA & VBO with 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Use VAO by binding it
	glBindVertexArray(VAO);

	// copy vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// Set vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// To avoid accidentally changing the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

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
