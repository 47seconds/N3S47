#pragma once

#include <cstdint>

class cpu {
private:

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

  // addressing modes
  // 1. Indexed
  void ZPX(); // Zero page indexed: d, x
  void ZPY(); // Zero page indexed: d, y
  void ABX(); // Absolute indexed: a, x
  void ABY(); // Absolute indexed: a, y
  void IIX(); // Indexed indirect: (d, x)
  void IIY(); // Indirect indexed: (d), y
  //2. Others
  void IMP(); // Implicit
  void ACC(); // Accumulator
  void IMM(); // Immediate
  void ZP_(); // Zero Page
  void ABS(); // Absolute
  void REL(); // Relative
  void IND(); // Indirect
};
