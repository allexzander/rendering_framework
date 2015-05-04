#include "src\renderer.h"

int main()
{
	ALZ_RENDERER::Renderer* pRenderer = ALZ_RENDERER::Renderer::getInstance();
#if _WIN32
	pRenderer->initialize(ALZ_RENDERER::Renderer::RER_IMPL_OPENGL_WIN);
#endif //_WIN32
	return 0;
}