#pragma once
#include "HardwareBuffer.h"
#include <glew\glew.h>
#include<memory>
namespace SRE {

	class HardwareVertexBuffer : public HardwareBuffer
	{
	public:
		typedef std::shared_ptr<HardwareVertexBuffer> ptr;
		HardwareVertexBuffer(size_t vertex_size, size_t num_vertices, HardwareBuffer::Usage usage, bool use_shadow_buffer = false);
		~HardwareVertexBuffer();
	public:

		virtual void*	lock(size_t offset, size_t length, LockOptions options);
		virtual void*	lock(LockOptions options);
		virtual void	unlock(void);

		virtual void	readData(size_t offset, size_t length, void* dest);
		virtual void	writeData(size_t offset, size_t length, const void* source, bool discardWholeBuffer = false);

		//virtual void	copyData(HardwareBuffer& src_buffer, size_t src_offset, size_t dst_offset, size_t length, bool discardWholeBuffer = false);
		//virtual void	copyData(HardwareBuffer& src_buffer);

		virtual size_t	getSizeInBytes(void) const { return _sizeInBytes; }
		virtual Usage	getUsage(void) const { return _usage; }

		virtual bool    isLocked(void) const { return _isLocked; }
		virtual bool	isUseShadowBuffer(void) const { return _useShadowBuffer; }
		virtual void    upload(void);
		GLuint  getBufferID() { return _verexBufferID; }
		unsigned int getVertexSize() { return _vertexSize; }
		unsigned int getVertexNum() { return _numVertices; }
	protected:
		GLuint _verexBufferID;//vbo
		size_t _numVertices;//
		size_t _vertexSize;

		size_t _sizeInBytes;
		Usage  _usage;
		bool _isLocked;
		bool _useShadowBuffer;
		unsigned char* _data;

		//从内存池取数据
		bool   _lockFromPool;
		size_t _scrachSize;
		size_t _scrachOffset;
		void * _scrachPtr;

		size_t _lockSize;
		size_t _lockStart;
		
		bool _scratchNeedUpload;
	};
}