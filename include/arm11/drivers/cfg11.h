#pragma once

/*
 *   This file is part of libn3ds
 *   Copyright (C) 2024 derrek, profi200
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


#ifdef __cplusplus
extern "C"
{
#endif

#define CFG11_REGS_BASE  (IO_COMMON_BASE + 0x40000)

typedef struct
{
	vu64 dsp_ram_code_cnt;    // 0x000 8 u8 registers combined.
	vu64 dsp_ram_data_cnt;    // 0x008 8 u8 registers combined.
	u8 _0x10[0xf0];
	vu32 nullpage_cnt;        // 0x100
	vu8 fiq_mask;             // 0x104
	vu8 unk105;               // 0x105 Debug related? Mask?
	u8 _0x106[2];
	vu8 unk108;               // 0x108 LGY gamecard related?
	u8 _0x109[3];
	vu8 cdma_cnt;             // 0x10C
	u8 _0x10d[3];
	vu8 unk110;               // 0x110 VRAM related?
	u8 _0x111[0x2f];
	vu16 gpuprot;             // 0x140
	u8 _0x142[0x3e];
	vu8 wifi_power;           // 0x180 Used for flight mode?
	u8 _0x181[0x3f];
	vu16 spi_cnt;             // 0x1C0
	u8 _0x1c2[0x3e];
	vu32 unk200;              // 0x200 GPIO3 related? 8x4 bits.
	u8 _0x204[0x1fc];
	vu8 gpu_n3ds_cnt;         // 0x400 New3DS-only.
	u8 _0x401[0xf];
	vu32 cdma_peripherals;    // 0x410 New3DS-only.
	u8 _0x414[0xc];
	vu8 bootrom_overlay_cnt;  // 0x420 New3DS-only.
	u8 _0x421[3];
	vu32 bootrom_overlay_val; // 0x424 New3DS-only.
	vu8 unk428;               // 0x429 New3DS-only. 1 bit. Enable CPU core 1 access to overlay regs?
	u8 _0x429[0xbd3];
	const vu16 socinfo;       // 0xFFC
} Cfg11;
static_assert(offsetof(Cfg11, socinfo) == 0xFFC, "Error: Member socinfo of Cfg11 is not at offset 0xFFC!");

ALWAYS_INLINE Cfg11* getCfg11Regs(void)
{
	return (Cfg11*)CFG11_REGS_BASE;
}


// REG_DSP_RAM_CODE_CNT[8] and REG_DSP_RAM_DATA_CNT[8].
// Note: All defines for each of the 8 registers.
#define DSP_RAM_MASTER_ARM      (0u)            // Bank master CPU only.
#define DSP_RAM_MASTER_DSP      (1u)            // Bank master DSP. The ARM CPUs still have access.
#define DSP_RAM_OFFS(n)         (((n) & 7u)<<2) // Bank offset in 32 KiB unit. 0-7.
#define DSP_RAM_EN              BIT(7)          // Bank enable.

// REG_CFG11_NULLPAGE_CNT
#define NULLPAGE_CNT_FAULT_EN   BIT(0)  // All data accesses to 0x000-0xFFF generate data aborts.
#define NULLPAGE_CNT_ACCESSED   BIT(16) // 0x000-0xFFF has been accessed flag. Write 0 to clear.

// REG_CFG11_FIQ_MASK
// Each bit 1 = masked/disabled.
#define FIQ_MASK_CPU0           BIT(0)
#define FIQ_MASK_CPU1           BIT(1)
#define FIQ_MASK_CPU2           BIT(2) // New3DS-only.
#define FIQ_MASK_CPU3           BIT(3) // New3DS-only.

// REG_CFG11_CDMA_CNT
#define CDMA_CNT_MIC_EN         BIT(0)
#define CDMA_CNT_NTRCARD_EN     BIT(1)
#define CDMA_CNT_CAM1_EN        BIT(2)
#define CDMA_CNT_CAM2_EN        BIT(3)
#define CDMA_CNT_TMIO2_EN       BIT(4) // WiFi
#define CDMA_CNT_TMIO3_EN       BIT(5)

// REG_CFG11_GPUPROT
// When the lower FCRAM protection is set to non-zero,
// the first 0x800000 bytes of upper FCRAM are protected.
#define GPUPROT_FCRAM_LO(x)     (x)      // Protect lower 128 MiB of FCRAM (0x28000000-(0x800000*x)).
#define GPUPROT_FCRAM_UP(x)     ((x)<<4) // Protect upper 128 MiB of FCRAM (0x30000000-(0x800000*x)) (New3DS-only).
#define GPUPROT_AXIWRAM         BIT(8)   // Protect AXI RAM.
#define GPUPROT_QTM(x)          ((x)<<9) // Protect QTM RAM (0x1F400000-(0x100000*x)). 2 bits. TODO: Confirm this.
#define GPUPROT_NO_PROT         (0u)
#define GPUPROT_PROT_ALL        (GPUPROT_QTM(3u) | GPUPROT_AXIWRAM | \
                                 GPUPROT_FCRAM_UP(15u) | GPUPROT_FCRAM_LO(15u))

// REG_CFG11_WIFI_POWER
#define WIFI_POWER_ON           BIT(0)

// REG_CFG11_SPI_CNT
#define SPI_CNT_SPI1_NEW_IF     BIT(0) // New interface (NSPI).
#define SPI_CNT_SPI2_NEW_IF     BIT(1)
#define SPI_CNT_SPI3_NEW_IF     BIT(2)

// REG_CFG11_GPU_N3DS_CNT
#define GPU_N3DS_CNT_N3DS_MODE  BIT(0) // Enable access to mem extensions.
#define GPU_N3DS_CNT_TEX_FIX    BIT(1) // Fixes some texture glitches in New3DS mode.

// REG_CFG11_CDMA_PERIPHERALS
// Each bit 1 = DMA requests go to CDMA2.
// TODO: Add individual periphals.
#define CDMA_PERIPHERALS_ALL    (0x3FFFFu)

// REG_CFG11_BOOTROM_OVERLAY_CNT
#define BOOTROM_OVERLAY_CNT_EN  BIT(0)

// REG_CFG11_SOCINFO
#define SOCINFO_CTR             BIT(0) // Also set on New 3DS.
#define SOCINFO_LGR1            BIT(1) // Never saw the daylight? Set on retail N3DS (LGR2).
#define SOCINFO_LGR2            BIT(2) // Set on New 3DS.

#ifdef __cplusplus
} // extern "C"
#endif