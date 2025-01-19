#pragma once

#include "interconnect.h"
#include "typedefs.h"
#include <cstdint>
#include <utility>

namespace nemus::cpu {

/**
 * The Register block for the NES CPU. The NES only has 6 registers
 * in the CPU.
 */
struct RegisterBlock {
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

  /** various getters and setters for Status Register flags. */
  void set_n_flag() { m_status = (m_status | 0b10000000); };
  void set_v_flag() { m_status = (m_status | 0b01000000); };
  void set_b_flag() { m_status = (m_status | 0b00010000); };
  void set_i_flag() { m_status = (m_status | 0b00001000); };
  void set_d_flag() { m_status = (m_status | 0b00000100); };
  void set_z_flag() { m_status = (m_status | 0b00000010); };
  void set_c_flag() { m_status = (m_status | 0b00000001); };

  void clear_n_flag() { m_status = (m_status & ~0b10000000); };
  void clear_v_flag() { m_status = (m_status & ~0b01000000); };
  void clear_b_flag() { m_status = (m_status & ~0b00010000); };
  void clear_i_flag() { m_status = (m_status & ~0b00001000); };
  void clear_d_flag() { m_status = (m_status & ~0b00000100); };
  void clear_z_flag() { m_status = (m_status & ~0b00000010); };
  void clear_c_flag() { m_status = (m_status & ~0b00000001); };

  Reg8 get_n_flag() { return (m_status & 0b10000000 >> 7); };
  Reg8 get_v_flag() { return (m_status & 0b01000000 >> 6); };
  Reg8 get_b_flag() { return (m_status & 0b00010000 >> 4); };
  Reg8 get_i_flag() { return (m_status & 0b00001000 >> 3); };
  Reg8 get_d_flag() { return (m_status & 0b00000100 >> 2); };
  Reg8 get_z_flag() { return (m_status & 0b00000010 >> 1); };
  Reg8 get_c_flag() { return (m_status & 0b00000001 >> 0); };
};

/**
 * NESCpu class represents the CPU in NES. It inherits from ICNode
 * which means that it is connected to the interconnect and can send
 * and receive messages to/from the interconnect. The NESCpu also
 * satisfies the InsnMemIfc concept, as a result it can passed as
 * a reference all NES instructions, and also act as a memory interface
 * from NES instructions.
 * */
class NESCpu : public interconnect::ICNode {
public:
  NESCpu();
  bool recieve(interconnect::ICMessage &) override;
  RegisterBlock &get_reg_block();

  std::pair<bool, Data16> read(Addr16 addr, Size8 size);
  bool write(Addr16 addr, Size8 size, Data16 data);
  std::pair<bool, Data16> read_rom(Addr16 addr, Size8 size);
  bool write_rom(Addr16 addr, Size8 size, Data16 data);

private:
  RegisterBlock m_regblock;
};

} // namespace nemus::cpu
