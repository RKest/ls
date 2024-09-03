#include "ls/shader.h"

#include <fstream>
#include <iostream>

using namespace ls;

static void CheckShaderError(GLuint shader, GLuint flag, const std::string& errorMessage);
static void CheckProgramError(GLuint shader, GLuint flag, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::filesystem::path& shaders_path, std::span<std::string> param_names,
               std::span<std::string> uniform_names, bool has_geom_shader) :
    uniforms(uniform_names.size())
{
    program = glCreateProgram();
    shaders.push_back(CreateShader(LoadShader(shaders_path / "VS.glsl"), GL_VERTEX_SHADER));
    shaders.push_back(CreateShader(LoadShader(shaders_path / "FS.glsl"), GL_FRAGMENT_SHADER));
    if (has_geom_shader)
    {
        shaders.push_back(CreateShader(LoadShader(shaders_path / "GS.glsl"), GL_GEOMETRY_SHADER));
    }
    for (auto& shader : shaders)
    {
        glAttachShader(program, shader);
    }
    for (std::size_t i = 0; i < param_names.size(); ++i)
    {
        glBindAttribLocation(program, i, param_names[i].c_str());
    }
    glLinkProgram(program);
    CheckProgramError(program, GL_LINK_STATUS, "ERROR: Program linking failed");
    glValidateProgram(program);
    CheckProgramError(program, GL_VALIDATE_STATUS, "ERROR: Program is invalid");

    for (std::size_t i = 0; i < uniform_names.size(); ++i)
    {
        uniforms[i] = glGetUniformLocation(program, uniform_names[i].c_str());
    }
}

Shader::~Shader()
{
    for (auto& shader : shaders)
    {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }
    glDeleteProgram(program);
}

void Shader::Bind()
{
    glUseProgram(program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
    glm::mat4 model = transform.Model();
    glm::mat4 projection = camera.ViewProjection();

    SetMat4(TRANSFORM_U, model);
    SetMat4(PROJECTION_U, projection);
}

void Shader::Update(const Transform& transform)
{
    glm::mat4 model = transform.Model();

    SetMat4(TRANSFORM_U, model);
    SetMat4(PROJECTION_U, blankTransform);
}

static std::string LoadShader(const std::string& fileName)
{
    std::string output;
    std::string line;
    std::ifstream file{fileName};
    if (!file.is_open())
    {
        std::cerr << "Unable to open shader: " << fileName << std::endl;
        return output;
    }
    while (getline(file, line))
    {
        output.append(line + '\n');
    }
    return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = {0};
    glGetShaderiv(shader, flag, &success);
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}
static void CheckProgramError(GLuint shader, GLuint flag, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = {0};
    glGetProgramiv(shader, flag, &success);
    if (success == GL_FALSE)
    {
        glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0)
        std::cerr << "ERROR: Shader creation failed" << std::endl;

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];

    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, "ERROR: Shader failed to compile");

    return shader;
}

void Shader::SetMat4(const std::string& name, const glm::mat4& arg)
{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &arg[0][0]);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& arg)
{
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &arg[0]);
}

void Shader::SetFloat(const std::string& name, float arg)
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), arg);
}

void Shader::SetInt(const std::string& name, unsigned arg)
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), arg);
}

void Shader::SetMat4(std::span<Shader> shaders, const std::string& name, const glm::mat4& arg)
{
    for (Shader& shader : shaders)
        shader.SetMat4(name, arg);
}

void Shader::SetVec3(std::span<Shader> shaders, const std::string& name, const glm::vec3& arg)
{
    for (Shader& shader : shaders)
        shader.SetVec3(name, arg);
}

void Shader::SetFloat(std::span<Shader> shaders, const std::string& name, float arg)
{
    for (Shader& shader : shaders)
        shader.SetFloat(name, arg);
}
