#pragma once

/*
 *   This file is part of libn3ds
 *   Copyright (C) 2025 derrek, profi200
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
#include "mem_map.h"

#ifdef __ARM9__
#define PRNG_REGS_BASE (IO_AHB_BASE + 0x11000) 
#endif // #ifdef __ARM9__

typedef struct
{
	const vu32 rand0;
    u8 _0x4[0xc];
    const vu32 rand1;
    u8 _0x14[0xc];
    const vu32 seed;
} Prng;
static_assert(offsetof(Prng, seed) == 0x20, "Error: Member seed of Prng is not at offset 0x20!");

#ifdef __ARM9__
ALWAYS_INLINE Prng const* getPrngRegs(void)
{
	return (Prng*)PRNG_REGS_BASE;
}
#endif // #ifdef __ARM9__

#ifdef __cplusplus
extern "C"
{
#endif

u32 PRNG_GetSeed(void);
u32 PRNG_GetRand0(void);
u32 PRNG_GetRand1(void);

#ifdef __cplusplus
} // extern "C"
#endif