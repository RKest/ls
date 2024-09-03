#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace ls
{
    class Camera
    {
    public:
        Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) :
            perspective{glm::perspective(fov, aspect, zNear, zFar)}, position{pos}
        {
        }

        inline auto Pos() -> glm::vec3& { return position; }
        inline auto Fwd() -> glm::vec3& { return forward; }
        inline auto Up() -> glm::vec3& { return up; }
        inline auto ViewProjection() const -> glm::mat4
        {
            return perspective * glm::lookAt(position, position + forward, up);
        }

    private:
        glm::mat4 perspective;
        glm::vec3 position;
        glm::vec3 forward{0, 0, 1};
        glm::vec3 up{0, 1, 0};
    };
} // namespace ls