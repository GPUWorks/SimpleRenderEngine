#pragma once
#include "Camera.h"
namespace Core {
	class Effect {//��Ч��ô��ư�����������׼����չ��һ�������ר������д��Ч����Ч�����װ��shader
	public:
		Effect(){}
		virtual ~Effect(){}
	public:
		virtual void init() = 0;
		virtual void render(Camera* camera, int deltaTime) = 0;

	};
}


