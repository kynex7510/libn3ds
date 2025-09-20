/*
 *   This file is part of open_agb_firm
 *   Copyright (C) 2021 derrek, profi200
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
#include "drivers/prng.h"
#include "drivers/pxi.h"
#include "ipc_handler.h"

u32 PRNG_GetSeed(void)
{
    u32 seed;
    const u32 cmdBuf[2] = {(u32)&seed, sizeof(u32)};
    PXI_sendCmd(IPC_CMD9_PRNG_GET_SEED, cmdBuf, 2);
    return seed;
}

u32 PRNG_GetRand0(void)
{
    u32 rand0;
    const u32 cmdBuf[2] = {(u32)&rand0, sizeof(u32)};
    PXI_sendCmd(IPC_CMD9_PRNG_GET_RAND0, cmdBuf, 2);
    return rand0;
}

u32 PRNG_GetRand1(void)
{
    u32 rand1;
    const u32 cmdBuf[2] = {(u32)&rand1, sizeof(u32)};
    PXI_sendCmd(IPC_CMD9_PRNG_GET_RAND1, cmdBuf, 2);
    return rand1;
}