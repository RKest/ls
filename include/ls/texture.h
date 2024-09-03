#pragma once

#include <GL/glew.h>
#include <string>

namespace ls
{
    class Texture
    {
    public:
        Texture(const std::string& fileName);

        void bind(unsigned unit);

        virtual ~Texture();

    private:
        GLuint texture;
    };
}