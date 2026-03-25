#pragma once

#include <cstdint>

class cpu {
private:

  // Instruction holding name, function pointer, address mode (function) pointer it operates on, and number of cycles this instruction needs to complete
  struct Instruction {
    const char* name;
    uint8_t     (cpu::*operate)(void);
    uint8_t     (cpu::*addrmode)(void);
    uint8_t     cycles;
  };

public:
  // registers (8-bit, except PC)
  uint8_t   A   = 0x00;
  uint8_t   X   = 0x00;
  uint8_t   Y   = 0x00;
  uint8_t   P   = 0x24;
  uint8_t   SP  = 0xFD;
  uint16_t  PC  = 0xFFFC;

  // P register flags
  /* 
    bit   masking:
    Flag	Bit	Value
    C	    0	  00000001
    Z	    1	  00000010
    ...
  */
  enum P_FLAGS {
    C = (1 << 0), // carry
    Z = (1 << 1), // zero
    I = (1 << 2), // interrupt disable
    D = (1 << 3), // decimal
    B = (1 << 4), // B is 0 when pushed by interrupts (NMI and IRQ) and 1 when pushed by instructions (BRK and PHP)
    O = (1 << 5), // always pushed as one (no use, null)
    V = (1 << 6), // overflow
    N = (1 << 7), // negative
  };

private:

public:
  cpu();
  ~cpu();

  // Every function/instruction should return in uint8_t (1 byte), returning if they need extra cycle conditionally
  // addressing modes
  // 1. Indexed
  uint8_t ZPX(); // Zero page indexed: d, x
  uint8_t ZPY(); // Zero page indexed: d, y
  uint8_t ABX(); // Absolute indexed: a, x
  uint8_t ABY(); // Absolute indexed: a, y
  uint8_t IIX(); // Indexed indirect: (d, x)
  uint8_t IIY(); // Indirect indexed: (d), y
  //2. Others
  uint8_t IMP(); // Implicit
  uint8_t ACC(); // Accumulator
  uint8_t IMM(); // Immediate
  uint8_t ZP_(); // Zero Page
  uint8_t ABS(); // Absolute
  uint8_t REL(); // Relative
  uint8_t IND(); // Indirect

  // Instruction Codes Set
  // https://www.nesdev.org/obelisk-6502-guide/reference.html
  uint8_t ADC(); // Add with Carry
  uint8_t AND();
  uint8_t ASL();
  uint8_t BCC();
  uint8_t BCS();
  uint8_t BEQ();
  uint8_t BIT();
  uint8_t BMI();
  uint8_t BNE();
  uint8_t BPL();
  uint8_t BRK();
  uint8_t BVC();
  uint8_t BVS();
  uint8_t CLC();
  uint8_t CLD();
  uint8_t CLI();
  uint8_t CLV();
  uint8_t CMP();
  uint8_t CPX();
  uint8_t CPY();
  uint8_t DEC();
  uint8_t DEX();
  uint8_t DEY();
  uint8_t EOR();
  uint8_t INC();
  uint8_t INX();
  uint8_t INY();
  uint8_t JMP();
  uint8_t JSR();
  uint8_t LDA();
  uint8_t LDX();
  uint8_t LDY();
  uint8_t LSR();
  uint8_t NOP();
  uint8_t ORA();
  uint8_t PHA();
  uint8_t PHP();
  uint8_t PLA();
  uint8_t PLP();
  uint8_t ROL();
  uint8_t ROR();
  uint8_t RTI();
  uint8_t RTS();
  uint8_t SBC();
  uint8_t SEC();
  uint8_t SED();
  uint8_t SEI();
  uint8_t STA();
  uint8_t STX();
  uint8_t STY();
  uint8_t TAX();
  uint8_t TAY();
  uint8_t TSX();
  uint8_t TXA();
  uint8_t TXS();
  uint8_t TYA();
};
