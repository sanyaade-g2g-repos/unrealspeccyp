/*
Portable ZX-Spectrum emulator.
Copyright (C) 2001-2012 SMT, Dexus, Alone Coder, deathsoft, djdron, scor

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

#include "platform/platform.h"
#include "speccy.h"
#include "devices/memory.h"
#include "devices/ula.h"
#include "devices/input/keyboard.h"
#include "devices/input/kempston_joy.h"
#include "devices/input/kempston_mouse.h"
#include "devices/input/tape.h"
#include "devices/sound/ay.h"
#include "devices/sound/beeper.h"
#include "devices/fdd/wd1793.h"
#include "z80/z80.h"
#include "snapshot/snapshot.h"
#include "platform/io.h"
#include "ui/ui_desktop.h"
#include "platform/custom_ui/ui_main.h"
#include "tools/profiler.h"
#include "options_common.h"
#include "file_type.h"
#include "snapshot/rzx.h"

namespace xPlatform
{

class eMacro
{
public:
	eMacro() : frame(-1) {}
	virtual ~eMacro() {}
	virtual bool Do() = 0;
	virtual bool Update()
	{
		++frame;
		return Do();
	}
protected:
	int frame;
};

static struct eSpeccyHandler : public eHandler, public eRZX::eHandler, public xZ80::eZ80::eHandlerIo
{
	eSpeccyHandler() : speccy(NULL), macro(NULL), replay(NULL), video_paused(0), inside_replay_update(false) {}
	virtual ~eSpeccyHandler() { assert(!speccy); }
	virtual void OnInit();
	virtual void OnDone();
	virtual const char* OnLoop();
	virtual void* VideoData() { return speccy->Device<eUla>()->Screen(); }
	virtual void* VideoDataUI()
	{
#ifdef USE_UI
		return ui_desktop->VideoData();
#else//USE_UI
		return NULL;
#endif//USE_UI
	}
	virtual const char* WindowCaption() { return "Unreal Speccy Portable"; }
	virtual void OnKey(char key, dword flags);
	virtual void OnMouse(eMouseAction action, byte a, byte b);
	virtual bool FileTypeSupported(const char* name)
	{
		eFileType* t = eFileType::FindByName(name);
		return t && t->AbleOpen();
	}
	virtual bool OnOpenFile(const char* name, const void* data, size_t data_size);
	bool OpenFile(const char* name, const void* data, size_t data_size);
	virtual bool OnSaveFile(const char* name);
	virtual eActionResult OnAction(eAction action);

	virtual int	AudioSources() { return FullSpeed() ? 0 : SOUND_DEV_COUNT; }
	virtual void* AudioData(int source) { return sound_dev[source]->AudioData(); }
	virtual dword AudioDataReady(int source) { return sound_dev[source]->AudioDataReady(); }
	virtual void AudioDataUse(int source, dword size) { sound_dev[source]->AudioDataUse(size); }
	virtual void VideoPaused(bool paused) {	paused ? ++video_paused : --video_paused; }
	virtual void VideoFrameRate(int v) { for(int i = 0; i < SOUND_DEV_COUNT; ++i) sound_dev[i]->FrameRate(v); }

	virtual bool FullSpeed() const { return speccy->CPU()->HandlerStep() != NULL; }

	void PlayMacro(eMacro* m) { SAFE_DELETE(macro); macro = m; }
	virtual bool RZX_OnOpenSnapshot(const char* name, const void* data, size_t data_size) { return OpenFile(name, data, data_size); }
	virtual byte Z80_IoRead(word port, int tact)
	{
		byte r = 0xff;
		replay->IoRead(&r);
		return r;
	}
	const char* RZXErrorDesc(eRZX::eError err) const;
	void Replay(eRZX* r)
	{
		speccy->CPU()->HandlerIo(NULL);
		SAFE_DELETE(replay);
		replay = r;
		if(replay)
			speccy->CPU()->HandlerIo(this);
	}

	eSpeccy* speccy;
#ifdef USE_UI
	xUi::eDesktop* ui_desktop;
#endif//USE_UI
	eMacro* macro;
	eRZX* replay;
	int video_paused;
	bool inside_replay_update;

	enum { SOUND_DEV_COUNT = 3 };
	eDeviceSound* sound_dev[SOUND_DEV_COUNT];
} sh;

void eSpeccyHandler::OnInit()
{
	assert(!speccy);
	speccy = new eSpeccy;
#ifdef USE_UI
	ui_desktop = new xUi::eDesktop;
	ui_desktop->Insert(new xUi::eMainDialog);
#endif//USE_UI
	sound_dev[0] = speccy->Device<eBeeper>();
	sound_dev[1] = speccy->Device<eAY>();
	sound_dev[2] = speccy->Device<eTape>();
	xOptions::Init();
	OnAction(A_RESET);
}
void eSpeccyHandler::OnDone()
{
	xOptions::Done();
	SAFE_DELETE(macro);
	SAFE_DELETE(replay);
	SAFE_DELETE(speccy);
#ifdef USE_UI
	SAFE_DELETE(ui_desktop);
#endif//USE_UI
	PROFILER_DUMP;
}
const char* eSpeccyHandler::OnLoop()
{
	const char* error = NULL;
	if(FullSpeed() || !video_paused)
	{
		if(macro)
		{
			if(!macro->Update())
				SAFE_DELETE(macro);
		}
		if(replay)
		{
			int icount = 0;
			inside_replay_update = true;
			eRZX::eError err = replay->Update(&icount);
			inside_replay_update = false;
			if(err == eRZX::E_OK)
			{
				speccy->Update(&icount);
				err = replay->CheckSync();
			}
			if(err != eRZX::E_OK)
			{
				Replay(NULL);
				error = RZXErrorDesc(err);
			}
		}
		else
			speccy->Update(NULL);
	}
#ifdef USE_UI
	ui_desktop->Update();
#endif//USE_UI
	xOptions::Apply();
	return error;
}
const char* eSpeccyHandler::RZXErrorDesc(eRZX::eError err) const
{
	switch(err)
	{
	case eRZX::E_OK:			return "rzx_ok";
	case eRZX::E_FINISHED:		return "rzx_finished";
	case eRZX::E_SYNC_LOST:		return "rzx_sync_lost";
	case eRZX::E_INVALID:		return "rzx_invalid";
	case eRZX::E_UNSUPPORTED:	return "rzx_unsupported";
	}
	return NULL;
}
void eSpeccyHandler::OnKey(char key, dword flags)
{
	bool down = (flags&KF_DOWN) != 0;
	bool shift = (flags&KF_SHIFT) != 0;
	bool ctrl = (flags&KF_CTRL) != 0;
	bool alt = (flags&KF_ALT) != 0;

#ifdef USE_UI
	if(!(flags&KF_UI_SENDER))
	{
		ui_desktop->OnKey(key, flags);
		if(ui_desktop->Focused())
			return;
	}
#endif//USE_UI

	if(flags&KF_KEMPSTON)
		speccy->Device<eKempstonJoy>()->OnKey(key, down);
	if(flags&KF_CURSOR)
	{
		switch(key)
		{
		case 'l' : key = '5'; shift = down; break;
		case 'r' : key = '8'; shift = down; break;
		case 'u' : key = '7'; shift = down; break;
		case 'd' : key = '6'; shift = down; break;
		case 'f' : key = '0'; shift = false; break;
		}
	}
	else if(flags&KF_QAOP)
	{
		switch(key)
		{
		case 'l' : key = 'O'; break;
		case 'r' : key = 'P'; break;
		case 'u' : key = 'Q'; break;
		case 'd' : key = 'A'; break;
		case 'f' : key = ' '; break;
		}
	}
	else if(flags&KF_SINCLAIR2)
	{
		switch(key)
		{
		case 'l' : key = '6'; break;
		case 'r' : key = '7'; break;
		case 'u' : key = '9'; break;
		case 'd' : key = '8'; break;
		case 'f' : key = '0'; break;
		}
	}
	speccy->Device<eKeyboard>()->OnKey(key, down, shift, ctrl, alt);
}
void eSpeccyHandler::OnMouse(eMouseAction action, byte a, byte b)
{
	switch(action)
	{
	case MA_MOVE: 	speccy->Device<eKempstonMouse>()->OnMouseMove(a, b); 	break;
	case MA_BUTTON:	speccy->Device<eKempstonMouse>()->OnMouseButton(a, b != 0);	break;
	default: break;
	}
}
bool eSpeccyHandler::OnOpenFile(const char* name, const void* data, size_t data_size)
{
	OPTION_GET(op_last_file)->Set(name);
	return OpenFile(name, data, data_size);
}
bool eSpeccyHandler::OpenFile(const char* name, const void* data, size_t data_size)
{
	eFileType* t = eFileType::FindByName(name);
	if(!t)
		return false;

	if(data && data_size)
		return t->Open(data, data_size);

	FILE* f = fopen(name, "rb");
	if(!f)
		return false;
	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);
	fseek(f, 0, SEEK_SET);
	byte* buf = new byte[size];
	size_t r = fread(buf, 1, size, f);
	fclose(f);
	if(r != size)
	{
		delete[] buf;
		return false;
	}
	bool ok = t->Open(buf, size);
	delete[] buf;
	return ok;
}
bool eSpeccyHandler::OnSaveFile(const char* name)
{
	OPTION_GET(op_last_file)->Set(name);
	eFileType* t = eFileType::FindByName(name);
	if(!t)
		return false;
	return t->Store(name);
}

eActionResult eSpeccyHandler::OnAction(eAction action)
{
	switch(action)
	{
	case A_RESET:
		if(!inside_replay_update) // can be called from replay->Update()
			SAFE_DELETE(replay);
		SAFE_DELETE(macro);
		speccy->Reset();
		if(inside_replay_update)
			speccy->CPU()->HandlerIo(this);
		return AR_OK;
	case A_TAPE_TOGGLE:
		{
			eTape* tape = speccy->Device<eTape>();
			if(!tape->Inserted())
				return AR_TAPE_NOT_INSERTED;
			if(!tape->Started())
			{
				if(OPTION_GET(op_tape_fast))
					speccy->CPU()->HandlerStep(fast_tape_emul);
				else
					speccy->CPU()->HandlerStep(NULL);
				tape->Start();
			}
			else
				tape->Stop();
			return tape->Started() ? AR_TAPE_STARTED : AR_TAPE_STOPPED;
		}
	case A_TAPE_QUERY:
		{
			eTape* tape = speccy->Device<eTape>();
			if(!tape->Inserted())
				return AR_TAPE_NOT_INSERTED;
			return tape->Started() ? AR_TAPE_STARTED : AR_TAPE_STOPPED;
		}
	}
	return AR_ERROR;
}

static struct eFileTypeRZX : public eFileType
{
	virtual bool Open(const void* data, size_t data_size)
	{
		eRZX* rzx = new eRZX;
		if(rzx->Open(data, data_size, &sh) == eRZX::E_OK)
		{
			sh.Replay(rzx);
			return true;
		}
		else
		{
			sh.Replay(NULL);
			SAFE_DELETE(rzx);
		}
		return false;
	}
	virtual const char* Type() { return "rzx"; }
} ft_rzx;

static struct eFileTypeZ80 : public eFileType
{
	virtual bool Open(const void* data, size_t data_size)
	{
		sh.OnAction(A_RESET);
		return xSnapshot::Load(sh.speccy, Type(), data, data_size);
	}
	virtual const char* Type() { return "z80"; }
} ft_z80;
static struct eFileTypeSZX : public eFileTypeZ80
{
	virtual const char* Type() { return "szx"; }
} ft_szx;
static struct eFileTypeSNA : public eFileTypeZ80
{
	virtual bool Store(const char* name)
	{
		return xSnapshot::Store(sh.speccy, name);
	}
	virtual const char* Type() { return "sna"; }
} ft_sna;

class eMacroDiskRun : public eMacro
{
	virtual bool Do()
	{
		switch(frame)
		{
		case 100:
			sh.OnKey('e', KF_DOWN|KF_UI_SENDER);
			break;
		case 102:
			sh.OnKey('e', KF_UI_SENDER);
			break;
		case 200:
			sh.OnKey('e', KF_DOWN|KF_UI_SENDER);
			break;
		case 202:
			sh.OnKey('e', KF_UI_SENDER);
			return false;
		}
		return true;
	}
};

static struct eFileTypeTRD : public eFileType
{
	virtual bool Open(const void* data, size_t data_size)
	{
		eWD1793* wd = sh.speccy->Device<eWD1793>();
		bool ok = wd->Open(Type(), data, data_size);
		if(ok && OPTION_GET(op_auto_play_image))
		{
			sh.OnAction(A_RESET);
			if(wd->BootExist())
				sh.speccy->Device<eMemory>()->SetRomPage(eMemory::P_ROM_DOS);
			else
			{
				sh.speccy->Device<eMemory>()->SetRomPage(eMemory::P_ROM_SYS);
				sh.PlayMacro(new eMacroDiskRun);
			}
		}
		return ok;
	}
	virtual const char* Type() { return "trd"; }
} ft_trd;
static struct eFileTypeSCL : public eFileTypeTRD
{
	virtual const char* Type() { return "scl"; }
} ft_scl;
static struct eFileTypeFDI : public eFileTypeTRD
{
	virtual const char* Type() { return "fdi"; }
} ft_fdi;

class eMacroTapeLoad : public eMacro
{
	virtual bool Do()
	{
		switch(frame)
		{
		case 100:
			sh.OnKey('J', KF_DOWN|KF_UI_SENDER);
			break;
		case 102:
			sh.OnKey('J', KF_UI_SENDER);
			sh.OnKey('P', KF_DOWN|KF_ALT|KF_UI_SENDER);
			break;
		case 104:
			sh.OnKey('P', KF_UI_SENDER);
			break;
		case 110:
			sh.OnKey('P', KF_DOWN|KF_ALT|KF_UI_SENDER);
			break;
		case 112:
			sh.OnKey('P', KF_UI_SENDER);
			break;
		case 120:
			sh.OnKey('e', KF_DOWN|KF_UI_SENDER);
			break;
		case 122:
			sh.OnKey('e', KF_UI_SENDER);
			sh.OnAction(A_TAPE_TOGGLE);
			return false;
		}
		return true;
	}
};

static struct eFileTypeTAP : public eFileType
{
	virtual bool Open(const void* data, size_t data_size)
	{
		bool ok = sh.speccy->Device<eTape>()->Open(Type(), data, data_size);
		if(ok && OPTION_GET(op_auto_play_image))
		{
			sh.OnAction(A_RESET);
			eMemory* m = sh.speccy->Devices().Get<eMemory>();
			m->SetRomPage(m->ROM_SOS());
			sh.PlayMacro(new eMacroTapeLoad);
		}
		return ok;
	}
	virtual const char* Type() { return "tap"; }
} ft_tap;
static struct eFileTypeCSW : public eFileTypeTAP
{
	virtual const char* Type() { return "csw"; }
} ft_csw;
static struct eFileTypeTZX : public eFileTypeTAP
{
	virtual const char* Type() { return "tzx"; }
} ft_tzx;

}
//namespace xPlatform

// see platform-specific files for main() function
