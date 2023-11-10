/*
*******************************************************************************

Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.
Copyright (C) 2019-2020, 2022 SugarBombEngine Developers

This file is part of SugarBombEngine

SugarBombEngine is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

SugarBombEngine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with SugarBombEngine. If not, see <http://www.gnu.org/licenses/>.

In addition, SugarBombEngine is using id Tech 4 (BFG) pieces and thus subject to certain additional terms (all header and source files which 
contains such pieces has this additional part appended to the license header). You should have received a copy of these additional terms 
stated in a separate file (LICENSE-idTech4) which accompanied the SugarBombEngine source code. If not, please request a copy in 
writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc.,
Suite 120, Rockville, Maryland 20850 USA.

*******************************************************************************
*/

/// @file

//*****************************************************************************

#pragma once

//*****************************************************************************

namespace sbe
{

class SbDict;
class idUserCmdMgr;

struct SbFile;
struct SbRenderWorld;
struct SbSoundWorld;

constexpr auto TIME_GROUP1{0};
constexpr auto TIME_GROUP2{1};

struct gameReturn_t;

struct SbGame
{
	/// Initialize the game for the first time
	virtual void Init() = 0;
	
	/// Shut down the entire game
	virtual void Shutdown() = 0;
	
	/// Runs a game frame, may return a session command for level changing, etc
	virtual void RunFrame(idUserCmdMgr &aCmdMgr, gameReturn_t &aGameReturn) = 0;
	
	/// Runs prediction on entities at the client
	virtual void ClientRunFrame(idUserCmdMgr &aCmdMgr, bool abLastPredictFrame, gameReturn_t &aGameReturn) = 0;
	
	/// Makes rendering and sound system calls to display for a given clientNum
	virtual bool Draw(int anClientNum) = 0;
	
	///
	virtual void Shell_CreateMenu(bool abInGame) = 0;
	
	///
	virtual void Shell_Cleanup() = 0;
	
	///
	virtual void Shell_Show(bool abShow) = 0;
	
	///
	virtual void Shell_SyncWithSession() = 0;
};

}; // namespace sbe