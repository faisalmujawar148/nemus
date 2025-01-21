#pragma once

#include "cpu.h"
#include "insn.h"
#include "typedefs.h"

namespace nemus::insn_helpers {

struct InsnOprResp {
  Addr16 operand = 0;
  Data16 data = 0;
};

template <typename ObjType>
  requires insn::InsnMemIF<ObjType>
InsnOprResp static inline base_helper(insn::AddressingModesKind addr_mode,
                                      ObjType &mem, Data8 incr = 0,
                                      Size8 sz = 1) {
  auto operand = mem.read_insn_operands(addr_mode);
  auto data = mem.read(operand + incr, sz);
  return {operand, data};
};

template <typename ObjType>
  requires insn::InsnMemIF<ObjType>
InsnOprResp static inline get_immediate_operand(cpu::RegisterBlock &reg_block,
                                                ObjType &mem) {
  auto resp = mem.read_insn_operands(insn::AddressingModesKind::Immediate);
  return {resp, 0};
};

template <typename ObjType>
  requires insn::InsnMemIF<ObjType>
InsnOprResp static inline get_zero_page_operand(cpu::RegisterBlock &reg_block,
                                                ObjType &mem) {
  return base_helper(insn::AddressingModesKind::ZeroPage, mem);
};

template <typename ObjType>
  requires insn::InsnMemIF<ObjType>
InsnOprResp static inline get_zero_page_x_operand(cpu::RegisterBlock &reg_block,
                                                  ObjType &mem) {
  return base_helper(insn::AddressingModesKind::ZeroPageX, mem,
                     reg_block.m_index_x);
};

template <typename ObjType>
  requires insn::InsnMemIF<ObjType>
InsnOprResp static inline get_zero_page_y_operand(cpu::RegisterBlock &reg_block,
                                                  ObjType &mem) {
  return base_helper(insn::AddressingModesKind::ZeroPageY, mem,
                     reg_block.m_index_y);
};

template <typename ObjType>
  requires insn::InsnMemIF<ObjType>
InsnOprResp static inline get_absolute_operand(cpu::RegisterBlock &reg_block,
                                               ObjType &mem) {
  return base_helper(insn::AddressingModesKind::Absolute, mem);
};

template <typename ObjType>
  requires insn::InsnMemIF<ObjType>
InsnOprResp static inline get_absolute_x_operand(cpu::RegisterBlock &reg_block,
                                                 ObjType &mem) {
  return base_helper(insn::AddressingModesKind::AbsoluteX, mem,
                     reg_block.m_index_x);
};

template <typename ObjType>
  requires insn::InsnMemIF<ObjType>
InsnOprResp static inline get_absolute_y_operand(cpu::RegisterBlock &reg_block,
                                                 ObjType &mem) {
  return base_helper(insn::AddressingModesKind::AbsoluteY, mem,
                     reg_block.m_index_y);
};

template <typename ObjType>
  requires insn::InsnMemIF<ObjType>
InsnOprResp static inline get_indirect_operand(cpu::RegisterBlock &reg_block,
                                               ObjType &mem) {
  InsnOprResp ret_val =
      base_helper(insn::AddressingModesKind::Indirect, mem, 0, 2);
  Data16 data = mem.read(ret_val.data, 1);
  ret_val.operand = ret_val.data;
  ret_val.data = data;
  return ret_val;
};

template <typename ObjType>
  requires insn::InsnMemIF<ObjType>
InsnOprResp static inline get_indirect_x_operand(cpu::RegisterBlock &reg_block,
                                                 ObjType &mem) {
  InsnOprResp ret_val = base_helper(insn::AddressingModesKind::IndexedIndirect,
                                    mem, reg_block, 2);
  Data16 data = mem.read(ret_val.data, 1);
  ret_val.operand = ret_val.data;
  ret_val.data = data;
  return ret_val;
};

template <typename ObjType>
  requires insn::InsnMemIF<ObjType>
InsnOprResp static inline get_indirect_y_operand(cpu::RegisterBlock &reg_block,
                                                 ObjType &mem) {
  InsnOprResp ret_val =
      base_helper(insn::AddressingModesKind::IndexedIndirect, mem, 0, 2);
  Data16 data = mem.read(ret_val.data + reg_block.m_index_y, 1);
  ret_val.operand = ret_val.data;
  ret_val.data = data;
  return ret_val;
};

} // namespace nemus::insn_helpers
