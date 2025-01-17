#pragma once

#include "camera.h"
#include "transform.h"

#include <functional>
#include <iostream>

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>

namespace ls
{
    class Controller
    {
    public:
        Controller(Camera& camera);

        enum Key
        {
            W,
            A,
            S,
            D,
            LCTRL,
            SPACE,
            ESC
        };

        void invokeMouseEvents();
        void invokeKeyboardEvents();
        void bindTo(Key key, std::function<void()> callback);
        void bindToFront(Key key, auto&& function, auto&&... args)
        {
            bindTo(key, std::bind_front(std::forward<decltype(function)>(function),
                                        std::forward<decltype(args)>(args)...));
        }

    private:
        [[nodiscard]] static auto getScancode(Key key) -> SDL_Scancode;

        void moveForward();
        void moveBackwards();
        void moveRight();
        void moveLeft();
        void moveDown();
        void moveUp();

        Camera& camera;

        int xChange{0};
        int yChange{0};
        float yaw{-90.F};
        float pitch{0.F};

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        struct KeyMap
        {
            Key key;
            std::function<void()> callback;
        };
        std::vector<KeyMap> key_callbacks;

        constexpr static float default_stride = 0.1f;
    };
} // namespace ls
