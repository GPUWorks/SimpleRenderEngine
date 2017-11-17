#pragma once
#include "HardwareBuffer.h"

#include<memory>
namespace SRE {

	class HardwareVertexBuffer : public HardwareBuffer
	{
	public:

		virtual void*	lock(size_t offset, size_t length, LockOptions options);
		virtual void*	lock(LockOptions options);
		virtual void	unlock(void);

		virtual void	readData(size_t offset, size_t length, void* dest);
		virtual void	writeData(size_t offset, size_t length, const void* source, bool discardWholeBuffer = false);

		virtual void	copyData(HardwareBuffer& src_buffer, size_t src_offset, size_t dst_offset, size_t length, bool discardWholeBuffer = false);
		virtual void	copyData(HardwareBuffer& src_buffer);

		virtual size_t	getSizeInBytes(void) const;
		virtual Usage	getUsage(void) const;

		virtual bool    isLocked(void) const;
		virtual bool	isSystemMemory(void) const;

		virtual void    upload(void);
	protected:
		GLuint _bufferID;
		size_t _numVertex;
		size_t _vertexSize;

		size_t _sizeInBytes;
		Usage  _usage;
		bool _isLocked;
		void* _data;
	};
}