#pragma once

namespace ALZ_RENDERER
{
	class IRendererImpl;

	class Renderer
	{
	public:
		enum RENDERER_IMPLEMENTATION
		{
			RER_IMPL_UNKNOWN = -1,
			RER_IMPL_OPENGL_WIN
		};
	private:
		Renderer();
		Renderer(const Renderer& renderer);
		const Renderer& operator=(const Renderer& renderer);
	public:
		static Renderer* getInstance();
	public:
		~Renderer();
		bool initialize(RENDERER_IMPLEMENTATION rendererImpl);
		static void deInitialize();
		void render();
		void update();
		bool isInitialized() { return m_initialized; }
	private:
		IRendererImpl* m_pRendererImpl;
		bool m_initialized;
	private:
		static Renderer* pInstance;
	};
}; //ALZ_RENDERER