#include "rendering_framework.h"
#include "src\core\string.h"
#include "src\core\vector.h"
#include <Windows.h>

int main()
{
	ALZ_RENDERER::RenderingFrameWork* pRenderingFramework = ALZ_RENDERER::RenderingFrameWork::getInstance();
	ALZ_RENDERER::Renderer* pRenderer = pRenderingFramework->getRenderer();
	//init win opengl for now...
	pRenderer->initialize(ALZ_RENDERER::Renderer::RENDERER_IMPLEMENTATION::RER_IMPL_OPENGL_WIN);

	return 0;
}