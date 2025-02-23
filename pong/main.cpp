#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"
#include "shader.hpp"

#include <include/glad.h>
#include <GLFW/glfw3.h>

#include <include/glm/glm.hpp>
#include <include/glm/gtc/matrix_transform.hpp>
#include <include/glm/gtc/type_ptr.hpp>

#include <iostream>

//void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);


const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;


glm::mat4 speed = glm::mat4(1.0f);


int main()
{
	// glfw stuff
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,"OpenGL", NULL, NULL);



	if (window == NULL) {
		std::cout << "Error while creating GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// load opengl funcs ponters
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shader1("shaders/vertexShader.glsl", "shaders/color.glsl");

	// figure
	GLfloat vertices[] = {
		-.1f, -.1f, 0.0f,		0.0f, 0.0f, 0.0f,
		-.1f, .1f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.1f, -.1f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.1f, .1f, 0.0f,			0.0f, 0.0f, 0.0f,
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 1,
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


		// Transformations
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));


		// Shader operations
		shader1.use();
		GLuint moveSpeedLoc = glGetUniformLocation(shader1.ID, "moveSpeed");
		glad_glUniformMatrix4fv(moveSpeedLoc, 1, GL_FALSE, glm::value_ptr(speed));
		//GLuint transformLoc = glGetUniformLocation(shader1.ID, "transform");
		//glad_glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

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


	GLfloat movement = 0.02;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		speed = glm::translate(speed, glm::vec3(0.0, movement, 0.0));
	} 
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		speed = glm::translate(speed, glm::vec3(0.0, -movement, 0.0));
	} 
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		speed = glm::translate(speed, glm::vec3(-movement, 0.0, 0.0));
	} 
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		speed = glm::translate(speed, glm::vec3(movement, 0.0, 0.0));
	} 

}


