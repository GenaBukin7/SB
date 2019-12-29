/*
*******************************************************************************

Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company. 
Copyright (C) 2019 SugarBombEngine Developers

This file is part of SugarBombEngine

SugarBombEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SugarBombEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SugarBombEngine. If not, see <http://www.gnu.org/licenses/>.

In addition, SugarBombEngine is using id Tech 4 (BFG) pieces and thus
subject to certain additional terms (all header and source files which 
contains such pieces has this additional part appended to the license 
header). You should have received a copy of these additional terms 
stated in a separate file (LICENSE-idTech4) which accompanied the 
SugarBombEngine source code. If not, please request a copy in 
writing from id Software at the address below.

If you have questions concerning this license or the applicable additional
terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc.,
Suite 120, Rockville, Maryland 20850 USA.

*******************************************************************************
*/

/// @file

//*****************************************************************************

#include <stdexcept>

#include <windows.h>

#include "SbWindowWin.hpp"

#include "CoreLibs/SbSystem/ISystem.hpp"

//*****************************************************************************

namespace sbe
{

LONG WINAPI MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 1;
	};
	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
};

/*
=======================
GLW_CreateWindow

Responsible for creating the Win32 window.
If fullscreen, it won't have a border
=======================
*/
SbWindowWin::SbWindowWin(ISystem &aSystem, int anWidth, int anHeight, const char *asTitle, bool abFullScreen)
	: mSystem(aSystem)
{
	// create our window class if we haven't already
	CreateWindowClass();
	
	int stylebits{WINDOW_STYLE | WS_SYSMENU};
	int exstyle{0};
	
	if(parms.fullScreen != 0)
	{
		stylebits = WS_POPUP | WS_VISIBLE | WS_SYSMENU;
		exstyle = WS_EX_TOPMOST;
	};
	
	mhWnd = CreateWindowEx(exstyle, WIN32_WINDOW_CLASS_NAME, GAME_NAME, stylebits, x, y, w, h, nullptr, nullptr, win32.hInstance, nullptr);
					 
	if(!mhWnd)
	{
		mSystem.Printf("^3GLW_CreateWindow() - Couldn't create window^0\n");
		throw std::runtime_error("Couldn't create window!");
	};
	
	::SetTimer(mhWnd, 0, 100, nullptr);
	
	ShowWindow(mhWnd, SW_SHOW);
	UpdateWindow(mhWnd);
	mSystem.Printf("...created window @ %d,%d (%dx%d)\n", x, y, w, h);
	
	SetForegroundWindow(mhWnd);
	SetFocus(mhWnd);
};

SbWindowWin::~SbWindowWin()
{
	// destroy window
	if(mhWnd)
	{
		mSystem.Printf("...destroying window\n");
		ShowWindow(mhWnd, SW_HIDE);
		DestroyWindow(mhWnd);
		mhWnd = nullptr;
	};
};

/*
==============
Sys_ShowWindow
==============
*/
void SbWindowWin::SetVisible(bool abVisible)
{
	::ShowWindow(mhWnd, abVisible ? SW_SHOW : SW_HIDE);
};

/*
==============
Sys_IsWindowVisible
==============
*/
bool SbWindowWin::IsVisible() const
{
	return (::IsWindowVisible(mhWnd) != 0);
};

void SbWindowWin::CreateWindowClass()
{
	WNDCLASS wc{};
	
	//
	// register the window class if necessary
	//
	//if( win32.windowClassRegistered )
		//return;
	
	memset(&wc, 0, sizeof(wc));
	
	wc.style         = 0;
	wc.lpfnWndProc   = ( WNDPROC ) MainWndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = win32.hInstance;
	wc.hIcon         = LoadIcon( win32.hInstance, MAKEINTRESOURCE( IDI_ICON1 ) );
	wc.hCursor       = nullptr;
	wc.hbrBackground = ( struct HBRUSH__* )COLOR_GRAYTEXT;
	wc.lpszMenuName  = 0;
	wc.lpszClassName = WIN32_WINDOW_CLASS_NAME;
	
	if( !RegisterClass( &wc ) )
	{
		common->FatalError( "GLW_CreateWindow: could not register window class" );
	}
	common->Printf( "...registered window class\n" );
	
	//win32.windowClassRegistered = true;
};

}; // namespace sbe