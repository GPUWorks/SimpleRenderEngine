#include "Camera.h"
#include "../math/MathHelper.h"
#include "../Math/Matrix3D.h"
namespace Core {


	void Camera::lookAt(const Vector3D& target)
	{
		lookAt(_position, target, getUp());
	}
	void Camera::lookAt(const Vector3D& position, const Vector3D target, const Vector3D& up)
	{
		Matrix4D matrix = Matrix4D::lookAt(target, position, up);
		_orientation.setFromRotationMatrix(matrix);

	}	
	Matrix4D Camera::getViewMatrix()const
	{	
		//Ҫ����Ԫ�����棺��Ϊ�������ϵ��xyz�͵�ǰ������Ԫ������������ϵ�෴,��Ϊʲôֱ������Ԫ�����������ϵһ����
		return Matrix4D::lookAt(_position, _position + getDirection(), getUp());
		//return Matrix4D::makeTransformMatrix(_position, Vector3D(1.0), _orientation.Inverse());
	}
	void Camera::ProcessKeyboard(float xoffset, float yoffset)
	{	
		Vector3D direction = getDirection();
		Vector3D right = getRight();
		_position += direction * _movementSpeed * xoffset;		
		_position += right * _movementSpeed * yoffset;
	}

	void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
	{
		xoffset *= _mouseSensitivity;
		yoffset *= _mouseSensitivity;

		///yaw(xoffset);
		//pitch(yoffset);

		if (constrainPitch)
		{
			//if (_pitch > 89.0f)
			//	_pitch = 89.0f;
			//if (_pitch < -89.0f)
			//	_pitch = -89.0f;
		}

	}
}