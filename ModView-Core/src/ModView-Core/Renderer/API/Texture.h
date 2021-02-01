#pragma once
#include <cstdint>
#include <string>

namespace MV {


	//TODO: texture props !
	class Texture {

		public :
			Texture(const std::string& filepath);
			~Texture();

			void Bind(uint8_t slot = 0) const;
			void Unbind() const;

			uint32_t GetRendererID() const { return m_RendererID; }
			uint32_t GetSlot() const { return m_Slot; }

		public :
			static Ref<Texture> Create(const std::string& filepath);

		private :
			uint32_t m_RendererID;
			int32_t m_Width = 0, m_Height = 0, m_Bpp = 0;
			mutable uint32_t m_Slot;
			std::string m_Filepath;
	};

}