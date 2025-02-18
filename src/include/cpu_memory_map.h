#pragma once

#include "typedefs.h"
#include "util.h"

namespace nemus::cpummap {
using namespace utils;
/** Zero Page Range. */
constexpr range<Addr16> zero_page_range =
    range<Addr16>(0x0, 0x100, "Zero Page Address Range in the CPU Memory Map");

/** Stack range. */
constexpr range<Addr16> stack_range =
    range<Addr16>(0x0100, 0x0100, "Stack Address Range in the CPU Memory Map");

/** Ram range. */
constexpr range<Addr16> ram_range =
    range<Addr16>(0x0200, 0x0600, "RAM Address Range in the CPU Memory Map");

/** Lower Mirror range. */
constexpr range<Addr16> lower_mirror_range = range<Addr16>(
    0x0800, 0x1800, "Lower Mirror Address Range in the CPU Memory Map");

/** Lower I/O Registers. */
constexpr range<Addr16> lower_io_reg_range = range<Addr16>(
    0x2000, 0x0008, "Lower I/O Registers Address Range in the CPU Memory Map");

/** Upper Mirror range. */
constexpr range<Addr16> upper_mirror_range = range<Addr16>(
    0x2008, 0x1FF8, "Upper Mirror Address Range in the CPU Memory Map");

/** Upper I/O Registers. */
constexpr range<Addr16> upper_io_reg_range = range<Addr16>(
    0x4000, 0x0020, "Upper I/O Registers Address Range in the CPU Memory Map");

/** Expansion ROM. */
constexpr range<Addr16> expansion_rom_range = range<Addr16>(
    0x4020, 0x1FE0, "Expansion ROM Address Range in the CPU Memory Map");

/** SRAM. */
constexpr range<Addr16> sram_range =
    range<Addr16>(0x6000, 0x2000, "SRAM Address Range in the CPU Memory Map");

/** PRG-ROM Lower Bank. */
constexpr range<Addr16> lower_prg_rom_range = range<Addr16>(
    0x8000, 0x4000, "PRG-ROM Lower Bank Address Range in the CPU Memory Map");

/** PRG-ROM Upper Bank. */
constexpr range<Addr16> upper_prg_rom_range = range<Addr16>(
    0xC000, 0x4000, "PRG-ROM Upper Bank Address Range in the CPU Memory Map");

} // namespace nemus::cpummap
