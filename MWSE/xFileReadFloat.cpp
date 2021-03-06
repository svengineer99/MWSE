/************************************************************************
	
	xFileReadFloat.cpp - Copyright (c) 2008 The MWSE Project
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
#include "FileUtil.h"

#include <list>

using namespace mwse;

namespace mwse
{
	class xFileReadFloat : mwse::InstructionInterface_t
	{
	public:
		xFileReadFloat();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static xFileReadFloat xFileReadFloatInstance;

	xFileReadFloat::xFileReadFloat() : mwse::InstructionInterface_t(OpCode::xFileReadFloat) {}
	
	void xFileReadFloat::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xFileReadFloat::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		if (mwse::Stack::getInstance().size() < 2) {
			mwse::log::getLog() << "xFileReadFloat: Function called with too few arguments." << std::endl;
			return 0.0f;
		}

		// Get arguments from the stack.
		mwseString_t& fileName = virtualMachine.getString(mwse::Stack::getInstance().popLong());
		mwLong count = mwse::Stack::getInstance().popLong();

		// Gather values into a temporary list, so they aren't in reverse order.
		mwLong valuesRead = 0;
		std::list<mwFloat> values;
		for (mwLong i = 0; i < count; i++) {
			try {
				mwFloat value = mwse::FileSystem::getInstance().readFloat(fileName.c_str());
				values.push_front(value);
				valuesRead++;
			}
			catch (std::exception& e) {
				values.push_front(0.0f);
			}
		}

		// Copy values from the temporary vector to the stack.
		while (!values.empty()) {
			mwse::Stack::getInstance().pushFloat(values.front());
			values.pop_front();
		}
		mwse::Stack::getInstance().pushLong(valuesRead);

		return 0.0f;
	}
}