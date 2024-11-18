#pragma once

#include <string>
#include <unordered_map>
#include <map>


class Shader
{
public:
	Shader();
	~Shader();

public:
	void Parse(std::string shader_name);//����Shader�ļ�������
	void CreateShaderProgram(const char* vertex_shader_text, const char* fragment_shader_text);

	//void ConnectUniformBlockAndBindingPoint();

	void Active();//����
	void InActive();//����

	unsigned int shader_program_handle() const { return shader_program_handle_; }//Shader������;

public:
	static Shader* Find(std::string shader_name);

private:
	static std::unordered_map<std::string, Shader*> kShaderMap;

private:
	std::string shader_name_;
	unsigned int shader_program_handle_;
	//std::unordered_map<std::string, unsigned int> uniform_block_binding_point_map;
};

