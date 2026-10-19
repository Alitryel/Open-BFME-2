/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: AutoDepositUpdate.h /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Aug 2002
//
//	Filename: 	AutoDepositUpdate.h
//
//	author:		Chris Huybregts
//	
//	purpose:	Auto Deposit Update Module
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __AUTO_DEPOSIT_UPDATE_H_
#define __AUTO_DEPOSIT_UPDATE_H_

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "GameLogic/Module/UpdateModule.h"
//-----------------------------------------------------------------------------
// FORWARD REFERENCES /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
class Player;
class Thing;
void parseUpgradePair( INI *ini, void *instance, void *store, const void *userData );
struct upgradePair
{
	std::string type;
	Int         amount;
};

//-----------------------------------------------------------------------------
// TYPE DEFINES ///////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// BFME TU-scoped shim (ModuleFactory.cpp only): Zero Hour's
// AutoDepositUpdate.h, unchanged except that this unit must keep its rowed
// ??_GAutoDepositUpdateModuleData deleting destructor (0x0025528B) while not
// emitting its own non-retail ??0/??1 AutoDepositUpdateModuleData COMDATs (the
// ctors/dtor are retail-owned by AutoDepositUpdateModuleDataCtor/Dtor.cpp).
// Defining the tag constructor emits the vftable and the deleting destructor;
// the default constructor and the destructor are declared only, so the link
// keeps the rowed owners' bodies (the pattern of
// Code/GameEngine/Source/Common/FamilyDeletingDtors_muse-4f8a.cpp).
struct EmitVtableTag;

class AutoDepositUpdateModuleData : public UpdateModuleData
{
public:

	UnsignedInt m_depositFrame;
	Int m_depositAmount;
	Int m_initialCaptureBonus;
	Bool m_isActualMoney;
	std::list<upgradePair> m_upgradeBoost;

	AutoDepositUpdateModuleData();
	AutoDepositUpdateModuleData( EmitVtableTag * );
	virtual ~AutoDepositUpdateModuleData();

	static void buildFieldParse(MultiIniFieldParse& p) 
	{
    UpdateModuleData::buildFieldParse(p);
		static const FieldParse dataFieldParse[] = 
		{
			{ "DepositTiming",					INI::parseDurationUnsignedInt,		NULL, offsetof( AutoDepositUpdateModuleData, m_depositFrame ) },
			{ "DepositAmount",					INI::parseInt,		NULL, offsetof( AutoDepositUpdateModuleData, m_depositAmount ) },
			{ "InitialCaptureBonus",		INI::parseInt,		NULL, offsetof( AutoDepositUpdateModuleData, m_initialCaptureBonus ) },
			{ "ActualMoney",						INI::parseBool,		NULL, offsetof( AutoDepositUpdateModuleData, m_isActualMoney ) },
			{ "UpgradedBoost",					parseUpgradePair,		NULL, offsetof( AutoDepositUpdateModuleData, m_upgradeBoost ) },
			{ 0, 0, 0, 0 }
		};
    p.add(dataFieldParse);
	}
};


//-------------------------------------------------------------------------------------------------
class AutoDepositUpdate : public UpdateModule
{

	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( AutoDepositUpdate, "AutoDepositUpdate" )
	MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA( AutoDepositUpdate, AutoDepositUpdateModuleData )

public:

	AutoDepositUpdate( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype provided by memory pool declaration

	void awardInitialCaptureBonus( Player *player );	// Test and award the initial capture bonus
	virtual UpdateSleepTime update( void );

protected:

	Int getUpgradedSupplyBoost() const;

	UnsignedInt m_depositOnFrame;
	Bool m_awardInitialCaptureBonus;
	Bool m_initialized;

};


//-----------------------------------------------------------------------------
// INLINING ///////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// EXTERNALS //////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

#endif // __AUTO_DEPOSIT_UPDATE_H_
