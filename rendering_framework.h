#pragma once
#include "src\renderer.h"

namespace ALZ_RENDERER
{
	/*Rendering Framework entry point*/
	class RenderingFrameWork
	{
	private:
		RenderingFrameWork();
		RenderingFrameWork(const RenderingFrameWork& copy);
		const RenderingFrameWork& operator=(const RenderingFrameWork& copy);
	public:
		~RenderingFrameWork();
	public:
		Renderer* getRenderer();
	public:
		static RenderingFrameWork* getInstance();
	private:
		Renderer* m_pRenderer;
	private:
		static RenderingFrameWork* pInstance;
	};
}; //ALZ_RENDERER