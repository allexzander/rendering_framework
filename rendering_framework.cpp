#include "rendering_framework.h"
#include "renderer\commondefs.h"
#include "renderer\renderer.h"

namespace ALZ_RENDERER
{
	RenderingFrameWork::RenderingFrameWork() : m_pRenderer(nullptr)
	{
	}

	Renderer* RenderingFrameWork::getRenderer()
	{
		if(!m_pRenderer)
		{
			m_pRenderer = Renderer::getInstance();
		}

		return m_pRenderer;
	}

	RenderingFrameWork* RenderingFrameWork::getInstance()
	{
		if(!pInstance)
		{
			pInstance = new RenderingFrameWork();
		}

		return pInstance;
	}

	RenderingFrameWork::~RenderingFrameWork()
	{
	}

	RenderingFrameWork* RenderingFrameWork::pInstance = nullptr;
};