#pragma once

#include "interconnect.h"
#include "typedefs.h"
#include <cstdint>

namespace nemus::cpu {

/**
 * The Register block for the NES CPU. The NES only has 6 registers
 * in the CPU.
 */
struct RegiserBlock {
  /** The Program Counter Register. */
  Reg16 m_pc;
  /** The Stack Pointer Register. */
  Reg8 m_stack_ptr;
  /** The Accumulator Register. */
  Reg8 m_accm;
  /** The Index Register X. */
  Reg8 m_index_x;
  /** The Index Register Y. */
  Reg8 m_index_y;
  /** The Status Register. */
  Reg8 m_status;
};

class NESCpu : public interconnect::ICNode {
public:
  NESCpu();
  bool recieve(interconnect::ICMessage &) override;
  RegiserBlock &get_reg_block();
  uint16_t read(Addr16 addr, uint8_t size);
  bool write(Addr16 addr, uint8_t size, uint16_t data);

private:
  RegiserBlock &m_regblock;
};

} // namespace nemus::cpu
