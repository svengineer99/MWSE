/************************************************************************
	
	xSetSpellInfo.cpp - Copyright (c) 2008 The MWSE Project
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

#include "TES3Spell.h"

using namespace mwse;

namespace mwse
{
	class xSetSpellInfo : mwse::InstructionInterface_t
	{
	public:
		xSetSpellInfo();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static xSetSpellInfo xSetSpellInfoInstance;

	xSetSpellInfo::xSetSpellInfo() : mwse::InstructionInterface_t(OpCode::xSetSpellInfo) {}

	void xSetSpellInfo::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xSetSpellInfo::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		// Get parameters.
		mwseString_t& spellId = virtualMachine.getString(mwse::Stack::getInstance().popLong());
		mwLong nameId = mwse::Stack::getInstance().popLong();
		mwLong type = mwse::Stack::getInstance().popLong();
		mwLong cost = mwse::Stack::getInstance().popLong();
		mwLong flags = mwse::Stack::getInstance().popLong();
		mwLong origin = mwse::Stack::getInstance().popLong();

		// Validate spell type.
		if (type < TES3::FirstSpellType || type > TES3::LastSpellType) {
#if _DEBUG
			mwse::log::getLog() << "xSetSpellInfo: Spell type out of range: " << type << std::endl;
#endif
			mwse::Stack::getInstance().pushLong(false);
			return 0.0f;
		}

		// Validate spell flags.
		if (flags < TES3::NoSpellFlags || flags > TES3::AllSpellFlags) {
#if _DEBUG
			mwse::log::getLog() << "xSetSpellInfo: Spell flags out of range: " << flags << std::endl;
#endif
			mwse::Stack::getInstance().pushLong(false);
			return 0.0f;
		}

		// Validate spell origin.
		if (origin != 0 && (origin < TES3::SpellOriginsFirst || origin > TES3::SpellOriginsLast)) {
#if _DEBUG
			mwse::log::getLog() << "xSetSpellInfo: Spell origin out of range: " << origin << std::endl;
#endif
			mwse::Stack::getInstance().pushLong(false);
			return 0.0f;
		}

		// Get spell data by id.
		TES3::Spell* spell = tes3::getSpellRecordById(spellId);
		if (spell == NULL) {
#if _DEBUG
			mwse::log::getLog() << "xSetSpellInfo: Could not find spell of id '" << spellId << "'" << std::endl;
#endif
			mwse::Stack::getInstance().pushLong(false);
			return 0.0f;
		}

		// Set spell name if one is provided.
		if (nameId) {
			mwseString_t& name = virtualMachine.getString(nameId);
			if (name.length() > 31) {
#if _DEBUG
				mwse::log::getLog() << "xSetSpellInfo: Given name must be 31 characters or less." << std::endl;
#endif
				mwse::Stack::getInstance().pushLong(false);
				return 0.0f;
			}
			
			// Expand name length if needed.
			if (name.length() > strlen(spell->name)) {
				spell->name = reinterpret_cast<char*>(tes3::realloc(spell->name, 32));
			}

			// Copy name over.
			strcpy(spell->name, name.c_str());
		}

		// Set cost.
		if (flags & TES3::AutoCalculateCost && !(spell->flags & TES3::AutoCalculateCost)) {
			//! TODO: Recalculate spell cost.
		}
		else if (!(flags & TES3::AutoCalculateCost)) {
			spell->cost = cost;
		}

		// Set other information.
		spell->type = type;
		spell->flags = flags;
		if (origin != 0) {
			spell->origin = origin;
		}

		// Report success.
		mwse::Stack::getInstance().pushLong(true);

		return 0.0f;
	}
}