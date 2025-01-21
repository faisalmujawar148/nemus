#pragma once

#include "cpu.h"
#include "typedefs.h"
#include "util.h"
#include <concepts>
#include <cstdint>
#include <fmt/core.h>
#include <iostream>
#include <string>

#define NES_INSN_DEFN(mnemonic)                                                \
  template <typename ObjType>                                                  \
    requires InsnMemIF<ObjType>                                                \
  static inline bool nes##_##mnemonic##_##insn(                                \
      Opcode opcode, cpu::RegisterBlock &reg_block, ObjType &mem)

#define NES_INSN(mnemonic) nemus::insn::nes##_##mnemonic##_##insn

namespace nemus::insn {

enum AddressingModesKind : uint8_t;

/** Concept which provides a memory interface to NES instructions. */
template <typename ObjType>
concept InsnMemIF = requires(ObjType obj, Addr16 addr, Size8 size, Data16 data,
                             AddressingModesKind addr_mode, Addr16 pc) {
  { obj.read(addr, size) } -> std::same_as<Data16>;
  { obj.write(addr, size, data) } -> std::same_as<bool>;
  { obj.read_rom(addr, size) } -> std::same_as<Data16>;
  { obj.write_rom(addr, size, data) } -> std::same_as<bool>;
  { obj.read_insn_operands(addr_mode, pc = 0) } -> std::same_as<Data16>;
};

// clang-format off
/** All addressing modes supported by the ISA. */
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
} // namespace nemus::insn
