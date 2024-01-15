/*
*******************************************************************************

Copyright (C) 2019-2020 SugarBombEngine Developers

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

*******************************************************************************
*/

/// @file
/// @brief SbGameFramework module exports

//*****************************************************************************

#include <functional>

#include "SbGameFramework.hpp"
#include "SbGameFramework/SbModuleAPI.hpp"
#include "SbGameExternal.hpp"
#include "SbNetworkExternal.hpp"
#include "SbPhysicsExternal.hpp"

#ifdef _WIN32
#	define EXPORT [[dllexport]]
#else
#	define EXPORT [[visibility("default")]]
#endif

#define C_EXPORT extern "C" EXPORT

//*****************************************************************************

sbe::IGame *CreateGame(sbe::IRenderSystem &aRenderSystem, sbe::ISoundSystem &aSoundSystem, sbe::ISystem &aSystem)
{
#ifndef SBE_SINGLE_BINARY
	static sbe::SbGameFramework::SbGameExternal SbGameModule(aSystem);
	return SbGameModule.GetGame();
#else
	return new sbe::SbGame::SbGame(aSystem);
#endif
};

sbe::INetworkSystem *CreateNetworkSystem(sbe::ISystem &aSystem)
{
#ifndef SBE_NETWORK_HARD_LINKED
	static sbe::SbGameFramework::SbNetworkExternal SbNetworkModule(aSystem);
	return SbNetworkModule.GetNetworkSystem();
#else
	return new sbe::SbNetwork::SbNetworkSystem(aSystem);
#endif
};

sbe::IPhysicsSystem *CreatePhysicsSystem(sbe::ISystem &aSystem)
{
#ifndef SBE_PHYSICS_HARD_LINKED
	static sbe::SbGameFramework::SbPhysicsExternal SbPhysicsModule(aSystem);
	return SbPhysicsModule.GetPhysicsSystem();
#else
	return new sbe::SbPhysics::SbPhysicsSystem(aSystem);
#endif
};

C_EXPORT sbe::gameFrameworkExport_t *GetGameFrameworkAPI(sbe::gameFrameworkImport_t *apModuleImports)
{
	if(apModuleImports->version == sbe::GAMEFRAMEWORK_API_VERSION)
	{
		static sbe::ISystem &System = *apModuleImports->sys;
		static sbe::IGame *pGame = CreateGame(*apModuleImports->sys);
		static sbe::INetworkSystem *pNetworkSystem = CreateNetworkSystem(*apModuleImports->sys);
		static sbe::SbGameFramework::SbGameFramework GameFramework(apModuleImports->renderSystem, apModuleImports->soundSystem, *pNetworkSystem, *pGame, System);
		
		static sbe::gameFrameworkExport_t ModuleExports;
		
		ModuleExports.version = sbe::GAMEFRAMEWORK_API_VERSION;
		ModuleExports.gameFramework = std::addressof(GameFramework);
		
		return &ModuleExports;
	};
	
	return nullptr;
};