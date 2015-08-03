#pragma once

namespace ALZ_RENDERER
{
	class IRendererImpl
	{
		//!!!!Can be constructed and used only inside Renderer!!!!!!!!!!
		friend class Renderer;
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	protected:
		IRendererImpl()
		{}
		//Don't allow copy or assign
		IRendererImpl(const IRendererImpl& rendererImpl);
		const IRendererImpl& operator=(const IRendererImpl& rendererImpl);
		//!!!!!!!!!!!!!!!!!!!!!!!!!
	public:
		virtual ~IRendererImpl()
		{}
	protected:
		virtual bool initialize(const void* params) = 0;
		virtual void deInitialize() = 0;
		virtual void render() = 0;
		virtual void update() = 0;
		virtual bool isInitialized() = 0;
	};
}; //ALZ_RENDERER