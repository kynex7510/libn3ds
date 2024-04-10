#pragma once

/*
 *   This file is part of libn3ds
 *   Copyright (C) 2019 Aurora Wright, TuxSH, derrek, profi200
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "types.h"



#ifdef __cplusplus
extern "C"
{
#endif

// Based on https://github.com/LumaTeam/Luma3DS/blob/master/arm9/source/alignedseqmemcpy.s

void copy32(u32 *restrict dst, const u32 *restrict src, u32 size);
void clear32(u32 *ptr, const u32 value, u32 size);

#ifdef __cplusplus
} // extern "C"
#endif