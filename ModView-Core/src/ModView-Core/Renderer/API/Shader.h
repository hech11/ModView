#pragma once

#include "mvpch.h"

#include "glm/glm.hpp"
namespace MV {

	class Shader {
		public :
			Shader(const std::string& filepath);
			Shader(const std::string& name, const char* vert, const char* frag);

			~Shader();

			void Bind() const;
			void Unbind() const;

			void UploadUniform4f(const std::string& name, const glm::vec4& values);
			void UploadUniform3f(const std::string& name, const glm::vec3& values);
			void UploadUniform2f(const std::string& name, const glm::vec2& values);
			void UploadUniform1f(const std::string& name, float value);
			void UploadUniform1i(const std::string& name, int value);

			
			void UploadUniformMat4(const std::string& name, const glm::mat4& mat);

			inline std::string GetName() { return m_Name; }

		public :
			static Ref<Shader> Create(const std::string& filepath);
			static Ref<Shader> Create(const std::string& name, const char* vert, const char* frag);
		private :
			unsigned int m_Program;
			std::string m_Name;

			// TODO: This is temp. Need to implement a proper way to get uniforms during shader parsing.
			std::unordered_map<std::string, int> m_UniformCacheLocations;
			int GetUniformLocations(const std::string& name);

			std::string ReadFile(const std::string& filepath);
			void Compile(const std::unordered_map<unsigned int, std::string>& src);
			std::unordered_map<unsigned int, std::string> GetSources(std::string src);
	};

}