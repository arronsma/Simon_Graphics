
#include "Renderer.h"
#include <direct.h>
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
	Renderer r;
	r.init();
	r.SetFramebufferSizeCallback();
	r.Render();

	std::cout << _getcwd(NULL, 0);
	return 0;
}


