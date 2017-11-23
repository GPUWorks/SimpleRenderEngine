#pragma once
#include <memory>
#include "Camera.h"
namespace SRE {
	class Scene;
	class Plugin {

	public:
		typedef std::shared_ptr<Plugin> ptr;
		virtual void init() = 0;//����shader������uniform������
		virtual void render(Camera* camera) = 0;
	};
}