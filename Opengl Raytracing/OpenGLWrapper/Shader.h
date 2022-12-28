#pragma once
#include "Common.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <functional>
class Shader
{
protected:
	int m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string, int>m_UniformLocationCache;
public:
	static std::unordered_map<int, Shader*> shaderList;
	int programID;
	Shader(){}
	Shader(const std::string& filepath);
	bool Recompile();
	~Shader();
	virtual void Bind();
	void Unbind();
	const std::string& GetFilePath() { return m_FilePath; }
	//Uniform
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform1i(const std::string& name, int val);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform3f(const std::string& name, const glm::vec3& vec);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform4f(const std::string& name, const glm::vec4&);
	void SetUniformMat4f(const std::string& name, const glm::mat4&);
	void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);
	void SetUniformMat2f(const std::string& name, const glm::mat2& matrix);

	std::function<void(Shader*)> preRender;

protected:
	int GetUniformLocation(const std::string& name);
};

class ComputeShader : public Shader
{
public:
	ComputeShader(const std::string& str);
	void Dispatch(uint groups_x, uint groups_y, uint groups_z);
};
