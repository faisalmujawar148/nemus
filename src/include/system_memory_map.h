#include "typedefs.h" 
#include "util.h"

namespace nemus::sysmmap {
/** Zero Page Range. */
constexpr range<Addr16> zero_page_range = range<Addr16>(
    0x0, 0x100, "Zero Page Address Range in the System Memory Map");
/** Stack range. */
constexpr range<Addr16> stack_range = range<Addr16>(0x0100, 0x0200, "Stack Address Range in the System Memory Map");

/** Ram range. */
constexpr range<Addr16> ram_range = range<Addr16>(0x0200, 0x0800, "RAM Address Range in the System Memory Map");
/** Lower Mirror range. */
constexpr range<Addr16> lower_mirror_range = range<Addr16>(0x0800, 0x2000, "Lower Mirror Address Range in the System Memory Map");

/** Lower I/O Registers. */
constexpr range<Addr16> lower_io_range = range<Addr16>(0x2000, 0x2008, "Lower I/O Address Range in the System Memory Map");
/** Upper Mirror range. */
constexpr range<Addr16> upper_mirror_range = range<Addr16>(0x2000, 0x4000, "Upper Mirror Address Range in the System Memory Map");
/** Upper I/O Registers. */
constexpr range<Addr16> upper_io_range = range<Addr16>(0x4000, 0x4020, "Upper I/O Address Range in the System Memory Map");

/** Expansion ROM. */
constexpr range<Addr16> expansion_rom_range = range<Addr16>(0x4020, 0x6000, "Expansion ROM Address Range in the System Memory Map");

/** SRAM. */
constexpr range<Addr16> sram_range = range<Addr16>(0x6000, 0x8000, "SRAM Address Range in the System Memory Map"); 


/** PRG-ROM Lower Bank. */
constexpr range<Addr16> lower_prg_rom_range = range<Addr16>(0x8000, 0xC000, "PRG-ROM Lower Bank Address Range in the System Memory Map");
/** PRG-ROM Upper Bank. */
constexpr range<Addr16> upper_prg_rom_range = range<Addr16>(0xC000, 0x10000, "PRG-ROM Upper Bank Address Range in the System Memory Map");

} // namespace nemus::sysmmap

