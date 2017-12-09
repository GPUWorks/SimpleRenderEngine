#include "DirectionLight.h"
#include <sstream>
namespace SRE {

	void DirectionLight::upload(Shader* shader)
	{
		//according to number,create uniform name,directionLights[number]

		std::stringstream ss;
		std::string number;
		ss << _number;
		ss >> number;
		std::string uniform_name_pre = "directionLights[].";
		if (_number < 10)
			uniform_name_pre.insert(16, number, 0, 1);
		else
			uniform_name_pre.insert(16, number, 0, 2);

		shader->use();

		std::string direction = uniform_name_pre + "direction";
		shader->setVec3(direction.c_str(), _uniform.direction);

		std::string color = uniform_name_pre + "color";
		shader->setVec3(color.c_str(), _uniform.color);		

		std::string shadow = uniform_name_pre + "shadow";
		shader->setBool(shadow.c_str(), _uniform.shadow);

		std::string shadowBias = uniform_name_pre + "shadowBias";
		shader->setFloat(shadowBias.c_str(), _uniform.shadowBias);

		std::string shadowRadius = uniform_name_pre + "shadowRadius";
		shader->setFloat(shadowRadius.c_str(), _uniform.shadowRadius);

		std::string shadowMapSize = uniform_name_pre + "shadowMapSize";
		shader->setVec2(shadowMapSize.c_str(), _uniform.shadowMapSize);

		shader->unUse();
	}
}