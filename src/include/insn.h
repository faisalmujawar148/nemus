#include "typedefs.h"
#include <cstdint>
#include <fmt/core.h>
#include <string>

#include "cpu.h"

namespace nemus::insn {

// clang-format off
/** All addressing modes supported by the ISA*/
enum AddressingModesKind : uint8_t {
  Implicit,        // [opcode 1B]
  Accumulator,     // [opcode 1B]              -> accumulator source and destination
  Immediate,       // [opcode 1B] [operand 2B] -> 16-bit address = operand
  ZeroPage,        // [opcode 1B] [operand 1B] -> operand is an 8-bit address in the ZeroPage Range
  ZeroPageX,       // [opcode 1B] [operand 1B] -> 8-bit address = operand + X
  ZeroPageY,       // [opcode 1B] [operand 1B] -> 8-bit address = operand + Y
  Relative,        // [opcode 1B] [operand 1B] -> Signed 8-bit address -> PC + operand
  Absolute,        // [opcode 1B] [operand 2B] -> 16-bit operand (LSB first)
  AbsoluteX,       // [opcode 1B] [operand 2B] -> 16-bit operand (LSB first) + X
  AbsoluteY,       // [opcode 1B] [operand 2B] -> 16-bit operand (LSB first) + Y
  Indirect,        // [opcode 1B] [operand 2B] -> 16-bit address = memory[operand+1] (msb) | memory[operand] (lsb) 
  IndexedIndirect, // [opcode 1B] [operand 2B] -> 16-bit address = memory[operand+X+1] (msb) | memory[operand+X] (lsb)  
  IndirectIndexed  // [opcode 1B] [operand 2B] -> 16-bit address =  (memory[operand+1] (msb) | memory[operand] (lsb)) + Y
};
// clang-format on

static inline void invalid_instruction(Opcode opcode, cpu::NESCpu &cpu) {
  fmt::println("Invalid opcode supplied: {:#02x}", opcode);
  std::exit(-1);
};

/** Bitwise AND. */
static inline bool and_insn(Opcode opcode, cpu::NESCpu &cpu) {
  auto &regblck = cpu.get_reg_block();
  switch (opcode) {
  case 0x29: // bitwise AND 
    uint16_t opr = cpu.read(regblck.m_pc + 1, 1);
    uint8_t accm = regblock.m_accm;
    return accm&opr;
  }
};
} // namespace nemus::insn
