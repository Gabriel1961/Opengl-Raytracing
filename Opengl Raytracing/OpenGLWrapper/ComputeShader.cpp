#include "Shader.h"
#include "Common.h"
#include "Shader.h"
#include "fstream"
#include "sstream"
#include "string"
#include <filesystem>
using namespace std;
void ShaderCompilationErrorCheck(unsigned int shaderID, const string& name);
void ShaderLinkErrorCheck(unsigned int shaderID, const string& name);

/// <summary>
/// Reads all text from the specified path
/// </summary>
/// <param name="path">path to the file you want to read</param>
/// <param name="out">null terminated string with the text</param>
/// <returns></returns>
void GetAllTextFromFile(const std::string& path, char*& out)
{
	std::ifstream fin(path);
	filesystem::path file(path);
	int fsize = std::filesystem::file_size(file);
	out = new char[fsize + 1];
	fin.get(out, fsize, 0);
	out[fsize] = 0;
}


int CreateProgram(const std::string& path)
{
	int ID;
	char* src;
	GetAllTextFromFile(path, src);
	gc(uint computeShader = glCreateShader(GL_COMPUTE_SHADER));
	gc(glShaderSource(computeShader, 1, &src, NULL));
	gc(glCompileShader(computeShader));

	ShaderCompilationErrorCheck(computeShader, path);

	ID = glCreateProgram();
	gc(glAttachShader(ID, computeShader));
	gc(glLinkProgram(ID));

	ShaderLinkErrorCheck(ID, path);
	glDeleteShader(computeShader);
	delete[] src;

	return ID;
}

/// <summary>
/// Creates a compute shader from path
/// </summary>
ComputeShader::ComputeShader(const std::string& path) :Shader()
{
	m_FilePath = path;
	m_RendererID = CreateProgram(path);
}
	

void ComputeShader::Dispatch(uint groups_x, uint groups_y, uint groups_z)
{
	Bind();
	glDispatchCompute(groups_x, groups_y, groups_z);
}

bool ComputeShader::Recompile()
{
	uint newId = 0;
	try {
		newId = CreateProgram(m_FilePath);
		gce(glUseProgram(newId));
	}
	catch (const exception& ex) {
		return 0;
	}
	if (newId == 0)
		return 0;

	gc(glDeleteProgram(m_RendererID));
	m_RendererID = newId;
	return 1;
}
