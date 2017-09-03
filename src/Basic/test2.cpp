//����Ԫ��ʹ��
#include<iostream>

#include <glew/glew.h>
#include "Shader.h"
#include "TextureManager.h"
// GLFW
#include <glfw3.h>

#include<FreeImage.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace RenderSystem;
using namespace std;
// ����ԭ��
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window �ߴ�
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW ��ʼ����GLFW
	glfwInit();
	// Set all the required options for GLFW ����GLFWҪ�����õ�ѡ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions ����һ��GLFWwindow object that can use for GLFW's
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions ���ûص�����
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a 
	//modern approach to retrieving function pointers and extensions ����Ϊtrue �����ڵķ����ָ�������ָ�����չ
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers  ��ʼ��GLEW ȥ����opengl�ĺ���ָ��
	glewInit();

	// Define the viewport dimensions ������ͼ�ߴ�
	glViewport(0, 0, WIDTH, HEIGHT);


	// Build and compile our shader program    �����ͱ������ǵ���Ⱦ����
	glewInit();
	Shader ourShader("../../../src/Data/shader/test.fs", "../../../src/Data/shader/test.vs");


	// Set up vertex data (and buffer(s)) and attribute pointers  ���ö������ݺ�ָ������
	GLfloat vertices[] = {
		// Positions   λ��       // Colors  ��ɫ         // Texture Coords  ��������
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0! ��ע���ǿ�ʼ��0
		0, 1, 3, // First Triangle ��һ��������
		1, 2, 3  // Second Triangle�ڶ���������
	};
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute  λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute  ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute   ������������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO ���VAO


						  // Load and create a texture   ���غʹ�������
	TextureManager::Inst()->LoadTexture("../../../src/Data/texture/1.jpg", 0);
	TextureManager::Inst()->LoadTexture("../../../src/Data/texture/1.jpg", 1);
	


	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		//������¼������̺����ȵȣ�������Ӧ����Ӧ����
		glfwPollEvents();

		// Render ��Ⱦ
		// Clear the colorbuffer  �����ɫ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Bind Textures using texture units  ������ ʹ������Ԫ
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 1);
		//glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
		ourShader.setInt("ourTexture1", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 2);
		ourShader.setInt("ourTexture2", 1);

		// Activate shader ������Ⱦ
		ourShader.use();

		// Create transformations ����ת��
		glm::mat4 transform; //����һ����λ����
		//transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));//�ƶ�
		//transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 0.0f, 1.0f));//��ת

																										// Get matrix's uniform location and set matrix  �õ�����uniform λ�ò������þ��󣬽��������õ����ݴ�����ɫ��
																										//��������uniform�����ĵ�ַ��Ȼ����glUniform�����Ѿ������ݷ��͸���ɫ�������������һ��Matrix4fv�ĺ�׺
																										//��һ�������ͱȽ���Ϥ�ˣ�����uniform�ĵ�ַ���ڶ�����������Opengl���ٸ����󱻷��͹�ȥ��Ŀǰ��1
																										//����������ѯ�����������Ƿ�ϣ���Ծ�������û���������Ѿ������ת��Ϊ�С�penGLʹ�õ��ڲ��ľ��󲼾ֽ�������Ϊ��˳��column-major ordering�����֡�
																										//GLM�Ѿ���������Ϊ��˳���������ľ������Բ�����Ҫ�û��������ǿ�����ΪGL_FALSE�����һ��������ʵ�ʵľ������ݣ�����GLM�����ǰ����ǵľ��󴢴�ΪOpenGL��ϣ�������֣�
																										//�������Ҫ����GLM���ڽ�����value_ptr���任��Щ���ݡ�
		//GLint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		ourShader.setMat4("transform", transform);
		// Draw container  ������
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap the screen buffers ������Ļ�Ļ���
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose  �ʵ��ĵ��ͷ���Դ
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.��ֹGLFW��������е�ͨ��GLFW�������Դ
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}