/************************************************************************
	
	mwseOffsets.h - Copyright (c) 2008 The MWSE Project
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

#pragma once

//
// Addresses for game data.
//

#define TES3_IP_IMAGE 0x7CEBB0
#define TES3_OP_IMAGE 0x7A91C4

#define TES3_LOCALVARIABLES_IMAGE 0x7CEBF8
#define TES3_SCRIPTTARGETREF_IMAGE 0x7CEBEC
#define TES3_SCRIPTTARGETTEMPL_IMAGE 0x7CEBF4
#define TES3_SECONDOBJECT_IMAGE 0x7CE6F8
#define TES3_SECONDOBJECT_LENGTH_IMAGE 0x7CEBB8
#define TES3_VARINDEX_IMAGE 0x7CEBB4

#define TES3_MASTER_IMAGE 0x7C67DC
#define TES3_VIEWMASTER_IMAGE 0x7C6CDC

// Master cell image. Use tes3::getCellMaster() instead of fetching manually.
#define TES3_MASTERCELL_IMAGE 0x7C67E0

#define TES3_DESTINATION_X_IMAGE 0x7CEA48
#define TES3_DESTINATION_Y_IMAGE 0x7CEA4C
#define TES3_DESTINATION_Z_IMAGE 0x7CEA50

#define TES3_TARGET_ROTX_IMAGE 0x7CEB08
#define TES3_TARGET_ROTY_IMAGE 0x7CEB0C
#define TES3_TARGET_ROTZ_IMAGE 0x7CEB10

//
// Hooking positions.
//

#define TES3_HOOK_GET_NEXT_INSTRUCTION 0x50055B
#define TES3_HOOK_GET_NEXT_INSTRUCTION_SIZE 0x6
#define TES3_HOOK_GET_NEXT_INSTRUCTION_RETURN (TES3_HOOK_GET_NEXT_INSTRUCTION + TES3_HOOK_GET_NEXT_INSTRUCTION_SIZE)

#define TES3_HOOK_RUN_FUNCTION 0x505831
#define TES3_HOOK_RUN_FUNCTION_SIZE 0x6
#define TES3_HOOK_RUN_FUNCTION_RETURN (TES3_HOOK_RUN_FUNCTION + TES3_HOOK_RUN_FUNCTION_SIZE)

#define TES3_HOOK_PLACE_GETREFERENCE 0x509992
#define TES3_HOOK_PLACE_GETREFERENCE_SIZE 0x6
#define TES3_HOOK_PLACE_GETREFERENCE_RETURN (TES3_HOOK_PLACE_GETREFERENCE + TES3_HOOK_PLACE_GETREFERENCE_SIZE)

//
// Addresses for in-function offsets.
//

#define TES3_INFUNC_RUN_SCRIPT_OPCODE 0x505793;
#define TES3_INFUNC_SCRIPT_ADD_ITEM 0x508B54;
#define TES3_MALLOC 0x749471C0
#define TES3_FREE 0x74947000
#define TES3_REALLOC 0x749472B0

//
// Addresses for game functions.
//

#define TES3_FUNC_GET_MACP 0x40FF20
#define TES3_FUNC_LOAD_MESSAGE 0x40F930
#define TES3_FUNC_FIXUP_INSTANCE 0x4B8F50
#define TES3_FUNC_FIXUP_TEMPLATE 0x4B8B60
#define TES3_FUNC_FIXUP_TEMPLATE2 0x4FE180
#define TES3_FUNC_FIND_SCRIPT 0x4BA700
#define TES3_FUNC_FIND_GLOBAL 0x4BA820
#define TES3_FUNC_SKILL_LEVEL_UP 0x56BBE0
#define TES3_FUNC_FIND_SCRIPT_VARIABLE 0x50E7B0
#define TES3_FUNC_DISPLAY_MESSAGE 0x5F90C0
#define TES3_FUNC_ADD_NEW_OBJECT 0x4B8980
#define TES3_FUNC_FIXUP_SCRIPT 0x4FDB00;
