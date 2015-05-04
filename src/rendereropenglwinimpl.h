#pragma once

#include "irendererimpl.h"

namespace ALZ_RENDERER
{
	////forward declarations
	class WinGlExtensionsLoader;

	class RendererOpenGlWinImpl : public IRendererImpl
	{
		friend class Renderer;
	public:
		struct WinOpenGLInitParams
		{
			float glClearColor[4];

			WinOpenGLInitParams()
			{
				glClearColor[0] = 0.0f;
				glClearColor[1] = 0.0f;
				glClearColor[2] = 0.0f;
				glClearColor[3] = 0.0f;
			}
		};
	private:
		RendererOpenGlWinImpl();
		~RendererOpenGlWinImpl();
		RendererOpenGlWinImpl(const RendererOpenGlWinImpl& rImpl);
	private:
		virtual bool initialize(const void* params);
		virtual void deInitialize();
		virtual void render();
		virtual void update();
		virtual bool isInitialized() { return m_initialized; }
	private:
		void drawAll();
		void loadExtensions();
	private:
		bool m_initialized;
		WinGlExtensionsLoader* p_glExtensionsLoader;
	};
}; //ALZ_RENDERER