#include <array>
#include <cstring>
#include <iostream>
#include <utility>

#include "insn.h"
#include "typedefs.h"

namespace nemus::test {

struct InsnMemIFMock {
  std::array<unsigned char, 2048> memory;

  std::pair<bool, Data16> read(Addr16 addr, Size8 size) {
    if (addr >= 2048 || size > 2 || size == 0) {
      return {false, 0};
    }
    if (addr + size > 2048) {
      return {false, 0};
    }
    Data16 value = 0;
    std::memcpy(&value, memory.data() + addr, size);
    return {true, value};
  };

  bool write(Addr16 addr, Size8 size, Data16 data) {
    if (addr >= 2048 || size > 2 || size == 0) {
      return false;
    }
    if (addr + size > 2048) {
      return false;
    }
    std::memcpy(memory.data() + addr, &data, size);
    return true;
  };
  std::pair<bool, Data16> read_rom(Addr16 addr, Size8 size) {
    return read(addr, size);
  };
  bool write_rom(Addr16 addr, Size8 size, Data16 data) {
    return write(addr, size, data);
  };

  std::pair<bool, Data16>
  read_insn_operands(insn::AddressingModesKind addr_mode, Addr16 pc = 0) {
    switch (addr_mode) {
    case nemus::insn::AddressingModesKind::Implicit: {
      return {true, 0};
      break;
    }
    case nemus::insn::AddressingModesKind::Accumulator: {
      return {true, 0};
      break;
    }
    case nemus::insn::AddressingModesKind::Immediate: {
      return read(pc + 1, 1);
      break;
    }
    case nemus::insn::AddressingModesKind::ZeroPage: {
      return read(pc + 1, 1);
      break;
    }
    case nemus::insn::AddressingModesKind::ZeroPageX: {
      return read(pc + 1, 1);
      break;
    }
    case nemus::insn::AddressingModesKind::ZeroPageY: {
      return read(pc + 1, 1);
      break;
    }
    case nemus::insn::AddressingModesKind::Relative: {
      return read(pc + 1, 1);
      break;
    }
    case nemus::insn::AddressingModesKind::Absolute: {
      return read(pc + 1, 2);
      break;
    }
    case nemus::insn::AddressingModesKind::AbsoluteX: {
      return read(pc + 1, 2);
      break;
    }
    case nemus::insn::AddressingModesKind::AbsoluteY: {
      return read(pc + 1, 2);
      break;
    }
    case nemus::insn::AddressingModesKind::Indirect: {
      return read(pc + 1, 2);
      break;
    }
    case nemus::insn::AddressingModesKind::IndexedIndirect: {
      return read(pc + 1, 1);
      break;
    }
    case nemus::insn::AddressingModesKind::IndirectIndexed: {
      return read(pc + 1, 1);
      break;
    }
    }
    return {false, 0};
  };
};

} // namespace nemus::test
