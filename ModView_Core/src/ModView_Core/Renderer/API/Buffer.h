#pragma once


namespace MV {

	enum class BufferUsage {
		None = 0, Static, Dynamic
	};


	enum class BufferLayoutTypes
	{
		None = -1,
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4,
		Short2,
		Short3,
		Short4,
		Char,
		Char2,
		Char3,
		Char4,
		Mat4
	};

	static unsigned int BufferLayoutDataTypeSize(BufferLayoutTypes type)
	{
		switch (type)
		{

			case BufferLayoutTypes::Char:		return 1;
			case BufferLayoutTypes::Char2:		return 2;
			case BufferLayoutTypes::Char3:		return 3;
			case BufferLayoutTypes::Char4:		return 4;
			case BufferLayoutTypes::Float:		return 4;
			case BufferLayoutTypes::Float2:		return 4 * 2;
			case BufferLayoutTypes::Float3:		return 4 * 3;
			case BufferLayoutTypes::Float4:		return 4 * 4;
			case BufferLayoutTypes::Mat4:		return 4 * 4 * 4;
			case BufferLayoutTypes::Int:		return 4;
			case BufferLayoutTypes::Int2:		return 4 * 2;
			case BufferLayoutTypes::Int3:		return 4 * 3;
			case BufferLayoutTypes::Int4:		return 4 * 4;
		}

		MV_Assert(false, "Unknown Buffer layout data type!");
		return 0;
	}



	struct BufferElement {
		std::string name;
		BufferLayoutTypes type;
		unsigned int count, offset, size;
		bool normilized;

		BufferElement(const std::string& dName, BufferLayoutTypes dataType, bool dnormilized = false)
			: name(dName), type(dataType), size(BufferLayoutDataTypeSize(dataType)), offset(0), normilized(dnormilized)
		{
			count = GetComponentCount();
		}


		unsigned int GetComponentCount() const {
			switch (type)
			{
				case BufferLayoutTypes::Float:   return 1;
				case BufferLayoutTypes::Float2:  return 2;
				case BufferLayoutTypes::Float3:  return 3;
				case BufferLayoutTypes::Float4:  return 4;
				case BufferLayoutTypes::Mat4:    return 4 * 4;
				case BufferLayoutTypes::Int:     return 1;
				case BufferLayoutTypes::Int2:    return 2;
				case BufferLayoutTypes::Int3:    return 3;
				case BufferLayoutTypes::Int4:    return 4;
			}
		}

	};


	class BufferLayout {

		public :
			BufferLayout(const std::initializer_list<BufferElement>& elements)
				: m_Elements(elements)
			{
				CalculateStrideAndOffset();
			}

			BufferLayout() {}

			void CalculateStrideAndOffset() {
				unsigned int offset = 0;
				m_Stride = 0;

				for (auto& elements : m_Elements) {

					elements.offset = offset;
					offset += elements.size;
					m_Stride += elements.size;
				}
			}	


			inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
			inline unsigned int GetStride() const { return m_Stride; }


			std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
			std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
			std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
			std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		private:
			std::vector<BufferElement> m_Elements;
			unsigned int m_Stride = 0;

	};




	class VertexBuffer {
		public :

			VertexBuffer(BufferUsage usage = BufferUsage::Static);
			~VertexBuffer();

			void UploadData(const void* data);
			void Resize(unsigned int size);

			void Bind() const;
			void Unbind() const;


			void SetLayout(const BufferLayout& layout);
			BufferLayout GetLayout() const { return m_Layout; }


		public :
			static Ref<VertexBuffer> Create(BufferUsage usage = BufferUsage::Static);

		private :
			unsigned int m_RendererID, m_Size;
			BufferUsage m_Usage;
			BufferLayout m_Layout;
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

		public :
			static Ref<IndexBuffer> Create(unsigned int count, IndexBuffer::BufferType type);

		private :
			unsigned int m_RendererID, m_Size, m_Count, m_Type;
	};
}