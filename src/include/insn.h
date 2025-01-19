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

  reg_block.update_z_flag(new_value);
  if (new_value & 0b10000000) {
    reg_block.update_n_flag(new_value);
  }
  reg_block.update_c_flag(old_value & 0x80);
  return true;
}

NES_INSN_DEFN(and) {
  Reg8 old_value;
  Reg8 new_value;
  switch (opcode) {
  case 0x29: { // Immediate
    Data16 opr = mem.read_rom(reg_block.m_pc + 1, 1);
    old_value = reg_block.m_accm;
    new_value = old_value & opr;
    reg_block.m_accm = new_value;
    break;
  }
  case 0x25: { // Zero Page
    Data16 addr = mem.read_rom(reg_block.m_pc + 1, 1);
    old_value = mem.read(addr, 1);
    new_value = reg_block.m_accm & old_value;
    reg_block.m_accm = new_value;
    break;
  }
  case 0x35: { // Zero Page, X
    Data16 addr = mem.read_rom(reg_block.m_pc + 1, 1);
    Reg8 xreg = reg_block.m_index_x;
    old_value = mem.read(addr + xreg, 1);
    new_value = old_value & reg_block.m_accm;
    reg_block.m_accm = new_value;
    break;
  }
  case 0x2D: { // Absolute
    Data16 addr = mem.read_rom(reg_block.m_pc + 1, 2);
    old_value = mem.read(addr, 1);
    new_value = old_value & reg_block.m_accm;
    reg_block.m_accm = new_value;
    break;
  }
  case 0x3D: { // Absolute, X
    Data16 addr = mem.read_rom(reg_block.m_pc + 1, 2);
    Reg8 xreg = reg_block.m_index_x;
    old_value = mem.read(addr + xreg, 1);
    new_value = old_value & reg_block.m_accm;
    reg_block.m_accm = new_value;
    break;
  }
  case 0x39: { // Absolute, Y
    Data16 addr = mem.read_rom(reg_block.m_pc + 1, 2);
    Reg8 yreg = reg_block.m_index_y;
    old_value = mem.read(addr + yreg, 1);
    new_value = old_value & reg_block.m_accm;
    reg_block.m_accm = new_value;
    break;
  }
  case 0x21: { // Indirect, X
    Reg8 xreg = reg_block.m_index_x;
    Data16 addr = mem.read_rom(reg_block.m_pc + 1, 2);
    addr = addr + xreg;
    Data16 taddr = mem.read(addr, 2);
    old_value = mem.read(taddr, 1);
    new_value = old_value & reg_block.m_accm;
    reg_block.m_accm = new_value;
    break;
  }
  case 0x31: { // Indirect, Y
    Reg8 yreg = reg_block.m_index_y;
    Data16 opr = mem.read_rom(reg_block.m_pc + 1, 2);
    Data16 addr = mem.read_rom(opr + yreg);
    Data16 taddr = addr + yreg;
    old_value = mem.read(taddr, 1);
    new_value = old_value & reg_block.m_accm;
    reg_block.m_accm = new_value;
    break;
  }
  default:
    return false;
  }
  reg_block.update_z_flag(new_value);
  if (new_value & 0x80) {
    reg_block.update_n_flag(new_value);
  }
  reg_block.update_c_flag(old_value & 0x80);
  return true;
};
} // namespace nemus::insn
