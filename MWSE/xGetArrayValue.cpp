/************************************************************************
	
	xGetArrayValue.cpp - Copyright (c) 2008 The MWSE Project
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
#include "ArrayUtil.h"

using namespace mwse;

namespace mwse
{
	class xGetArrayValue : mwse::InstructionInterface_t
	{
	public:
		xGetArrayValue();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static xGetArrayValue xGetArrayValueInstance;

	xGetArrayValue::xGetArrayValue() : mwse::InstructionInterface_t(OpCode::xGetArrayValue) {}

	void xGetArrayValue::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xGetArrayValue::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		if (mwse::Stack::getInstance().size() < 2) {
			mwse::log::getLog() << "xGetArrayValue: Function requires 2 arguments." << std::endl;
			mwse::Stack::getInstance().pushLong(0);
			return 0.0f;
		}

		mwLong id = mwse::Stack::getInstance().popLong();
		mwLong index = mwse::Stack::getInstance().popLong();

		mwLong value = mwse::Arrays::getInstance().getValue("xGetArrayValue", id, index);

		mwse::Stack::getInstance().pushLong(value);

		return 0.0f;
	}
}