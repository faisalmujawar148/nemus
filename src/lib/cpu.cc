#include "cpu.h"
#include "insn.h"
#include "typedefs.h"

namespace nemus::cpu {

void RegisterBlock::increment_pc(insn::AddressingModesKind addr_mode) {
  switch (addr_mode) {
  case nemus::insn::AddressingModesKind::Implicit: {
    m_pc += 1;
    break;
  }
  case nemus::insn::AddressingModesKind::Accumulator: {
    m_pc += 1;
    break;
  }
  case nemus::insn::AddressingModesKind::Immediate: {
    m_pc += 2;
    break;
  }
  case nemus::insn::AddressingModesKind::ZeroPage: {
    m_pc += 2;
    break;
  }
  case nemus::insn::AddressingModesKind::ZeroPageX: {
    m_pc += 2;
    break;
  }
  case nemus::insn::AddressingModesKind::ZeroPageY: {
    m_pc += 2;
    break;
  }
  case nemus::insn::AddressingModesKind::Relative: {
    m_pc += 2;
    break;
  }
  case nemus::insn::AddressingModesKind::Absolute: {
    m_pc += 3;
    break;
  }
  case nemus::insn::AddressingModesKind::AbsoluteX: {
    m_pc += 3;
    break;
  }
  case nemus::insn::AddressingModesKind::AbsoluteY: {
    m_pc += 3;
    break;
  }
  case nemus::insn::AddressingModesKind::Indirect: {
    m_pc += 3;
    break;
  }
  case nemus::insn::AddressingModesKind::IndexedIndirect: {
    m_pc += 2;
    break;
  }
  case nemus::insn::AddressingModesKind::IndirectIndexed: {
    m_pc += 2;
    break;
  }
  }
}

std::pair<bool, Data16>
NESCpu::read_insn_operands(insn::AddressingModesKind addr_mode, Addr16 pc) {

  return {false, 0};
}

} // namespace nemus::cpu
