#include "winglextensionsloader.h"

#include <GL/wglext.h>

namespace ALZ_RENDERER
{
	WinGlExtensionsLoader::WinGlExtensionsLoader()
	{
		glGenVertexArrays = nullptr;
		glBindVertexArray = nullptr;
		glGenBuffers = nullptr;
		glBindBuffer = nullptr;
		glBufferData = nullptr;
		glVertexAttribPointer = nullptr;
		glEnableVertexAttribArray = nullptr;
		glDisableVertexAttribArray = nullptr;
		glDeleteBuffers = nullptr;
		glDeleteVertexArrays = nullptr;
		glCreateShader = nullptr;
		glShaderSource = nullptr;
		glCompileShader = nullptr;
		glCreateProgram = nullptr;
		glLinkProgram = nullptr;
		glUseProgram = nullptr;
		glAttachShader = nullptr;
		glDetachShader = nullptr;
		glDeleteShader = nullptr;
		glDeleteProgram = nullptr;
		glGetUniformLocation = nullptr;
		glUniformMatrix4fv = nullptr;

		loadExtensions();
	}

	WinGlExtensionsLoader::~WinGlExtensionsLoader()
	{
	}

	void WinGlExtensionsLoader::loadExtensions()
	{
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
		glGenBuffers	  = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
		glBindBuffer	  = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
		glBufferData	  = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
		glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
		glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
		glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
		glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
		glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
		glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
		glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
		glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
		glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
		glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
		glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
		glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
		glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	}

	WinGlExtensionsLoader* WinGlExtensionsLoader::pInstance = nullptr;
}
