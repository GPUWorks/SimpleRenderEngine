#include "RenderState.h"

namespace SRE {


	RenderState::RenderState()
	{

	}
	void RenderState::setMaterial(Material::ptr material)
	{
		CullFaceMode cfm = material->getCullFaceMode();
		if (cfm == DoubleSide)
			glDisable(GL_CULL_FACE);
		else
		{
			glEnable(GL_CULL_FACE);
			glCullFace(cfm);
		}

		bool transparent = material->getTransparent();
		if (transparent)
		{
			//���û�Ϻ���
			glEnable(GL_BLEND);

		}
		else
		{
			glDisable(GL_BLEND);
		}
		bool depthTest = material->getDepthTest();
		if (depthTest)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
		CompareFunc depthFunc = material->gettDepthFunc();
		if(depthTest)glDepthFunc(depthFunc);

		bool depthWrite = material->getDepthWrite();
		glDepthMask(depthWrite);
		
		bool colorWrite = material->getColorWrite();
		glColorMask(colorWrite, colorWrite, colorWrite, colorWrite);
	}
	
	void RenderState::use()
	{		
		for (auto it = _state_map.begin(); it != _state_map.end(); it++)
		{
			if (it->second)
				glEnable(it->first);
			else
				glDisable(it->first);
		}

		glCullFace(mode);
		glDepthFunc(depthFunc);
		//glStencilFunc(stencilFunc);
	}
}