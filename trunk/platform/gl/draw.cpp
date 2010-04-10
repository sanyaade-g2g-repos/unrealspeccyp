/*
Portable ZX-Spectrum emulator.
Copyright (C) 2001-2010 SMT, Dexus, Alone Coder, deathsoft, djdron, scor

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "../platform.h"
#include "../../std.h"

#ifdef USE_GL

#ifdef _WINDOWS
#include <windows.h>
#endif//_WINDOWS

#include <GL/gl.h>

#ifdef _LINUX
//#define GLX_GLXEXT_PROTOTYPES 1
#include <GL/glx.h>
#endif//_LINUX

namespace xPlatform
{

static dword tex[512*256];

#define RGBX(r, g, b) ((b << 16)|(g << 8)|r)

//=============================================================================
//	DrawGL
//-----------------------------------------------------------------------------

static const GLushort vertices[4 * 2] =
{
	0, 0,
	0, 1,
	1, 1,
	1, 0,
};
static const GLubyte triangles[2 * 3] =
{
	0, 1, 2,
	0, 2, 3,
};

void DrawGL(int _w, int _h, void* _data)
{
	const byte brightness = 200;
	const byte bright_intensity = 55;
	byte* data = (byte*)_data;
	for(int y = 0; y < 240; ++y)
	{
		for(int x = 0; x < 320; ++x)
		{
			byte r, g, b;
			byte c = data[y*320+x];
			byte i = c&8 ? brightness + bright_intensity : brightness;
			b = c&1 ? i : 0;
			r = c&2 ? i : 0;
			g = c&4 ? i : 0;
			dword* p = &tex[y*512+x];
			*p = RGBX(r, g ,b);
		}
	}

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(320.0f/512.0f, 240.0f/256.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

	glColor3f(1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f);
	glViewport(0, 0, _w, _h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_SHORT, 0, vertices);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_SHORT, 0, vertices);
	glDrawElements(GL_TRIANGLES, 2*3, GL_UNSIGNED_BYTE, triangles);

	glFlush();
}

#ifdef _LINUX
void VsyncGL(bool on)
{
#ifdef GLX_SGI_swap_control
	static bool inited = false;
	static PFNGLXSWAPINTERVALSGIPROC si = NULL;
	if(!inited)
	{
		si = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalSGI");
		inited = true;
	}
	if(si)
		si(on);
//	const char* exts = (const char*)glGetString(GL_EXTENSIONS);
//	if(strstr(exts, "GLX_SGI_swap_control"))
	{
//		glXSwapIntervalSGI(on);
	}
#endif//GLX_SGI_swap_control
}
#endif//_LINUX

#ifdef _WINDOWS
void VsyncGL(bool on)
{
}
#endif//_WINDOWS

}
//namespace xPlatform

#endif//USE_GL
