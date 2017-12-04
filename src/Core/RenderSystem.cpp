#include "RenderSystem.h"
#include "RenderState.h"
#include "ShadowMapPlugin.h"
#include "ShaderManager.h"
#include "../Utils/CamerControl.h"
#include "../Utils/Event.h"
#include "../Utils/UtilsHelp.h"
#include "../Material/ShaderMaterial.h"
using namespace Utils;
#include <iostream>
namespace SRE {
	
	RenderSystem::RenderSystem(Scene* scene, Camera* camera)
	{
		_scene = (Scene::ptr)scene;
		_camera = (Camera::ptr)camera;
		//ע���������¼����������
		CameraControl::ptr cc = make_shared<CameraControl>(camera);
		EventManager::Inst()->registerReceiver("mouse.event", cc);
		EventManager::Inst()->registerReceiver("keyboard.event", cc);
	}
	
	void RenderSystem::render()
	{	
		beforeRender();
		renderImpl();
		afterRender();
	}
	void RenderSystem::beforeRender()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
	}
	void RenderSystem::renderImpl()
	{
		if (_camera == NULL)
		{
			std::cout << "no camera" << std::endl;
			return;
		}
		Object::ptr root = _scene->getSceneRoot();
		root->updateMatrixWorld();

		if (_camera->getParent())_camera->updateMatrixWorld();

		_frustum.setFromMatrix(_camera->getProjectionMatrix()*_camera->getViewMatrix());

		projectObject(root);

		//sort();

		if (/*_enable_shadow*/)
		{
			//ShadowMapPlugin* sp = new ShadowMapPlugin(_lights, _render_mesh);
			//sp->render(camera);			
		}
		Skybox* skybox = _scene->getSkybox();
		if (skybox)
			skybox->render(_camera.get());
		else
		{
			//clear color
		}

		if (_opaqueMehss.size()>0) renderMeshs(_opaqueMehss);

		// transparent pass (back-to-front order)

		if (_transparentMeshs.size()>0) renderMeshs(_transparentMeshs);
		//_scene->render(_camera.get());
	}
	void RenderSystem::renderMeshs(std::vector<Mesh::ptr> meshs)
	{
		for (auto mesh : meshs)
		{
			Material::ptr material = mesh->getMaterial();
			RenderState::setMaterial(material);//���û���ǰ�Ļ���

			//Ȼ��Ҫ���shader ��ȡ--> uniformֵ����----> ��������----> draw
			Material::MaterialType mt = material->getType();
			Shader::ptr shader;
			switch (mt)
			{
			case Material::Basic:
			{
				break;
			}
			case Material::Phong:
			{

				break;
			}
			}
			//Shader::ptr shader = getMaterialShader


		}
	}
	void RenderSystem::setProgram(Mesh::ptr mesh)
	{
		//��һ��ȫ�ֵ�uniforms�洢���е�uniform��Ϣ,���Ӧ�÷ֳ�need update��no need update������ǵ�һ֡��Ҫ����shader �� uniforms������ǵڶ�֡��ʼ��ֻ��Ҫ����uniforms��Ҫ���µ�ֵ��uniformӦ������shader�ڲ���Ӧuniform����
		Material::ptr material = mesh->getMaterial();
		Shader::ptr shader = material->getShader();
		if (NULL == shader)
		{
			//update
			shader->setMat4("viewMatrix", _camera->getViewMatrix());
			shader->setMat4("projectionMatrix", _camera->getProjectionMatrix());
			shader->setVec3("cameraPosition", _camera->getPosition());
			//������Ϣ��θ���
			

			return;
		}
		//������Ԥ������Ϣ��Ȼ���벻ͬ���ʶ�Ӧ��shader��������õ�������shader��Ȼ����б��룬����material��ֵ�ϴ���shader
		//Shader::ptr shader = getShader(material->getType());

		//shader->use();
		//��װshader
		std::string prefixVertex;// = vertex_attribute;
		if (material->getFog())
		{
			prefixVertex += "#define USE_FOG\n";
		}
		if (material->getMap())
		{
			prefixVertex += "#define USE_MAP\n";
		}
		if (material->getLightMap())
		{
			prefixVertex += "#define USE_LIGHTMAP\n";
		}
		if (material->getDisplacementMap())
		{
			prefixVertex += "#define USE_DISPLACEMENTMAP\n";
		}
		if (_scene->hasShadow() && mesh->getReceiveShadow())
		{
			prefixVertex += "#define USE_SHADOWMAP\n";
		}
		//if(material->)

		Material::MaterialType type = material->getType();
		switch (type) {
		case Material::Basic: {


			break;
		}

		case Material::Phong: {

			std::string shader_vertex = prefixVertex + readFileToStr("../../../src/Data/shader/phongMaterial.vs");

			std::string shader_fragment = prefixVertex + readFileToStr("../../../src/Data/shader/phongMaterial.fs");

			Shader::ptr shader = std::make_shared<Shader>();

			shader->load(shader_vertex.c_str(), shader_fragment.c_str());
			
			//shader->addUniform();

			break;

		}
		}
		
		if (true)
		{
			//vertex_shader += "#define SHADOW_MAP\n";
		}
		std::string fragment_shader;

		//��װuniform
		Matrix4D viewMatrix = _camera->getViewMatrix();
		Matrix4D projectionMatrix = _camera->getProjectionMatrix();

		//shader->setMat4("viewMatrix", viewMatrix);
		//shader->setMat4("projectionMatrix", projectionMatrix);

		
	}
	/*
	
	*/
	void RenderSystem::setMaterial(Material::ptr material)
	{
		Shader::ptr shader = material->getShader();

		
	}
	Shader::ptr RenderSystem::getShader(Material::MaterialType type)
	{
		Shader::ptr shader;
		switch (type)
		{
		case Material::Basic:
		{
			shader = make_shared<Shader>("../../../src/Data/shader/basic.vs", "../../../src/Data/shader/basic.fs");
			break;
		}
		case Material::Phong:
		{
			shader = make_shared<Shader>("../../../src/Data/shader/phong.vs", "../../../src/Data/shader/phong.fs");
			break;
		}
		}
		return shader;
	}
	void RenderSystem::projectObject(Object::ptr object)
	{
		//if (object->visible = false)return;
		if (object->asMesh())
		{
			Mesh* mesh = object->asMesh();
			if (_frustum.intersectsSphere(*mesh->getBoundSphere().get()))
			{
				Material::ptr material = mesh->getMaterial();
				if (material->getTransparent())
				{
					_transparentMeshs.push_back((Mesh::ptr)mesh);
				}
				else
				{
					_opaqueMehss.push_back((Mesh::ptr)mesh);
				}
			}				

		}
		else if (object->asLight())
		{
			Light* light = object->asLight();
			_lights.push_back((Light::ptr)light);
			if (light->getCastShadow())
				_shadow_lights.push_back((Light::ptr)light);

		}
		else if (object->asPlugin())
		{

		}
		else if (/*object->asSprite()*/)
		{

		}
		else if (object->asBillboardCollection())
		{
			//BillboardCollection* bbc = object->asBillboardCollection();
			//bbc->init();
			//_plugins.push_back(bbc);
		}
		else if (/*object->asParticleSystem()*/)
		{

		}
		else
		{

		}
		unsigned int count = object->getChildCount();
		for (int i = 0; i < count; i++)
		{
			Object::ptr child = object->getChild(i);
			projectObject(child);
		}	
	}
	void RenderSystem::resize(int x, int y, int width, int height)
	{
		ViewPort::ptr vp = _camera->getViewPort();
		vp->setViewport(x, y, width, height);
	}
	void RenderSystem::afterRender()
	{
		//_render_mesh.clear();
		//_lights.clear();

	}		
}