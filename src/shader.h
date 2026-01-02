#pragma once
#include <string>

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
};
