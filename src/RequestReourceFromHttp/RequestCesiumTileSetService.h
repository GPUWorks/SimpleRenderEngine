#pragma once
#include "../Core/Object.h"
#include "rapidjson/document.h"
namespace SRE {

	/*
	����Cesium������3D tilsetģ�ͷ���
	example url = "https://beta.cesium.com/api/assets/1458/"
	������̣� 1.������tileset.json�ļ��õ��ڵ�����Ϣ
			   2.����json�ļ����ڵ��Լ��ӽڵ���Ϣ�õ����ڵ�����url
	*/
	class Request3DTileSet {

	public:

		Object* requestFromUrl(const char* url);

	};
}