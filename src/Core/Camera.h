#pragma once
#include "ViewPort.h"
#include "Object.h"
#include "../Math/Matrix4D.h"
#include "../Math/Quaternion.h"
#include "../Math/Vector3D.h"
#include <memory>
namespace Core {

	class Camera 
		:public Object{
	public:
		typedef std::shared_ptr<Camera> ptr;
		Camera() = default;
		Camera(const Camera&) = default;
		Camera(const Vector3D& pos) :Object(pos) {}
		Camera(const Vector3D& pos, const Quaternion& quat) :Object(pos, quat) {}
	public:

		const Quaternion& getOrientation(void) const { return _orientation; }
		void setOrientation(const Quaternion& quat) { _orientation = quat; }
		const Vector3D& getPosition(void) const { return _position; }
		void setPosition(const Vector3D& pos) { _position = pos; }

		Vector3D getDirection(void) const { return _orientation * Vector3D(0, 0, 1); }
		Vector3D getUp(void) const { return _orientation * Vector3D(0, 1, 0); }
		Vector3D getRight(void) const { return _orientation * Vector3D(1, 0, 0); }
		Vector3D zAxis() { return _orientation.zAxis(); }
		void lookAt(const Vector3D& target);
		void lookAt(float x, float y, float z) { lookAt(Vector3D(x, y, z)); }
		void lookAt(const Vector3D& position, const Vector3D target, const Vector3D& up);
		void translate(const Vector3D &v) { _position += _orientation.Inverse() * v; }
		void translate(float x, float y, float z) { _position += _orientation.Inverse() * Vector3D(x, y, z); }

		void rotate(float angle, float x, float y, float z) { rotateOnAxis(Vector3D(x, y, z), angle); }

		void yaw(float angle) {
			rotateOnAxis(_orientation.xAxis(), angle);
			Vector3D dir = getDirection();
		}
		void pitch(float angle) { rotateOnAxis(_orientation.yAxis(), angle); }
		void roll(float angle) { rotateOnAxis(_orientation.zAxis(),angle); }

		Matrix4D getViewMatrix()const;
		virtual Matrix4D getProjectionMatrix() { return Matrix4D::makeIdentity(); }	

		//for mouse and keyboard control
	public:
		void ProcessKeyboard(float xoffset, float yoffset);
		void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
		void setViewPort(ViewPort::ptr vp) { _view_port = vp; }
		ViewPort::ptr getViewPort() { return _view_port; }
		//void ProcessMouseScroll(float yoffset);
	private:
		float _movementSpeed;
		float _mouseSensitivity;
		ViewPort::ptr _view_port;
	};

}

