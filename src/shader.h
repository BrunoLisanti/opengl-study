#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <string>

namespace b 
{
	class shader
	{
	private:
		std::string vertex_path;
		std::string fragment_path;
	public:
		unsigned int ID;
		shader(std::string vertex_path, std::string fragment_path);
		void use() const;
		void compile() ;
		void set_bool(const std::string &name, bool value) const;  
		void set_int(const std::string &name, int value) const;   
		void set_float(const std::string &name, float value) const;
		void set_vec2(const std::string &name, const glm::vec2 &value) const;
		void set_vec2(const std::string &name, float x, float y) const;
		void set_vec3(const std::string &name, const glm::vec3 &value) const;
		void set_vec3(const std::string &name, float x, float y, float z) const;
		void set_vec4(const std::string &name, const glm::vec4 &value) const;
		void set_vec4(const std::string &name, float x, float y, float z, float w) const;
		void set_mat2(const std::string &name, const glm::mat2 &value) const;
		void set_mat3(const std::string &name, const glm::mat3 &value) const;
		void set_mat4(const std::string &name, const glm::mat4 &value) const;
	};
}
