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

#include "../std.h"
#include "ui.h"
#include "../platform/io.h"

#ifdef USE_UI

namespace xUi
{

static dword screen[WIDTH*HEIGHT];
dword* Screen() { return screen; }

static struct eInit
{
	eInit() { memset(screen, 0, sizeof(screen)); }
}init;

static const eRGBAColor COLOR_WHITE(0x08ffffff);

inline void DrawPixel(const ePoint& p, const eRGBAColor& c)
{
	dword* dst = &screen[p.y*WIDTH + p.x];
	*dst = c.rgba;
}
inline void GetPixel(const ePoint& p, eRGBAColor* c)
{
	dword* dst = &screen[p.y*WIDTH + p.x];
	c->rgba = *dst;
}

void DrawRect(const eRect& r, const eRGBAColor& c)
{
	ePoint p;
	for(p.y = r.top; p.y < r.bottom; ++p.y)
	{
		for(p.x = r.left; p.x < r.right; ++p.x)
		{
			DrawPixel(p, c);
		}
	}
}

void DrawRect(const eRect& r, const eRGBAColor& c, const eRGBAColor& key)
{
	ePoint p;
	eRGBAColor src;
	for(p.y = r.top; p.y < r.bottom; ++p.y)
	{
		for(p.x = r.left; p.x < r.right; ++p.x)
		{
			GetPixel(p, &src);
			if(src.rgba != key.rgba)
			{
				DrawPixel(p, c);
			}
		}
	}
}

static class eFont
{
public:
	eFont() { Clear(self); }
	~eFont() { SAFE_DELETE(data); }
	void Create(int _w, int _h, const char* fname)
	{
		assert(!data);
		w = _w; h = _h;
		FILE* f = fopen(xIo::ResourcePath(fname), "rb");
		assert(f);
		int size = 8 * 256;
		data = new byte[size];
		fread(data, 1, size, f);
		fclose(f);
	}
	void Draw(int _char, const ePoint& p)
	{
		int pitch = 256;
		byte* src = data + _char + pitch*1;
		for(int y = 0; y < h; ++y)
		{
			for(int x = 0; x < w; ++x)
			{
				if(!((*src << x)&0x80))
					continue;
				DrawPixel(ePoint(p.x + x, p.y + y), COLOR_WHITE);
			}
			src += pitch;
		}
	}

public:
	int w, h;
	byte* data;
}font;

void DrawText(const eRect& r, const char* s)
{
	strupr(const_cast<char*>(s));
	ePoint p = r.beg;
	for(int i = 0; s[i]; ++i)
	{
		if(p.x + font.w > r.right)
			break;
		font.Draw(s[i], p);
		p.x += font.w;
	}
}

void _CreateFont(int _w, int _h, const char* fname) { font.Create(_w, _h, fname); }
int FontHeight() { return font.h; }

}
//namespace xUi

#endif//USE_UI