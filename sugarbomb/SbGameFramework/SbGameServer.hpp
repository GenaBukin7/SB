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
/// @brief game server - a type of server which treats net clients/connections as players

//*****************************************************************************

#pragma once

#include <vector>

//*****************************************************************************

namespace sbe
{

struct INetServer;

namespace SbGameFramework
{

class SbGameClient;
using tGameClientVec = std::vector<SbGameClient*>;

class SbGameServer
{
public:
	SbGameServer(uint32_t anPort);
	
	SbGameClient *GetClient(int anIndex) const {return mvClients.at(anIndex);}
private:
	tGameClientVec mvClients;
	
	INetServer *mpNetServer{nullptr};
};

};}; // namespace sbe::SbGameFramework