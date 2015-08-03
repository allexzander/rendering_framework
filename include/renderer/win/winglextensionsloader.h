#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glext.h>

namespace ALZ_RENDERER
{
	class WinGlExtensionsLoader
	{
	protected:
		WinGlExtensionsLoader();
		WinGlExtensionsLoader(const WinGlExtensionsLoader& winGlExtensionLoader);
		const WinGlExtensionsLoader& operator=(const WinGlExtensionsLoader& winGlExtensionLoader);
		~WinGlExtensionsLoader();
	public:
		static WinGlExtensionsLoader* pInstance;
		static WinGlExtensionsLoader* getInstance() 
		{ 
			if(pInstance == nullptr)
			{
				pInstance = new WinGlExtensionsLoader(); 
			}
			
			return pInstance; 
		}
	public:
		void loadExtensions();
	public:
		//Extension pointers
		PFNGLGENVERTEXARRAYSPROC		  glGenVertexArrays;
		PFNGLBINDVERTEXARRAYPROC		  glBindVertexArray;
		PFNGLGENBUFFERSPROC				  glGenBuffers;
		PFNGLBINDBUFFERPROC				  glBindBuffer;
		PFNGLBUFFERDATAPROC				  glBufferData;
		PFNGLVERTEXATTRIBPOINTERPROC	  glVertexAttribPointer;
		PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray;
		PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
		PFNGLDELETEBUFFERSPROC			  glDeleteBuffers;
		PFNGLDELETEVERTEXARRAYSPROC		  glDeleteVertexArrays;
		PFNGLCREATESHADERPROC			  glCreateShader;
		PFNGLSHADERSOURCEPROC			  glShaderSource;
		PFNGLCOMPILESHADERPROC			  glCompileShader;
		PFNGLCREATEPROGRAMPROC			  glCreateProgram;
		PFNGLLINKPROGRAMPROC			  glLinkProgram;
		PFNGLUSEPROGRAMPROC				  glUseProgram;
		PFNGLATTACHSHADERPROC			  glAttachShader;
		PFNGLDETACHSHADERPROC			  glDetachShader;
		PFNGLDELETESHADERPROC			  glDeleteShader;
		PFNGLDELETEPROGRAMPROC			  glDeleteProgram;
		PFNGLGETUNIFORMLOCATIONPROC		  glGetUniformLocation;
		PFNGLUNIFORMMATRIX4FVPROC		  glUniformMatrix4fv;
	};
};