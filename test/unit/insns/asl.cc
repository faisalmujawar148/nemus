#include "cpu.h"
#include "insn.h"
#include "testutils.h"
#include <gtest/gtest.h>

static nemus::cpu::RegisterBlock reg_block;
static nemus::test::InsnMemIFMock mem_mock;

TEST(NES_INSN_ASL, Accumulator) {
  reg_block.m_accm = 1;
  NES_INSN(asl)(0xA, reg_block, mem_mock);
  EXPECT_EQ(reg_block.m_accm, 0x2);
  EXPECT_EQ(reg_block.get_z_flag(), 0);
  EXPECT_EQ(reg_block.get_n_flag(), 0);
  EXPECT_EQ(reg_block.get_c_flag(), 0);
};

TEST(NES_INSN_ASL, ZeroPage) {
  // PC: 0 ASL PC: 1 0x44
  mem_mock.write_rom(1, 1, 0x44);
  mem_mock.write(0x44, 1, 0x2);
  NES_INSN(asl)(0x6, reg_block, mem_mock);
  EXPECT_EQ(mem_mock.read(0x44, 1).second, 0x4);
  EXPECT_EQ(reg_block.get_z_flag(), 0);
  EXPECT_EQ(reg_block.get_n_flag(), 0);
  EXPECT_EQ(reg_block.get_c_flag(), 0);
}

TEST(NES_INSN_ASL, ZeroPageX) {
  // PC: 0 ASL PC: 1 0x44 X = 0x2
  reg_block.m_index_x = 0x2;
  mem_mock.write_rom(1, 1, 0x44);
  mem_mock.write(0x44 + reg_block.m_index_x, 1, 0x2);
  NES_INSN(asl)(0x16, reg_block, mem_mock);
  EXPECT_EQ(mem_mock.read(0x44 + reg_block.m_index_x, 1).second, 0x4);
  EXPECT_EQ(reg_block.get_z_flag(), 0);
  EXPECT_EQ(reg_block.get_n_flag(), 0);
  EXPECT_EQ(reg_block.get_c_flag(), 0);
}

TEST(NES_INSN_ASL, Absolute) {
  // PC: 0 = ASL, PC: 1 = 0xFF, PC: 2 = 0x00
  mem_mock.write_rom(1, 1, 0xFF);
  mem_mock.write_rom(2, 1, 0x00);
  mem_mock.write(0xFF, 1, 0x2);
  NES_INSN(asl)(0x0E, reg_block, mem_mock);
  EXPECT_EQ(mem_mock.read(0xFF, 1).second, 0x4);
  EXPECT_EQ(reg_block.get_z_flag(), 0);
  EXPECT_EQ(reg_block.get_n_flag(), 0);
  EXPECT_EQ(reg_block.get_c_flag(), 0);
}

TEST(NES_INSN_ASL, AbsoluteX) {
  // PC: 0 = ASL, PC: 1 = 0xFF, PC: 2 = 0x00 X = 0x2
  reg_block.m_index_x = 0x2;
  mem_mock.write_rom(1, 1, 0xFF);
  mem_mock.write_rom(2, 1, 0x00);
  mem_mock.write(0xFF + reg_block.m_index_x, 1, 0x2);
  NES_INSN(asl)(0x1E, reg_block, mem_mock);
  EXPECT_EQ(mem_mock.read(0xFF + reg_block.m_index_x, 1).second, 0x4);
  EXPECT_EQ(reg_block.get_z_flag(), 0);
  EXPECT_EQ(reg_block.get_n_flag(), 0);
  EXPECT_EQ(reg_block.get_c_flag(), 0);
}

TEST(NES_INSN_ASL, Status_Zero) {
  // PC: 0 ASL PC: 1 0x44
  mem_mock.write_rom(1, 1, 0x44);
  mem_mock.write(0x44, 1, 0);
  NES_INSN(asl)(0x6, reg_block, mem_mock);
  EXPECT_EQ(mem_mock.read(0x44, 1).second, 0);
  EXPECT_EQ(reg_block.get_z_flag(), 1);
  EXPECT_EQ(reg_block.get_n_flag(), 0);
  EXPECT_EQ(reg_block.get_c_flag(), 0);
}

TEST(NES_INSN_ASL, Status_Carry_And_Negative) {
  // PC: 0 ASL PC: 1 0x44
  mem_mock.write_rom(1, 1, 0x44);
  mem_mock.write(0x44, 1, 0xC0);
  NES_INSN(asl)(0x6, reg_block, mem_mock);
  EXPECT_EQ(mem_mock.read(0x44, 1).second, 0x80);
  EXPECT_EQ(reg_block.get_z_flag(), 0);
  EXPECT_EQ(reg_block.get_n_flag(), 1);
  EXPECT_EQ(reg_block.get_c_flag(), 1);
}

TEST(NES_INSN_ASL, Status_Zero_And_Negative_And_Carry) {
  // PC: 0 ASL PC: 1 0x44
  mem_mock.write_rom(1, 1, 0x44);
  mem_mock.write(0x44, 1, 0x80);
  NES_INSN(asl)(0x6, reg_block, mem_mock);
  EXPECT_EQ(mem_mock.read(0x44, 1).second, 0x0);
  EXPECT_EQ(reg_block.get_z_flag(), 1);
  EXPECT_EQ(reg_block.get_n_flag(), 1);
  EXPECT_EQ(reg_block.get_c_flag(), 1);
}
