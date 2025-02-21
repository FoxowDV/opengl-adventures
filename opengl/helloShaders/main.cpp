//#include <chrono>
#include "include/shader.h"

#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



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
  Shader ourShader1("shaders/vertexShader.glsl", "shaders/rainbow.glsl");

  // vertex and attributes

  float verticesTriangle[] = {
	  // positions	    // colors
      0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,    // top2
      1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottomR
      -1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f    // bottomL
  };

  // buffer objects to GPU
  GLuint VBO, VAO;
  // create the buffers to send to the GPU
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // upload the data to the GPU and then configuring

  // vertices VAO
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle), verticesTriangle, GL_STATIC_DRAW);
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),  (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // unbind VBOs
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // render loop
  while(!glfwWindowShouldClose(window))
  {
    // input
    processInput(window);

    // render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw triangle
    ourShader1.use();
    ourShader1.setFloat("u_time", glfwGetTime());
    ourShader1.setFloat("width", 800.0f);
    ourShader1.setFloat("height", 800.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //float timeValue = glfwGetTime();
     // float greenValue = (sin(timeValue) /2.0f) + 0.5f;
    //glUniform4f(uniColor, 0.0f, greenValue, 0.0f, 1.0f);
    glBindVertexArray(0);


    // show the buffer to window
    glfwSwapBuffers(window);
    // get all the events
    glfwPollEvents();
  }


  // end program
  // opengl
  glDeleteVertexArrays(2, &VAO);
  glDeleteBuffers(2, &VBO);
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
