#include "mvpch.h"
#include "Shader.h"

#include <GLAD/include/glad.h>
#include "glm/gtc/type_ptr.hpp"


namespace MV {
	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment")
			return GL_FRAGMENT_SHADER;
		if (type == "geometry")
			return GL_GEOMETRY_SHADER;
		#if 0
		if (type == "compute") // I do not support openGL 4.3 or later
			return GL_COMPUTE_SHADER
		#endif
;

		MV_Assert(false, "Unknown shader type!");
		return 0;
	}
	
	static std::string ShaderTypeToString(unsigned int type) {
		switch (type) {
			case GL_VERTEX_SHADER:
				return "vertex";

			case GL_FRAGMENT_SHADER:
				return "fragment";


			case GL_GEOMETRY_SHADER:
				return "geometry";
		}
		
		MV_Assert(false, "Unknown shader type!");
		return 0;
	}
	


	Ref<Shader> Shader::Create(const std::string& filepath) {
		return std::make_shared<Shader>(filepath);

	}
	Ref<Shader> Shader::Create(const std::string& name, const char* vert, const char* frag) {
		return std::make_shared<Shader>(name, vert, frag);

	}

	Shader::Shader(const std::string& filepath) {
		std::string source = ReadFile(filepath);
		auto shaderSources = GetSources(source);
		Compile(shaderSources);

		// TODO: Get name from file
		m_Name = "TestShader! " + std::to_string(m_Program);
	}
	Shader::Shader(const std::string& name, const char* vert, const char* frag) : m_Name(name) {
		std::unordered_map<unsigned int, std::string> srcs;
		srcs[GL_VERTEX_SHADER] = std::string(vert);
		srcs[GL_FRAGMENT_SHADER] = std::string(frag);
		Compile(srcs);
	}

	Shader::~Shader() {
		glDeleteProgram(m_Program);
	}


	void Shader::Bind() const {
		glUseProgram(m_Program);
	}
	void Shader::Unbind() const {
		glUseProgram(0);
	}

	void Shader::Compile(const std::unordered_map<unsigned int, std::string>& src) {
		m_Program = glCreateProgram();
		MV_Assert(src.size() != 0, "Shader sources are 0!");

		std::vector<unsigned int> shaderID;
		shaderID.reserve(2);

		unsigned int srcSize = src.size();
		for (auto& s : src) {

			unsigned int type = s.first;
			const auto& source = s.second;

			unsigned int shader = glCreateShader(type);
			const char* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			int compileVal;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compileVal);
			if (compileVal == GL_FALSE) {
				int length = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

				std::vector<char> msg(length);
				glGetShaderInfoLog(shader, length, &length, &msg[0]);
				MV_ERROR("Shader Error!: [" << ShaderTypeToString(type) << "] : " << msg.data() << std::endl);

				glDeleteShader(shader);
				break;
			}

			glAttachShader(m_Program, shader);

			shaderID.emplace_back(shader);
		}


		glLinkProgram(m_Program);

		int linkValidation = 0;
		glGetProgramiv(m_Program, GL_LINK_STATUS, &linkValidation);
		if (linkValidation == GL_FALSE) {
			int length = 0;
			glGetProgramiv(m_Program, GL_LINK_STATUS, &length);

			char* infoLog = (char*)alloca(length);
			glGetProgramInfoLog(m_Program, length, &length, infoLog);
			glDeleteProgram(m_Program);

			MV_ERROR("Shader Error! : " << infoLog << std::endl);
			return;
		}

		for (auto id : shaderID) {
			glDetachShader(m_Program, id);
		}
		
	}


	std::unordered_map<unsigned int, std::string> Shader::GetSources(std::string src) {
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = src.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = src.find_first_of("\r\n", pos);
			MV_Assert(eol != std::string::npos, "There is a syntax error!");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = src.substr(begin, eol - begin);
			MV_Assert(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = src.find_first_not_of("\r\n", eol);
			pos = src.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = src.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? src.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}


	std::string Shader::ReadFile(const std::string& filepath) {
		std::string result;
		std::ifstream file(filepath, std::ios::in | std::ios::binary);

		if (!file) {
			MV_ERROR("Could not open file '" << filepath << "'!" << std::endl);
		}

		file.seekg(0, std::ios::end);
		result.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&result[0], result.size());
		file.close();

		return result;
	}


	int Shader::GetUniformLocations(const std::string& name) {

		if (m_UniformCacheLocations.find(name) != m_UniformCacheLocations.end()) {
			return m_UniformCacheLocations[name];
		}


		int location = glGetUniformLocation(m_Program, name.c_str());
		if (location < 0)
			MV_WARN("'" << name << "' uniform may not exist!");
		m_UniformCacheLocations[name] = location;
		return location;
	}

	void Shader::UploadUniform4f(const std::string& name, const glm::vec4& values) {
		glUniform4f(GetUniformLocations(name), values.x, values.y, values.z, values.w);
	}

	void Shader::UploadUniform3f(const std::string& name, const glm::vec3& values) {
		glUniform3f(GetUniformLocations(name), values.x, values.y, values.z);
	}

	void Shader::UploadUniform2f(const std::string& name, const glm::vec2& values) {
		glUniform2f(GetUniformLocations(name), values.x, values.y);
	}

	void Shader::UploadUniform1f(const std::string& name, float value) {
		glUniform1f(GetUniformLocations(name), value);
	}

	void Shader::UploadUniform1i(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocations(name), value);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& mat) {
		glUniformMatrix4fv(GetUniformLocations(name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	
}