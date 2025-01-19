#pragma once

#include "typedefs.h"
#include "util.h"
#include <concepts>
#include <cstdint>
#include <fmt/core.h>
#include <string>

#include "cpu.h"

#define NES_INSN_DEFN(mnemonic)                                                \
  template <typename ObjType>                                                  \
    requires InsnMemIF<ObjType>                                                \
  static inline bool nes##_##mnemonic##_##insn(                                \
      Opcode opcode, cpu::RegisterBlock &reg_block, ObjType &mem)

#define NES_INSN(mnemonic) nemus::insn::nes##_##mnemonic##_##insn

namespace nemus::insn {

/** Concept which provides a memory interface to NES instructions. */
template <typename ObjType>
concept InsnMemIF =
    requires(ObjType obj, Addr16 addr, Size8 size, Data16 data) {
      { obj.read(addr, size) } -> std::same_as<std::pair<bool, Data16>>;
      { obj.write(addr, size, data) } -> std::same_as<bool>;
      { obj.read_rom(addr, size) } -> std::same_as<std::pair<bool, Data16>>;
      { obj.write_rom(addr, size, data) } -> std::same_as<bool>;
    };

// clang-format off
/** All addressing modes supported by the ISA*/
enum AddressingModesKind : uint8_t {
  Implicit,        // [opcode 1B]
  Accumulator,     // [opcode 1B]              -> accumulator source and destination
  Immediate,       // [opcode 1B] [operand 1B] -> 16-bit address = operand
  ZeroPage,        // [opcode 1B] [operand 1B] -> operand is an 8-bit address in the ZeroPage Range
  ZeroPageX,       // [opcode 1B] [operand 1B] -> 8-bit address = operand + X
  ZeroPageY,       // [opcode 1B] [operand 1B] -> 8-bit address = operand + Y
  Relative,        // [opcode 1B] [operand 1B] -> Signed 8-bit address -> PC + operand
  Absolute,        // [opcode 1B] [operand 2B] -> 16-bit operand (LSB first)
  AbsoluteX,       // [opcode 1B] [operand 2B] -> 16-bit operand (LSB first) + X
  AbsoluteY,       // [opcode 1B] [operand 2B] -> 16-bit operand (LSB first) + Y
  Indirect,        // [opcode 1B] [operand 2B] -> 16-bit address = memory[operand+1] (msb) | memory[operand] (lsb) 
  IndexedIndirect, // [opcode 1B] [operand 1B] -> 16-bit address = memory[operand+X+1] (msb) | memory[operand+X] (lsb)  
  IndirectIndexed  // [opcode 1B] [operand 1B] -> 16-bit address =  (memory[operand+1] (msb) | memory[operand] (lsb)) + Y
};
// clang-format on

// -----------------------------------------------------------------------------
// ------------- Only instruction definitions from point onwards ---------------
// -----------------------------------------------------------------------------

static inline void invalid_instruction(Opcode opcode) {
  fmt::println("Invalid opcode supplied: {:#02x}", opcode);
  std::exit(-1);
};

NES_INSN_DEFN(asl) {
  Reg8 old_value;
  Reg8 new_value;
  switch (opcode) {
  case 0x0A: {
    old_value = reg_block.m_accm;
    new_value = old_value << 1;
    reg_block.m_accm = new_value;
    break;
  }
  case 0x06: {
    Data16 addr = mem.read_rom(reg_block.m_pc + 1, 1);
    old_value = mem.read(addr, 1);
    new_value = old_value << 1;
    mem.write(addr, 1, new_value);
    break;
  }
  case 0x16: {
    Data16 addr = mem.read_rom(reg_block.m_pc + 1, 1);
    Reg8 xreg = reg_block.m_index_x;
    old_value = mem.read(addr + xreg, 1);
    new_value = old_value << 1;
    mem.write(addr + xreg, 1, new_value);
    break;
  }
  case 0x0E: { // Absolute
    Data16 addr = utils::swap_msb_lsb(mem.read_rom(reg_block.m_pc + 1, 2));
    old_value = mem.read(addr, 1);
    new_value = old_value << 1;
    mem.write(addr, 1, new_value);
    break;
  }
  case 0x1E: { // AbsoluteX
    Data16 addr = utils::swap_msb_lsb(mem.read_rom(reg_block.m_pc + 1, 2));
    Reg8 xreg = reg_block.m_index_x;
    old_value = mem.read(addr + xreg, 1);
    new_value = old_value << 1;
    mem.write(addr + xreg, 1, new_value);
    break;
  }
  default:
    return false;
  }

  if (new_value == 0) {
    reg_block.set_z_flag();
  } else {
    reg_block.clear_z_flag();
  }
  if (new_value & 0b10000000) {
    reg_block.set_n_flag();
  }
  if (old_value & 0b10000000) {
    reg_block.set_c_flag();
  } else {
    reg_block.clear_c_flag();
  }
  return true;
}

} // namespace nemus::insn
