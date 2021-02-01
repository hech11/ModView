#pragma once

#include "mvpch.h"
#include "Buffer.h"

namespace MV {

	class VertexArray {

		public :
			VertexArray();
			~VertexArray();


			void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
			void AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

			void Bind() const;
			void Unbind()const;

			inline std::vector<Ref<VertexBuffer>>& GetVertexBuffers() { return m_VertexBuffers; }
			inline Ref<IndexBuffer>& GetIndexBuffer() { return m_IndexBuffer; }

		public :
			static Ref<VertexArray> Create();
		private :
			unsigned int m_RendererID;

			std::vector<Ref<VertexBuffer>> m_VertexBuffers;
			Ref<IndexBuffer> m_IndexBuffer;
	};

}