#include "../include/cpu.hpp"
#include <cstdint>

uint8_t CPU::ADC() {
  /*
    This instruction adds the contents of a memory location to the accumulator together with the carry bit. If overflow occurs the carry bit is set, this enables multiple byte addition to be performed.

    Processor Status after use:

    C 	Carry Flag 	        Set if overflow in bit 7
    Z 	Zero Flag 	        Set if A = 0
    I 	Interrupt Disable 	Not affected
    D 	Decimal Mode Flag 	Not affected
    B 	Break Command 	    Not affected
    V 	Overflow Flag 	    Set if sign bit is incorrect
    N 	Negative Flag 	    Set if bit 7 set
  */

  // Sum = A + operand + carry (read Carry bit from P)
  uint16_t sum = (uint16_t)A + (uint16_t)fetched_val + (P & C ? 1 : 0);

  // if res > uint8_t size, set carry bit, else set it to 0
  if (sum > 0xFF) P |= C; // Set carry bit in P (since C is already 1 in struct)
  else P &= ~C;

  uint8_t res = sum & 0xFF; // can use (uint8_t)sum, but conversion -> compiler decides, while rn we mark explicitly

  // set zero bit, if applicable
  if (!res) P |= Z;
  else P &= ~Z;

  // set negative if last bit is set (Xxxxxxxx & 10000000 (0x80))
  if (res & 0x80) P |= N;
  else P &= ~N;

  // set overflow if A and operand has same sign, but res has different -> overflow
  if (((~(A ^ fetched_val)) & (A ^ res)) & 0x80) P |= V;
  else P &= ~V;

  A = res;

  return 1; // need 1 extra if page crossed (https://www.nesdev.org/obelisk-6502-guide/reference.html)
}

uint8_t CPU::AND() {
  uint8_t res = A & fetched_val;

  if (!res) P |= Z;
  else P &= ~Z;

  if (res & 0x80) P |= N;
  else P &= ~N;

  A = res;

  return 1;
}
