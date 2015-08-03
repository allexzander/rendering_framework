#include "renderer/win/rendereropenglwinimpl.h"
#include "renderer/win/winglextensionsloader.h"
#include <windows.h>

#pragma comment(lib, "Opengl32")

//external globals
HWND  g_hWnd;
HDC	  g_hDC;
HGLRC g_hGLRC;

namespace ALZ_RENDERER
{
	RendererOpenGlWinImpl::RendererOpenGlWinImpl() : m_initialized(false), p_glExtensionsLoader(nullptr)
	{
		p_glExtensionsLoader = WinGlExtensionsLoader::getInstance();
	}

	RendererOpenGlWinImpl::~RendererOpenGlWinImpl()
	{

	}

	bool RendererOpenGlWinImpl::initialize(const void* params)
	{
		const WinOpenGLInitParams* initParams = static_cast<const WinOpenGLInitParams*>(params);
		//-------------------------------------------------------------------------------------
		//------------Fill in PIXELFORMATDESCRIPTOR struct-------------------------------------
		//-------------------------------------------------------------------------------------
		PIXELFORMATDESCRIPTOR pixelFormatDesc;
		ZeroMemory(&pixelFormatDesc, sizeof(pixelFormatDesc));

		pixelFormatDesc.nSize		 = sizeof(PIXELFORMATDESCRIPTOR);
		pixelFormatDesc.nVersion	 = 1;
		pixelFormatDesc.dwFlags		 = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pixelFormatDesc.iPixelType	 = PFD_TYPE_RGBA;
		pixelFormatDesc.cColorBits	 = 32;
		pixelFormatDesc.cDepthBits	 = 24;
		pixelFormatDesc.cStencilBits = 8;
		//-------------------------------------------------------------------------------------


		//Choose Pixel Format
		int pixelFormat = ChoosePixelFormat(g_hDC, &pixelFormatDesc);


		//Try setting Pixel Format
		if (!SetPixelFormat(g_hDC, pixelFormat, &pixelFormatDesc))
		{
			return false;
		}

		//Try creating OpenGL Rendering Context
		g_hGLRC = wglCreateContext(g_hDC);

		if (g_hGLRC == NULL)
		{
			return false;
		}

		//Try making Rendering Context current
		if (!wglMakeCurrent(g_hDC, g_hGLRC))
		{
			return false;
		}

		if(initParams != nullptr)
		{
			glClearColor(initParams->glClearColor[0]/*R*/, initParams->glClearColor[1]/*G*/,
				initParams->glClearColor[2]/*B*/, initParams->glClearColor[3]/*alpha*/);

		}

		m_initialized = true;

		return true;
	}

	void RendererOpenGlWinImpl::deInitialize()
	{
		if(!m_initialized)
		{
			return;
		}

		if (g_hGLRC != NULL)
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(g_hGLRC);

			if (g_hWnd != NULL)
			{
				ReleaseDC(g_hWnd, g_hDC);
			}
		}

		m_initialized = false;
	}

	void RendererOpenGlWinImpl::render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawAll();
		SwapBuffers(g_hDC);
	}

	void RendererOpenGlWinImpl::update()
	{
	}

	void RendererOpenGlWinImpl::drawAll()
	{
	}
};