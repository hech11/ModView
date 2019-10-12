#include "mvpch.h"
#include "VertexArray.h"

#include <GLAD/include/glad.h>


namespace MV {



	static unsigned int BufferLayoutDataTypeToOpenGLType(BufferLayoutTypes type)
	{
		switch (type) {
			case BufferLayoutTypes::Char:	return GL_BYTE;
			case BufferLayoutTypes::Char2:	return GL_BYTE;
			case BufferLayoutTypes::Char3:	return GL_BYTE;
			case BufferLayoutTypes::Char4:	return GL_BYTE;
			case BufferLayoutTypes::Short2: return GL_SHORT;
			case BufferLayoutTypes::Short3: return GL_SHORT;
			case BufferLayoutTypes::Short4: return GL_SHORT;
			case BufferLayoutTypes::Int:	return GL_INT;
			case BufferLayoutTypes::Int2:	return GL_INT;
			case BufferLayoutTypes::Int3:	return GL_INT;
			case BufferLayoutTypes::Int4:	return GL_INT;
			case BufferLayoutTypes::Float4: return GL_FLOAT;
			case BufferLayoutTypes::Float3: return GL_FLOAT;
			case BufferLayoutTypes::Float2: return GL_FLOAT;
			case BufferLayoutTypes::Float: return GL_FLOAT;
			case BufferLayoutTypes::Mat4:	return GL_FLOAT_MAT4x3;
		}

		MV_Assert(false, "No buffer types were listed!");
		return 0;
	}

	Ref<VertexArray> VertexArray::Create() {
		return std::make_shared<VertexArray>();
	}

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
		Bind();
		vertexBuffer->Bind();


		unsigned int index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		MV_Assert(layout.GetElements().size(), "Layout not set in vertexbuffer!");
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				BufferLayoutDataTypeToOpenGLType(element.type),
				(element.normilized ? GL_TRUE : GL_FALSE),
				layout.GetStride(),
				(const void*)element.offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
		Bind();
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	void VertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() const {
		glBindVertexArray(0);

	}

}