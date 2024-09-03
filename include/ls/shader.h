#pragma once

#include <filesystem>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <GL/glew.h>

#include "camera.h"
#include "transform.h"

namespace ls
{

    class Shader
    {
    public:
        Shader(const std::filesystem::path& shader_path, std::span<std::string> paramNames,
               std::span<std::string> uniform_names, bool has_geom_shader = false);

        void Bind();
        void Update(const Transform& transform, const Camera& camera);
        void Update(const Transform& transform);

        void SetMat4(const std::string& name, const glm::mat4& arg);
        void SetFloat(const std::string& name, float arg);
        void SetVec3(const std::string& name, const glm::vec3& arg);
        void SetInt(const std::string& name, unsigned int arg);

        static void SetMat4(std::span<Shader> shaders, const std::string& name,
                            const glm::mat4& arg);
        static void SetVec3(std::span<Shader> shaders, const std::string& name,
                            const glm::vec3& arg);
        static void SetFloat(std::span<Shader> shaders, const std::string& name, float arg);

        virtual ~Shader();

    protected:
    private:
        void SetMat4(GLuint uId, const glm::mat4& arg)
        {
            glUniformMatrix4fv(uniforms[uId], 1, GL_FALSE, &arg[0][0]);
        }

        void SetVec3(GLuint uId, const glm::vec3& arg) { glUniform3fv(uniforms[uId], 1, &arg[0]); }

        GLuint program;
        // 0 == Vertex Shader; 1 == Fragment Shader
        std::vector<GLuint> shaders;
        std::vector<GLuint> uniforms;

        glm::mat4 blankTransform = glm::translate(glm::vec3(0, 0, 0));
    };
} // namespace ls
