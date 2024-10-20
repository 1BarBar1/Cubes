#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h> 

//Vertex source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


int main() 
{
	//intilaze GLFW
	glfwInit();
	//Adressing what version of OpenGl iam using
	//OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW what we are using the CORE ptrofile
	//This means that we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// cordinates for the verticeses
	GLfloat vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	//Crating the window 
	//Where size,name are assigned 
	GLFWwindow* window = glfwCreateWindow(800,800, "Cubes", NULL, NULL);
	//Error handeling if window fails
	if (window == NULL) 
	{
		std::cout << "Window failled" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Introduces the window to current context
	glfwMakeContextCurrent(window);

	//Loading GLAD
	gladLoadGL();


	//Specify the viewport of OpenGl in the window 
	// in this case x = 0, y = 0, to x = 800, y = 800
	glViewport(0,0,800,800);

	//Creating the Vertex Shader and get reffrences with &
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach Vertex Shader source to the Vertex Shader Object 
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compiling the vertex Shader inte mashine code 
	glCompileShader(vertexShader);


	//Creating the Fragment Shader and get reffrences with &
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach Fragment Shader source to the fragment Shader Object 
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//compiling the Fragment Shader inte mashine code 
	glCompileShader(fragmentShader);


	//Crating Shader program Object and get its references 
	GLuint shaderProgram = glCreateProgram();
	//attaching the Vertex shader abnd fragment sheder to the Shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Link all the shaders together into the shader pprogram
	glLinkProgram(shaderProgram);

	//Deletes usles shader programs
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Crates refernce container for the Vertes array object aand the vertex buffer object
	GLuint VAO, VBO, EBO;

	// Genarting the VAO and VBO with only one object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//make the VAO the current vertex array object by bvinding itt
	glBindVertexArray(VAO);

	//Binding the VBO  specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Inturduces the vertuices into VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Binding to EBO to Element array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//configure the Vetex attributes so the OpenGL can read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	//Enabole Vertex attribute so that the openGL knows to use it
	glEnableVertexAttribArray(0);

	//Bind biooth VAO VBO to 0 so that we don't accidentaal modify it
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//Backgruond color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//cleans back buffer and assign collor to it
	glClear(GL_COLOR_BUFFER_BIT);
	//swaps back buffer with front 
	glfwSwapBuffers(window);

	//while loop so window dosen't close
	while (!glfwWindowShouldClose(window)) {
		
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//tell OpwenGL which we ´want to use
		glUseProgram(shaderProgram);
		//Bind the VAO so OpenGL Know to use it
		glBindVertexArray(VAO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	//Deletes 
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//deletes window
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
