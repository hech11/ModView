#pragma once
#include <cstdint>
#include <vector>
#include "ModView-Core/Base/Base.h"


namespace MV {

	// TODO: framebuffer needs to support multi sampling...
	// TODO: Frame buffer needs a spec struct to help organize this header
	class FrameBuffer {

		public :
			FrameBuffer(uint32_t width, uint32_t height);
			~FrameBuffer();


			void Bind() const;
			void Unbind() const;

			void Resize(uint32_t width, uint32_t height);

			uint32_t GetColorAttachment() const { return m_ColorAttachment; }
			uint32_t GetDepthAttachment() const { return m_DepthAttachment; }
			uint32_t GetRendererID() const { return m_RendererID; }



			uint32_t GetWidth() const;
			uint32_t GetHeight() const;
		public :
			static Ref<FrameBuffer> Create(uint32_t width, uint32_t height);

		private :

			// Need a way to store the format of the attachments
			uint32_t m_RendererID, m_DepthAttachment;
			uint32_t m_ColorAttachment; // TODO: Needs to support multiple attachments


			uint32_t m_Width = 0, m_Height = 0;

	};

}
