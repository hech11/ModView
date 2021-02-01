#include "mvpch.h"
#include "Texture.h"

#include <GLAD/include/glad.h>
#include <stb_image/stb_image.h>


namespace MV {

	Ref<Texture> Texture::Create(const std::string& filepath) {
		return std::make_shared<Texture>(filepath);
	}



	Texture::Texture(const std::string& filepath) 
		: m_Filepath(filepath), m_Slot(0)
	{
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);


		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_Bpp, 4);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		} else {
			MV_ERROR("Failed to load %s", filepath.c_str());
		}

		stbi_image_free(data);

	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererID);
	}


	void Texture::Bind(uint8_t slot) const
	{
		m_Slot = slot;
		glActiveTexture(GL_TEXTURE0 + m_Slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void Texture::Unbind() const
	{
		m_Slot = 0;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}