#pragma once
#include <windows.h>
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4D.h"

#define math_tolerance 1e-14
#define math_tolerancef 1e-6
#define math_pi     3.14159265358979323846
#define math_two_pi     6.28318530717958647692
#define math_half_pi     (math_pi*0.5)
#define math_quarter_pi     (math_pi*0.25)
namespace Math {

	
	class MathHelper {

	public:		
		template<class T>
		static T lerp(T t1, T t2, float factor)
		{
			return t1 * (1 - factor) + t2 * factor;
		}

		static double radian(float degrees)
		{
			return degrees * 0.01745329251994329576923690768489;
		}

		static UINT ColorTo32(const Vector3D& color) {
			BYTE red = 255 * color[0];
			BYTE green = 255 * color[1];
			BYTE blue = 255 * color[2];
			return (UINT)((BYTE)blue | (WORD)((BYTE)green << 8) | (DWORD)((BYTE)red << 16));
		}
		static bool Clip(Vector4D v)
		{
			if (v.x >= -v.w && v.x <= v.w && v.y >= -v.w && v.y <= v.w &&
				v.z >= -v.w && v.z <= v.w)
				return true;
			return false;
		}
		static void ToNDC(Vector4D& v)
		{
			v.x /= v.w;
			v.y /= v.w;
			v.z /= v.w;
			v.w = 1;
		}
		static bool cullFace(Vector3D camPos, Vector3D v1, Vector3D v2, Vector3D v3)
		{
			//Ĭ��˳ʱ��
			Vector3D v12 = v2 - v1;
			Vector3D v23 = v3 - v2;
			
			Vector3D dir = v12.cross(v23);
		
			Vector3D viewDir = v1 - camPos;
			if (dir.dot(viewDir) < 0)
			{
				return true;
			}
			return false;
		}
		static Vector3D unProject(const Matrix4D& view, const Matrix4D& projection, const Vector3D& vec);
		static Vector3D project(const Matrix4D& view, const Matrix4D& projection, const Vector3D& vec);		
	};
}