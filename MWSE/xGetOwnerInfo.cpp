/************************************************************************
	
	xGetOwnerInfo.cpp - Copyright (c) 2008 The MWSE Project
	https://github.com/MWSE/MWSE/

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
	
**************************************************************************/

#include "VMExecuteInterface.h"
#include "Stack.h"
#include "InstructionInterface.h"
#include "TES3Util.h"

#include "TES3GlobalVariable.h"
#include "TES3Faction.h"

using namespace mwse;

namespace mwse
{
	class xGetOwnerInfo : mwse::InstructionInterface_t
	{
	public:
		xGetOwnerInfo();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static xGetOwnerInfo xGetOwnerInfoInstance;

	xGetOwnerInfo::xGetOwnerInfo() : mwse::InstructionInterface_t(OpCode::xGetOwnerInfo) {}

	void xGetOwnerInfo::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xGetOwnerInfo::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		mwString id = NULL;
		mwLong rank = 0;
		mwLong type = 0;

		// Get reference.
		TES3::Reference* reference = virtualMachine.getReference();
		if (reference) {
			// Get the attached varnode as owner information.
			TES3::OwnershipAttachment* ownerInfo = reinterpret_cast<TES3::OwnershipAttachment*>(tes3::getAttachedVarHolderNode(reference));
			if (ownerInfo) {
				TES3::BaseObject* owner = ownerInfo->owner;
				if (owner) {
					type = owner->objectType;
					if (type == TES3::ObjectType::NPC) {
						id = owner->objectID;
						if (ownerInfo->rankVar.variable) {
							rank = mwse::string::store::getOrCreate(reinterpret_cast<TES3::GlobalVariable*>(ownerInfo->rankVar.variable)->name);
						}
					}
					else if (type == TES3::ObjectType::Faction) {
						TES3::Faction * faction = reinterpret_cast<TES3::Faction*>(owner);
						id = faction->objectID;
						rank = ownerInfo->rankVar.rank;
					}
					else {
#if _DEBUG
						mwse::log::getLog() << "xGetOwnerInfo: Owner was of unhandled type " << type << "." << std::endl;
#endif
					}
				}
			}
			else {
#if _DEBUG
				mwse::log::getLog() << "xGetOwnerInfo: Could not obtain attached VARNODE." << std::endl;
#endif
			}
		} else {
#if _DEBUG
			mwse::log::getLog() << "xGetOwnerInfo: No reference provided." << std::endl;
#endif
		}

		mwse::Stack::getInstance().pushLong(rank);
		mwse::Stack::getInstance().pushString(id);
		mwse::Stack::getInstance().pushLong(type);

		return 0.0f;
	}
}