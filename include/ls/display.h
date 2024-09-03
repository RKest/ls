#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace ls
{
    class Display
    {
    public:
        Display(int _width, int _height, const std::string& title);

        void clear(float r, float g, float b, float a);
        void close();
        void update();
        [[nodiscard]] auto isClosed() -> bool const&;
        [[nodiscard]] auto aspectRatio() -> float const&;

        virtual ~Display();

    private:
        void initSDL(int width, int height, const std::string& title);
        void initGLOptions();

        SDL_Window* window;
        SDL_GLContext glContext;

        float aspect_ratio;
        bool is_closed = false;
    };
} // namespace ls
