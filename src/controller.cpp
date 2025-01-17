#include "ls/controller.h"

#include <SDL2/SDL.h>

using namespace ls;

Controller::Controller(Camera& new_camera) : camera{new_camera}
{
    bindToFront(W, &Controller::moveForward, this);
    bindToFront(S, &Controller::moveBackwards, this);
    bindToFront(A, &Controller::moveLeft, this);
    bindToFront(D, &Controller::moveRight, this);
    bindToFront(LCTRL, &Controller::moveDown, this);
    bindToFront(SPACE, &Controller::moveUp, this);
}
void Controller::moveForward()
{
    camera.Pos() += default_stride * glm::vec3(camera.Fwd().x, 0, camera.Fwd().z);
}
void Controller::moveBackwards()
{
    camera.Pos() -= default_stride * glm::vec3(camera.Fwd().x, 0, camera.Fwd().z);
}
void Controller::moveLeft()
{
    camera.Pos() -= default_stride * glm::normalize(glm::cross(camera.Fwd(), camera.Up()));
}
void Controller::moveRight()
{
    camera.Pos() += default_stride * glm::normalize(glm::cross(camera.Fwd(), camera.Up()));
}
void Controller::moveDown()
{
    camera.Pos() -= default_stride * glm::vec3(0, 1, 0);
}
void Controller::moveUp()
{
    camera.Pos() += default_stride * glm::vec3(0, 1, 0);
}
void Controller::bindTo(Controller::Key key, std::function<void()> callback)
{
    key_callbacks.emplace_back(key, std::move(callback));
}

void Controller::invokeMouseEvents()
{
    SDL_GetRelativeMouseState(&xChange, &yChange);

    float sens = 0.1f;
    yaw += xChange * sens;
    pitch -= yChange * sens;
    pitch = std::clamp(pitch, -89.F, 89.F);

    camera.Fwd().x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera.Fwd().y = sin(glm::radians(pitch));
    camera.Fwd().z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera.Fwd() = glm::normalize(camera.Fwd());
}

void Controller::invokeKeyboardEvents()
{
    for (auto& [key, callback] : key_callbacks)
    {
        if (keys[getScancode(key)])
        {
            callback();
        }
    }
}

auto Controller::getScancode(Key key) -> SDL_Scancode
{
    // Do not define default case for compiler warnings
    switch (key)
    {
    case W: return SDL_SCANCODE_W;
    case S: return SDL_SCANCODE_S;
    case A: return SDL_SCANCODE_A;
    case D: return SDL_SCANCODE_D;
    case LCTRL: return SDL_SCANCODE_LCTRL;
    case SPACE: return SDL_SCANCODE_SPACE;
    case ESC: return SDL_SCANCODE_ESCAPE;
    }
    return SDL_Scancode{};
}
