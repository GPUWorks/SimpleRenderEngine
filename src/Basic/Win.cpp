#include "Win.h"
#include  <iostream>
#include "RenderSystem.h"
namespace Basic {
	Win* Win::m_Inst(0);
	Win* Win::Inst() {
		if (m_Inst)
			m_Inst = new Win();
		return m_Inst;
	}

	bool Win::createWindow(const int& width, const int& height, const char* name)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
														
		GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return false;
		}
		return true;
	}
	void Win::starup(Camera::ptr camera)
	{
		while (!glfwWindowShouldClose(window))
		{
			//��ϣ������Ӧ���и�����������update�����볡���е�entity��������update
			float currentFrame = glfwGetTime();
			RenderSystem::RenderSystem::Inst()->beginRender();
			RenderSystem::RenderSystem::Inst()->render(camera, currentFrame);
			RenderSystem::RenderSystem::Inst()->endRender();
			//deltaTime = currentFrame - lastFrame;
			//lastFrame = currentFrame;
		
			//�¼�������ôдѽ������
			//processInput(window);
			
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}
}