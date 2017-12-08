#include "Object.h"
#include "../Math/Vector4D.h"
namespace SRE {

	Object* Object::getParent() {
		if (!_parent)return _parent;
		else
			return NULL;
	}
	void Object::applyMatrix(const Matrix4D& matrix)
	{
		_matrix_local = _matrix_local * matrix;
		_matrix_local.decompose(_position, _scale, _orientation);
	}
	void Object::setRotationFromAxisAngle(const Vector3D& axis, double angle)
	{
		_orientation.setFromAxisAngle(angle, axis);
	}
	void Object::setRotationFromMatrix(const Matrix4D& rotate)
	{
		_orientation.setFromRotationMatrix(rotate);
	}
	void Object::rotateOnAxis(const Vector3D& axis, double angle)
	{
		Quaternion quat;
		quat.setFromAxisAngle(angle, axis);
		_orientation = _orientation * quat;
		//_position = _position * quat;//
	}
	void Object::rotateOnAxisFixedPosition(const Vector3D& axis, double angle)
	{
		Quaternion quat;
		quat.setFromAxisAngle(angle, axis);
		_orientation = _orientation * quat;
		_position = _position * quat;//
	}
	void Object::translateOnAxis(const Vector3D& axis, double distance)
	{
		Vector3D new_axis = axis * _orientation;//得到旋转后的向量
		_position += (distance * new_axis);		
	}
	void Object::localToWorld(Vector3D& vector)
	{
		vector = _matrix_world * vector;
	}
	void Object::worldToLocal(Vector3D& vector)
	{
		Matrix4D matrix_inverse = _matrix_world.getInverse();
		vector = matrix_inverse * vector;
	}
	bool Object::add(Object* object)
	{
		if (!object)return false;
		Object* parent = object->getParent();
		if (parent)
			parent->remove(object);
		object->setParent(this);
		_children.push_back((Object::ptr)object);
		return true;
	}
	bool Object::remove(Object* object)
	{
		for (Children::iterator it = _children.begin();it!=_children.end();it++)
		{
			if (it->get() == object)
			{
				_children.erase(it);
				return true;
			}
				
		}
		return false;
	}
	Object::ptr Object::getChild(int index)
	{
		if (index < _children.size())
			return _children[index];
		return NULL;
	}
	void Object::updateMatrixLocal()
	{
		_matrix_local = Matrix4D::makeTransformMatrix(_position, _scale, _orientation);
	}
	void Object::updateMatrixWorld()
	{
		this->updateMatrixLocal();
		if (this->getParent() == NULL)
			_matrix_world = _matrix_local;
		else
		{
			_matrix_world = _matrix_local * this->getParent()->getWorldMatrix();
		}
		if (_children.size() == 0)return;
		for (auto child : _children)
			child->updateMatrixWorld();
	}

	Matrix4D Object::getLocalMatrix()
	{		
		return _matrix_local;
	}

	Matrix4D Object::getWorldMatrix()
	{		
		return _matrix_world;
	}

	Vector3D Object::getWorldPosition()
	{
		this->updateMatrixWorld();
		//this->_matrix_world.decompose(_position, _scale, _orientation);
		return Vector3D(_matrix_world[12], _matrix_world[13], _matrix_world[14]);
	}

	Quaternion Object::getWorldQuaternion()
	{
		this->updateMatrixWorld();
		this->_matrix_world.decompose(_position, _scale, _orientation);
		return _orientation;
	}

	Vector3D Object::getWorldScale()
	{
		this->updateMatrixWorld();
		this->_matrix_world.decompose(_position, _scale, _orientation);
		return _scale;
	}

}