#include <GLFW/glfw3.h>

class GLFWWindow
{
    GLFWwindow* window;
public:
    int width;
    int height;

    int Init(int width, int height);
    void SetFramebufferSizeCallback(GLFWframebuffersizefun framebuffer_size_callback);

    bool ShouldClose();
    void ProcessInput();
    void SwapBuffers();
};