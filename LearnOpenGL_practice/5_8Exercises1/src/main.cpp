
#include "Renderer.h"
#include <direct.h>
#include "Shader.h"


int main()
{
	Renderer r;
	r.init();
	r.SetFramebufferSizeCallback();
	r.Render();

	std::cout << _getcwd(NULL, 0);
	return 0;
}


