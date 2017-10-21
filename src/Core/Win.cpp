#include <glew\glew.h>
#include "Win.h"
#include  <iostream>
#include "RenderSystem.h"
using namespace Utils;
namespace Core {
	
	Win* Win::instance(0);
	Win* Win::getSingleton() {
		if (!instance)
			instance = new Win();
		return instance;
	}
	std::vector<mouse_event> mouse_events;
	Keys keyboard_events;
	bool button_down = false;
	bool Win::create(const int& width, const int& height, const char* name)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glViewport(0, 0, width, height);
		window = glfwCreateWindow(width, height, name, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(window);
		//��ʼ��glew
		glewExperimental = GL_TRUE;
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error: " << error << std::endl;
		}
		GLenum glewinit = glewInit();
		if (glewinit != GLEW_OK) {
			std::cout << "Glew not okay! " << glewinit;
			exit(EXIT_FAILURE);
		}

		glfwSetCursorPosCallback(window, cursorPositionCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);	

		
	}
	void Win::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
	{
		if (!button_down)return;
		mouse_event event;
		double seconds = glfwGetTime();
		event.mouse_status = M_MOVE;
		event.time = seconds;
		event.xpos = xpos;
		event.ypos = ypos;
		mouse_events.push_back(event);
	}
	void Win::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
	{
		mouse_event event;
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		double seconds = glfwGetTime();
		event.mouse_status = MOUSE_NONE;
		event.time = seconds;
		event.xpos = xpos;
		event.ypos = ypos;
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			event.mouse_status = LB_DOWN;
			button_down = true;
		}
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
		{
			event.mouse_status = MB_DOWN;
			button_down = true;
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT  && action == GLFW_PRESS)
		{
			event.mouse_status = RB_DOWN;
			button_down = true;
		}
		else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		{
			event.mouse_status = LB_UP;
			button_down = false;
		}
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
		{
			event.mouse_status = MB_UP;
			button_down = false;
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT  && action == GLFW_RELEASE)
		{
			event.mouse_status = RB_UP;
			button_down = false;
		}

		if (event.mouse_status != MOUSE_NONE)
			mouse_events.push_back(event);

		glfwSwapBuffers(window);



	}
	void Win::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		char* event_name = "keyboard.event";
		Event::ptr event = EventManager::Inst()->createEvent();
		event->setName(event_name);
		event->setValue(event_name, '0');
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
			event->setValue(event_name, 'W');
			EventManager::Inst()->sendEvent(event);

		}
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			event->setValue(event_name, 'A');
			EventManager::Inst()->sendEvent(event);
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
			event->setValue(event_name, 'S');
			EventManager::Inst()->sendEvent(event);
		}
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
			event->setValue(event_name, 'D');
			EventManager::Inst()->sendEvent(event);
		}
	}
	void Win::framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	void Win::processInput()
	{
		unsigned int num_events = mouse_events.size();
		if (mouse_events.size() > 0)
		{
			Event::ptr event = EventManager::Inst()->createEvent();
			mouse_event_vector xx;
			xx._mouse_events = &mouse_events[0];//mouse_events;
			xx._event_num = num_events;
			event->setName("mouse.event");
			event->setValue("mouse.event", xx);
			EventManager::Inst()->sendEvent(event);
		}
		mouse_events.clear();
	}
	void Win::startRenderLoop()
	{
		while (!glfwWindowShouldClose(window))
		{			
			processInput();			
			_render_system->render();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}
}