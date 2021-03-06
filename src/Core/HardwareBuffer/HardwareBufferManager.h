#pragma once
#include <glew\glew.h>
#include "HardwareBuffer.h"
#include "HardwareIndexBuffer.h"
#include "HardwareVertexBuffer.h"
#include "VertexDeclaration.h"
#include "VertexBufferBinding.h"
namespace SRE {


	#define DefaultMapBufferThreshold (1024 * 32)//向内存池申请阈值
	//32位结构（位域）
	struct BufferAlloc
	{
		/// Size in bytes
		unsigned int size : 31;
		/// Free? (pack with size)
		unsigned int free : 1;
	};

	#define POOLSIZE 1 * 1024 * 1024
	#define ALIGNMENT 32

	class HardwareBufferManager {
	public:
		HardwareBufferManager();
		~HardwareBufferManager();
	public:
		static HardwareBufferManager& getSingleton(void);
		static HardwareBufferManager* getSingletonPtr(void);
		

		HardwareIndexBuffer::ptr
			createIndexBuffer(HardwareIndexBuffer::IndexType itype, unsigned int num_indexes,
				HardwareBuffer::Usage usage, bool use_shadow_buffer = false);
		HardwareVertexBuffer::ptr createVertexBuffer(rsize_t vertex_size, rsize_t num_verts, HardwareBuffer::Usage usage,
			bool use_shadow_buffer = false);
		VertexDeclaration::ptr createVertexDeclaration(void);

		void destroyVertexDeclaration(VertexDeclaration::ptr decl);

		VertexBufferBinding::ptr createVertexBufferBinding(void);

		void destroyVertexBufferBinding(VertexBufferBinding::ptr binding);

		size_t getMapBufferThreshold() { return DefaultMapBufferThreshold; }
		void* allocate(size_t size);
		void deallocate(void* ptr);
		static GLenum getGLUsege(unsigned int usage);
		static GLenum getGLType(unsigned int type);
	
		
	protected:
		static HardwareBufferManager* _singleton;
		char* _bufferpool;

	};
}