#pragma once

#include <cstdint>

class cpu {
private:

public:
  // registers
  uint8_t   Ac;
  uint8_t   X;
  uint8_t   Y;
  uint8_t   P;
  uint8_t   SP;
  uint16_t  PC;

  // P register flags
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
  void AX();  // Absolute indexed: a, x
  void AY();  // Absolute indexed: a, y
  void IIX(); // Indexed indirect: (d, x)
  void IIY(); // Indirect indexed: (d), y

};
