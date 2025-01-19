#pragma once

#include "interconnect.h"
#include "typedefs.h"
#include <cstdint>
#include <iostream>
#include <utility>
namespace nemus::insn {
enum AddressingModesKind : uint8_t;
};

namespace nemus::cpu {

/**
 * The Register block for the NES CPU. The NES only has 6 registers
 * in the CPU.
 */
struct RegisterBlock {
  /** The Program Counter Register. */
  Reg16 m_pc = 0;
  /** The Stack Pointer Register. */
  Reg8 m_stack_ptr = 0;
  /** The Accumulator Register. */
  Reg8 m_accm = 0;
  /** The Index Register X. */
  Reg8 m_index_x = 0;
  /** The Index Register Y. */
  Reg8 m_index_y = 0;
  /** The Status Register. */
  Reg8 m_status = 0;

  /** various getters and setters for Status Register flags. */
  inline Reg8 update_n_flag(bool value) {
    m_status = (m_status & ~0b10000000) | (static_cast<Reg8>(value) << 7);
    return m_status;
  };
  inline Reg8 update_v_flag(bool value) {
    m_status = (m_status & ~0b01000000) | (static_cast<Reg8>(value) << 6);
    return m_status;
  };
  inline Reg8 update_b_flag(bool value) {
    m_status = (m_status & ~0b00010000) | (static_cast<Reg8>(value) << 4);
    return m_status;
  };
  inline Reg8 update_i_flag(bool value) {
    m_status = (m_status & ~0b00001000) | (static_cast<Reg8>(value) << 3);
    return m_status;
  };
  inline Reg8 update_d_flag(bool value) {
    m_status = (m_status & ~0b00000100) | (static_cast<Reg8>(value) << 2);
    return m_status;
  };
  inline Reg8 update_z_flag(bool value) {
    m_status = (m_status & 0b11111101) | (static_cast<Reg8>(value == 0) << 1);

    return m_status;
  };
  inline Reg8 update_c_flag(bool value) {
    m_status = (m_status & ~0b00000001) | (static_cast<Reg8>(value) << 0);
    return m_status;
  };

  Reg8 get_n_flag() { return ((m_status & 0b10000000) >> 7); };
  Reg8 get_v_flag() { return ((m_status & 0b01000000) >> 6); };
  Reg8 get_b_flag() { return ((m_status & 0b00010000) >> 4); };
  Reg8 get_i_flag() { return ((m_status & 0b00001000) >> 3); };
  Reg8 get_d_flag() { return ((m_status & 0b00000100) >> 2); };
  Reg8 get_z_flag() { return ((m_status & 0b00000010) >> 1); };
  Reg8 get_c_flag() { return ((m_status & 0b00000001) >> 0); };

  void increment_pc(insn::AddressingModesKind addr_mode);
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
  std::pair<bool, Data16>
  read_insn_operands(insn::AddressingModesKind addr_mode, Addr16 pc = 0);

private:
  RegisterBlock m_regblock;
};

} // namespace nemus::cpu
