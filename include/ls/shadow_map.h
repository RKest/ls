#pragma once

#include "ls/shader.h"

#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/transform.hpp"

namespace ls
{
    class ShadowMap
    {
    public:
        ShadowMap();
        ~ShadowMap();

        void Apply(Shader& depthMapShader, Transform& transform, const glm::vec3& lightPos);
        void CleanUp(unsigned screenWidth, unsigned screenHeight);
        inline GLuint Cubemap() { return depthCubemap; }

    protected:
    private:
        glm::mat4 shadowProjection;

        GLuint depthMapFBO;
        GLuint depthCubemap;
    };
} // namespace ls
