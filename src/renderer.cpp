#include "renderer.h"
#include "irendererimpl.h"
#include "rendereropenglwinimpl.h"

namespace ALZ_RENDERER
{
	Renderer::Renderer() : m_pRendererImpl(nullptr)
	{
	}
	Renderer* Renderer::getInstance()
	{
		if(!pInstance)
		{
			pInstance = new Renderer();
		}

		return pInstance;
	}
	Renderer::~Renderer()
	{
	}
	bool Renderer::initialize(RENDERER_IMPLEMENTATION rendererImpl)
	{
		void* renderImplParams = nullptr;

		switch(rendererImpl)
		{
		case RER_IMPL_OPENGL_WIN:
			{
				m_pRendererImpl = new RendererOpenGlWinImpl();
				RendererOpenGlWinImpl::WinOpenGLInitParams* openglRendererParams = new RendererOpenGlWinImpl::WinOpenGLInitParams();
				openglRendererParams->glClearColor[1] = 1.0f;
				renderImplParams = openglRendererParams;
				break;
			}
		default:
			break;
		}

		if(m_pRendererImpl == nullptr)
		{
			return false;
		}

		bool result = m_pRendererImpl->initialize(renderImplParams);

		if(renderImplParams)
		{
			delete renderImplParams;
		}

		m_initialized = result;

		return result;
	}
	void Renderer::deInitialize()
	{
		if(!pInstance || !pInstance->m_initialized)
		{
			return;
		}

		if(pInstance->m_pRendererImpl)
		{
			pInstance->m_pRendererImpl->deInitialize();
			delete pInstance->m_pRendererImpl;
			pInstance->m_pRendererImpl = nullptr;
		}

		pInstance->m_initialized = false;
		delete pInstance;
		pInstance = nullptr;
	}
	void Renderer::render()
	{
		if(m_pRendererImpl)
		{
			m_pRendererImpl->render();
		}
	}
	void Renderer::update()
	{
		if(m_pRendererImpl)
		{
			m_pRendererImpl->update();
		}
	}

	Renderer* Renderer::pInstance = nullptr;
}; //ALZ_RENDERER