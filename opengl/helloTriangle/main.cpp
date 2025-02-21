//#include <chrono>
//#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// shaders
const char *vertexShaderSource = R"glsl(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	void main()
	{
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
)glsl";

//const char *fragmentShaderSource = R"glsl(
//	#version 330 core
//	uniform vec3 triangleColor;
//	out vec4 FragColor;
//	void main()
//	{
//		FragColor = vec4(triangleColor, 1.0f);
//	}
//)glsl";

const char *fragmentShaderSource1 = R"glsl(
	#version 330 core
	out vec4 FragColor;
	void main()
	{
		FragColor = vec4(0.9f, 0.5f, 0.2f, 1.0f);
	}
)glsl";

const char *fragmentShaderSource2 = R"glsl(
	#version 330 core
	out vec4 FragColor;
	void main()
	{
		FragColor = vec4(0.1f, 0.7f, 0.7f, 1.0f);
	}
)glsl";

int main()
{
	//auto t_start = std::chrono::high_resolution_clock::now();
	// configure glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// create glfw window
	// windowed
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
	// fullscreen
	//GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", glfwGetPrimaryMonitor(), NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// load openGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	// shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint shaderProgram1 = glCreateProgram();
	GLuint shaderProgram2 = glCreateProgram();
	
	// vertex shader 
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// fragment shader 1
	glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader1);
	// fragment shader 2
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);
	// link shader 1
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);
	// link shader 2
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

	// delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);
	glDeleteShader(fragmentShader2);

	// vertex and attributes
	float verticesFirstTriangle[] = {
		// First triangle
			-0.33f, 0.5f, 0.0f,  // top1
			-0.66f, -0.3f, 0.0f,  // bottomL
			 0.0f,  -0.3f, 0.0f,  // bottomR
	};

	float verticesSecondTriangle[] = {
			0.33f, 0.5f, 0.0f,  // top2
			0.66f, -0.3f, 0.0f,  // bottomL
			 0.0f,  -0.3f, 0.0f,  // bottomR
	};
	unsigned int indices[] = { 
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
	};  

	// buffer objects to GPU
	GLuint VBOs[2], VAOs[2];//, EBO;
	// create the buffers to send to the GPU
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	//glGenBuffers(1, &EBO);

	// upload the data to the GPU and then configuring

	// vertices VAO 1
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFirstTriangle), verticesFirstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// indices
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// vertices VAO 2
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSecondTriangle), verticesSecondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind VBOs
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// render loop
	//GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
	while(!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		//auto t_now = std::chrono::high_resolution_clock::now();
		//float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		//glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
		glUseProgram(shaderProgram1);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		// show the buffer to window
		glfwSwapBuffers(window);
		// get all the events
		glfwPollEvents();
	}


	// end program
	// opengl
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram1);
	glDeleteProgram(shaderProgram2);
	// glfw
	glfwTerminate();
	return 0;
}

// handle input
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

// Resize view port dynamically
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
