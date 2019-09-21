#include "mvpch.h"
#include "Buffer.h"

#include <glad.h>



namespace MV {


	static GLenum ConvertUsage(BufferUsage usage) {
		switch (usage) {

			case BufferUsage::Static:
				return GL_STATIC_DRAW;

			case BufferUsage::Dynamic:
				return GL_DYNAMIC_DRAW;

		}


		MV_Assert(false, "Invalid bufferusage type!");
	}

	static GLenum ConvertType(IndexBuffer::BufferType usage) {
		switch (usage) {

			case IndexBuffer::BufferType::Char:
				return GL_UNSIGNED_BYTE;

			case IndexBuffer::BufferType::Short:
				return GL_UNSIGNED_SHORT;

			case IndexBuffer::BufferType::Int:
				return GL_UNSIGNED_INT;

		}


		MV_Assert(false, "Invalid buffertype!");
	}



	static unsigned int CalculateSize(unsigned int count, unsigned int type) {
		switch (type) {
			case GL_UNSIGNED_INT:
				return count * sizeof(unsigned int);

			case GL_UNSIGNED_SHORT:
				return count * sizeof(unsigned short);

			case GL_UNSIGNED_BYTE:
				return count * sizeof(unsigned char);
		}

		MV_Assert(false, "Invalid count or type!");
	}


	// ************* VertexBuffer ************* //



	Ref<VertexBuffer> VertexBuffer::Create(BufferUsage usage) {
		return std::make_shared<VertexBuffer>(usage);
	}


	VertexBuffer::VertexBuffer(BufferUsage usage) :m_Usage(usage), m_Size(0)
	{
		glGenBuffers(1, &m_RendererID);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::UploadData(const void* data) {
		if (!m_Size) {
			MV_WARN("[VertexBuffer] '" << m_RendererID << "'Size is 0!");
		}
		glBufferData(GL_ARRAY_BUFFER, m_Size, data, ConvertUsage(m_Usage));
	}

	void VertexBuffer::Resize(unsigned int size) {
		m_Size = size;
	}

	void VertexBuffer::Bind() const{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}



	void VertexBuffer::SetLayout(const BufferLayout& layout) {
		m_Layout = layout;
	}

	// ************* IndexBuffer ************* //


	Ref<IndexBuffer> IndexBuffer::Create(unsigned int count, IndexBuffer::BufferType type) {
		return std::make_shared<IndexBuffer>(count, type);
	}



	IndexBuffer::IndexBuffer(unsigned int count, IndexBuffer::BufferType type) 
		:  m_Count(count), m_Type(ConvertType(type))
	{

		m_Size = CalculateSize(count, m_Type);
		glGenBuffers(1, &m_RendererID);
	}

	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void IndexBuffer::UploadData(const void* data) {
		if (!m_Size || !m_Count)  {
			MV_WARN("[IndexBuffer] '" << m_RendererID << "'Size or count is 0!"); 
		}
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Size, data, GL_STATIC_DRAW);
	}

	void IndexBuffer::Resize(unsigned int count, IndexBuffer::BufferType type) {
		m_Count = count;
		m_Type = ConvertType(type);
		m_Size = CalculateSize(count, m_Type);
	}

	void IndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}