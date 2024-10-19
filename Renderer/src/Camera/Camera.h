#include <glm/glm.hpp>
#include "../Screen/Window.h"

class Camera
{
    // The Camera will render to window or offscreen RBO.
    // if render to window, the size change of window ?
    float fov;
    float width;
    float height;

    float nearPlane;
    float farPlane;

    glm::mat4x4 projectionMatrix;
public:
};