/************************************************************************

	xFirstNPC.cpp - Copyright (c) 2008 The MWSE Project
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

#include "TES3CellMaster.h"

using namespace mwse;

namespace mwse
{
	class xFirstNPC : mwse::InstructionInterface_t
	{
	public:
		xFirstNPC();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static xFirstNPC xFirstNPCInstance;

	xFirstNPC::xFirstNPC() : mwse::InstructionInterface_t(OpCode::xFirstNPC) {}

	void xFirstNPC::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xFirstNPC::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		// Clear elements in our stored exterior ref list.
		mwse::tes3::clearExteriorRefs();

		TES3::Reference* reference = NULL;
		TES3::CellMaster* cellMaster = mwse::tes3::getCellMaster();
		if (cellMaster->interiorCell != NULL) {
			reference = mwse::tes3::skipRemovedReferences(cellMaster->interiorCell->npc.first);
		}
		else {
			TES3::CellPointer* cellPointer = cellMaster->exteriorCells[TES3::CellGridCenter];
			if (cellPointer->size == 1) {
				// Get the start of the list for the center cell. We'll check that it's valid later.
				reference = mwse::tes3::skipRemovedReferences(cellPointer->cell->npc.first);
				int exteriorCount = 0;
				for (int i = 0; i < 9; i++) {
					if (i == TES3::CellGridCenter) {
						continue;
					}

					cellPointer = cellMaster->exteriorCells[i];
					if (cellPointer->size == 1) {
						TES3::Reference* tempReference = mwse::tes3::skipRemovedReferences(cellPointer->cell->npc.first);
						if (tempReference != NULL) {
							mwse::tes3::exteriorRefs[exteriorCount] = tempReference;
							exteriorCount++;
						}
					}
					else {
						mwse::log::getLog() << "xFirstNPC: Exterior size is " << cellPointer->size << ". Skipping exterior " << i << "." << std::endl;
					}
				}
				
				// Make sure that we end our list with a NULL, so we know we're done.
				mwse::tes3::exteriorRefs[exteriorCount] = NULL;

				// Make sure the reference in the center cell is valid.
				// If not, use the reference from another exterior cell.
				if (reference == NULL && exteriorCount > 0) {
					exteriorCount--;
					reference = mwse::tes3::exteriorRefs[exteriorCount];
					mwse::tes3::exteriorRefs[exteriorCount] = NULL;
				}
			}
		}

		mwse::Stack::getInstance().pushLong((mwLong)reference);

		return 0.0f;
	}
}