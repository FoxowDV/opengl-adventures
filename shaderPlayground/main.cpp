#include "shader.hpp"

#include <include/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <ratio>
#include <thread>
#include <chrono>
#include <vector>

std::vector<float> cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


int main()
{
	// glfw stuff
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	//glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	int count;
	GLFWmonitor ** monitors = glfwGetMonitors(&count);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", monitors[1], NULL);



	if (window == NULL) {
		std::cout << "Error while creating GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// load opengl funcs ponters
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

//	Shader shader2("shaders/vertexShader.glsl", "shaders/shadertoy.glsl");

	// figure
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0,
	};


	GLuint VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Vertices
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Position attibute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Bind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)) {
		// Input
		processInput(window);

		// Render things
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Shader operations
		//shader1.use();
		Shader shader1("shaders/vertexShader.glsl", "shaders/fragment.glsl");
		shader1.use();

		// passing uniforms
		// Resolution
		std::vector<int> res(2);
		glfwGetWindowSize(window, &res[0], &res[1]);
		std::vector<GLfloat> resolution(res.begin(), res.end());
		GLuint resolutionLoc = glGetUniformLocation(shader1.ID, "u_resolution");
		glUniform2fv(resolutionLoc, 1, &resolution[0]);

		// MousePos
		std::vector<double> mouseD(2);
		glfwGetCursorPos(window, &mouseD[0], &mouseD[1]);
		std::vector<GLfloat> mouse(mouseD.begin(), mouseD.end());
		GLuint mousePos = glGetUniformLocation(shader1.ID, "u_mouse");
		glUniform2fv(mousePos, 1, &mouse[0]);
		
		// Clock
		shader1.setFloat("u_time", glfwGetTime());

		// Render forms
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return 0;
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	} else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}


std::vector<float> cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	return std::vector<float> {static_cast<float>(xpos), static_cast<float>(ypos)};

}
