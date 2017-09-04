#ifndef WIN_H
#define WIN_H
#include "Camera.h"
#include <glfw3.h>
namespace Basic {//ʱ����ô�ӽ�������glfw���о�һ��
	class Win {
	public:
		static Win* Inst();
		bool createWindow(const int& width = 800, const int& height = 600, const char* name = "SimpleRenderEngine v1.0");
		void starup(Camera::ptr camera);
	public:
		GLFWwindow* window;
		static Win* m_Inst;
	};
}
#endif // !WIN_H
