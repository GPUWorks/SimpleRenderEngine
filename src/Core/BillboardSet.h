#pragma once


#include "RenderObject.h"
#include "Billboard.h"
namespace SRE {

	/** ���뷽ʽ */
	enum BillboardOrigin
	{
		BBO_TOP_LEFT,
		BBO_TOP_CENTER,
		BBO_TOP_RIGHT,
		BBO_CENTER_LEFT,
		BBO_CENTER,
		BBO_CENTER_RIGHT,
		BBO_BOTTOM_LEFT,
		BBO_BOTTOM_CENTER,
		BBO_BOTTOM_RIGHT
	};
	
	enum BillboardRotationType
	{
		/// Rotate the billboard's vertices around their facing direction
		BBR_VERTEX,
		/// Rotate the billboard's texture coordinates
		BBR_TEXCOORD
	};
	enum BillboardType
	{
		///һֱ����������Ĳ����
		BBT_POINT,
		/// Y����ͳһ�ķ���
		BBT_ORIENTED_COMMON,
		/// Y�����Լ����õķ���
		BBT_ORIENTED_SELF,
		///X��Y����ͳһ��direction��up�������
		BBT_PERPENDICULAR_COMMON,
		/// ��������Լ����õ�direction��ֱ
		BBT_PERPENDICULAR_SELF
	};
	class Camera;
	class BillboardSet : public RenderObject {

	public:
		BillboardSet(unsigned int poolSize = 10);
		~BillboardSet();
		void update(size_t renderSize);
		Billboard* createBillboard(const Vector3D& position, const Vector3D& color = Vector3D(1.0,1.0,1.0));

		Billboard* getBillboard(unsigned int index) const;
		void removeBillboard(unsigned int index);
		void removeBillboard(Billboard* pBill);
		void setBillboardOrigin(BillboardOrigin origin) { _originType = origin; }
		BillboardOrigin getBillboardOrigin() const { return _originType; }
		void setBillboardRotationType(BillboardRotationType rotationType) { _rotationType = rotationType; }
		BillboardRotationType getBillboardRotationType() const { return _rotationType; }
		void setDefaultWidth(float width) { _defaultWidth = width; }
		float getDefaultWidth() const { return _defaultWidth; }
		void setDefaultHeight(float height) { _defaultHeight = height; }
		float getDefaultHeight() const { return _defaultHeight; }
		void setBillboardType(BillboardType bbt) { _billboardType = bbt; }
		BillboardType getBillboardType(void) const { return _billboardType; }
		void setCommonDirection(const Vector3D& vec) { _commonDirection = vec; }
		const Vector3D& getCommonDirection(void) const { return _commonDirection; }
		void setCommonUpVector(const Vector3D& vec) { _commonUpVector = vec; }
		const Vector3D& getCommonUpVector(void) const { return _commonUpVector; }
	protected:
		void beginUpdate(size_t numBillboards);
		void endUpdate();
		virtual void createBuffer();
		void updateBillboard(const Billboard& billboard);
		bool visibleBillboard(Camera* camera, const Billboard& billboard);
		//����BillboardOrigin���뷽ʽ��ȡƫ����Ϣ
		void getParametricOffsets(float& left, float& right, float& top, float& bottom);
		void genBillboardAxes(Vector3D* pX, Vector3D *pY, const Billboard* bb = 0);
		//��Ҫ�Ǹ���billboard��ƫ����Ϣ�������ĸ��ǵĶ���ƫ����Ϣ
		void genVertOffsets(float left, float right, float top, float bottom, float width, float height, const Vector3D& x, const Vector3D& y, Vector3D* outVec);
		void genVertices(const Vector3D* const offsets, const Billboard& pBillboard);
		
	
	protected:
		//���ݵ�ǰbillboardˢ��buffer
		float * _lockData;
		HardwareVertexBuffer::ptr _vertexBuffer;
		
		BillboardType _billboardType;
		BillboardRotationType _rotationType;
		BillboardOrigin _originType;

		size_t _maxSize;
		size_t _currentNumVisible;//��ǰ֡�ɻ��Ƶ�����

		float _leftOff, _rightOff, _topOff, _bottomOff;

		unsigned int _defaultWidth, _defaultHeight;//ÿ��bb��С��һ��ʱ����Ĭ��ֵ
		bool _useDefaultSize;

		typedef std::vector<Billboard::ptr> BillboardList;
		BillboardList _billboards;

		typedef std::vector<Texture::ptr> TextureSet;//���ÿ��billboard����һ��
		TextureSet _textureSet;

		Camera* _currentCamera;
		
		bool _pointRender;//�Ƿ��ǵ���Ʒ�ʽ
		bool _useDefaultOriention;//�Ƿ���Ĭ�ϵķ���
		bool _accurateFacing;//��׼�������

		Vector3D _xAxis, _yAxis;
		Vector3D _offsets[4];

		Vector3D _commonDirection, _commonUpVector;

	};
}