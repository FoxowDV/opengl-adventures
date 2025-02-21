#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);


const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;


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

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

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


