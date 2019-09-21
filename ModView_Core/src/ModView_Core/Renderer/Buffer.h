#pragma once


namespace MV {

	enum class BufferUsage {
		None = 0, Static, Dynamic
	};
	class VertexBuffer {
		public :

			VertexBuffer(BufferUsage usage = BufferUsage::Static);
			~VertexBuffer();

			void UploadData(const void* data);
			void Resize(unsigned int size);

			void Bind() const;
			void Unbind() const;


		private :
			unsigned int m_RendererID, m_Size;
			BufferUsage m_Usage;
	};

	class IndexBuffer {
		public :
			enum class BufferType {
				None = 0, Char, Short, Int
			};


			IndexBuffer(unsigned int count, IndexBuffer::BufferType type);
			~IndexBuffer();



			void UploadData(const void* data);
			void Resize(unsigned int count, IndexBuffer::BufferType type);

			void Bind() const;
			void Unbind() const;

			inline unsigned int GetSize() const { return m_Size; }
			inline unsigned int GetCount() const { return m_Count; }
			inline unsigned int GetType() const { return m_Type; }

		private :
			unsigned int m_RendererID, m_Size, m_Count, m_Type;
	};
}