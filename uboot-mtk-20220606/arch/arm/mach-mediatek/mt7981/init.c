// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020 MediaTek Inc.
 * Author: Sam Shih <sam.shih@mediatek.com>
 */

#include <common.h>
#include <fdtdec.h>
#include <asm/armv8/mmu.h>
#include <init.h>
#include <asm/system.h>
#include <asm/global_data.h>

#ifdef CONFIG_DEBUG_UART
#include <debug_uart.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

int print_cpuinfo(void)
{
	printf("CPU:   MediaTek MT7981\n");
	return 0;
}

int dram_init(void)
{
	gd->ram_size = get_ram_size((void *)CONFIG_SYS_SDRAM_BASE, SZ_2G);

	return 0;
}

void reset_cpu(ulong addr)
{
	psci_system_reset();
}

static struct mm_region mt7981_mem_map[] = {
	{
		/* DDR */
		.virt = 0x40000000UL,
		.phys = 0x40000000UL,
		.size = 0x80000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) | PTE_BLOCK_OUTER_SHARE,
	}, {
		.virt = 0x00000000UL,
		.phys = 0x00000000UL,
		.size = 0x40000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		0,
	}
};

struct mm_region *mem_map = mt7981_mem_map;
