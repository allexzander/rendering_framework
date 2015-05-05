#include "rendering_framework.h"
#include "src\core\string.h"
#include <Windows.h>

int main()
{
	ALZ_RENDERER::RenderingFrameWork* pRenderingFramework = ALZ_RENDERER::RenderingFrameWork::getInstance();
	ALZ_RENDERER::Renderer* pRenderer = pRenderingFramework->getRenderer();
	//init win opengl for now...
	pRenderer->initialize(ALZ_RENDERER::Renderer::RENDERER_IMPLEMENTATION::RER_IMPL_OPENGL_WIN);

	CORE_LIB::String myString(_T("Привет мир!"));
	CORE_LIB::String myString1(myString);
	CORE_LIB::String myString3;
	CORE_LIB::String myNumberString(_T("-12345.124242"));
	double toDouble = myNumberString;
	int toInt = myNumberString;
	const TCHAR* toString = myString;
	return 0;
}