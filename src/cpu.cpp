#include "../include/cpu.hpp"
#include <cstdint>
#include <vector>

CPU::CPU() {
  // https://www.masswerk.at/6502/6502_instruction_set.html
  // https://www.nesdev.org/obelisk-6502-guide/reference.html
  std::vector<Instruction> instruction_set = {
        { "BRK", &CPU::BRK, &CPU::IMM, 7 },{ "ORA", &CPU::ORA, &CPU::IIX, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 8 },{ "XXX", &CPU::NOP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::ZP_, 3 },{ "ASL", &CPU::ASL, &CPU::ZP_, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 5 },{ "PHP", &CPU::PHP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::IMM, 2 },{ "ASL", &CPU::ASL, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "XXX", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABS, 4 },{ "ASL", &CPU::ASL, &CPU::ABS, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },
		{ "BPL", &CPU::BPL, &CPU::REL, 2 },{ "ORA", &CPU::ORA, &CPU::IIY, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 8 },{ "XXX", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ZPX, 4 },{ "ASL", &CPU::ASL, &CPU::ZPX, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },{ "CLC", &CPU::CLC, &CPU::IMP, 2 },{ "ORA", &CPU::ORA, &CPU::ABY, 4 },{ "XXX", &CPU::NOP, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 7 },{ "XXX", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABX, 4 },{ "ASL", &CPU::ASL, &CPU::ABX, 7 },{ "XXX", &CPU::XXX, &CPU::IMP, 7 },
		{ "JSR", &CPU::JSR, &CPU::ABS, 6 },{ "AND", &CPU::AND, &CPU::IIX, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 8 },{ "BIT", &CPU::BIT, &CPU::ZP_, 3 },{ "AND", &CPU::AND, &CPU::ZP_, 3 },{ "ROL", &CPU::ROL, &CPU::ZP_, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 5 },{ "PLP", &CPU::PLP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::IMM, 2 },{ "ROL", &CPU::ROL, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "BIT", &CPU::BIT, &CPU::ABS, 4 },{ "AND", &CPU::AND, &CPU::ABS, 4 },{ "ROL", &CPU::ROL, &CPU::ABS, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },
		{ "BMI", &CPU::BMI, &CPU::REL, 2 },{ "AND", &CPU::AND, &CPU::IIY, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 8 },{ "XXX", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ZPX, 4 },{ "ROL", &CPU::ROL, &CPU::ZPX, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },{ "SEC", &CPU::SEC, &CPU::IMP, 2 },{ "AND", &CPU::AND, &CPU::ABY, 4 },{ "XXX", &CPU::NOP, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 7 },{ "XXX", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ABX, 4 },{ "ROL", &CPU::ROL, &CPU::ABX, 7 },{ "XXX", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTI", &CPU::RTI, &CPU::IMP, 6 },{ "EOR", &CPU::EOR, &CPU::IIX, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 8 },{ "XXX", &CPU::NOP, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::ZP_, 3 },{ "LSR", &CPU::LSR, &CPU::ZP_, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 5 },{ "PHA", &CPU::PHA, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::IMM, 2 },{ "LSR", &CPU::LSR, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "JMP", &CPU::JMP, &CPU::ABS, 3 },{ "EOR", &CPU::EOR, &CPU::ABS, 4 },{ "LSR", &CPU::LSR, &CPU::ABS, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVC", &CPU::BVC, &CPU::REL, 2 },{ "EOR", &CPU::EOR, &CPU::IIY, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 8 },{ "XXX", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ZPX, 4 },{ "LSR", &CPU::LSR, &CPU::ZPX, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },{ "CLI", &CPU::CLI, &CPU::IMP, 2 },{ "EOR", &CPU::EOR, &CPU::ABY, 4 },{ "XXX", &CPU::NOP, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 7 },{ "XXX", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ABX, 4 },{ "LSR", &CPU::LSR, &CPU::ABX, 7 },{ "XXX", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTS", &CPU::RTS, &CPU::IMP, 6 },{ "ADC", &CPU::ADC, &CPU::IIX, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 8 },{ "XXX", &CPU::NOP, &CPU::IMP, 3 },{ "ADC", &CPU::ADC, &CPU::ZP_, 3 },{ "ROR", &CPU::ROR, &CPU::ZP_, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 5 },{ "PLA", &CPU::PLA, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::IMM, 2 },{ "ROR", &CPU::ROR, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "JMP", &CPU::JMP, &CPU::IND, 5 },{ "ADC", &CPU::ADC, &CPU::ABS, 4 },{ "ROR", &CPU::ROR, &CPU::ABS, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVS", &CPU::BVS, &CPU::REL, 2 },{ "ADC", &CPU::ADC, &CPU::IIY, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 8 },{ "XXX", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ZPX, 4 },{ "ROR", &CPU::ROR, &CPU::ZPX, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },{ "SEI", &CPU::SEI, &CPU::IMP, 2 },{ "ADC", &CPU::ADC, &CPU::ABY, 4 },{ "XXX", &CPU::NOP, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 7 },{ "XXX", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ABX, 4 },{ "ROR", &CPU::ROR, &CPU::ABX, 7 },{ "XXX", &CPU::XXX, &CPU::IMP, 7 },
		{ "XXX", &CPU::NOP, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::IIX, 6 },{ "XXX", &CPU::NOP, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },{ "STY", &CPU::STY, &CPU::ZP_, 3 },{ "STA", &CPU::STA, &CPU::ZP_, 3 },{ "STX", &CPU::STX, &CPU::ZP_, 3 },{ "XXX", &CPU::XXX, &CPU::IMP, 3 },{ "DEY", &CPU::DEY, &CPU::IMP, 2 },{ "XXX", &CPU::NOP, &CPU::IMP, 2 },{ "TXA", &CPU::TXA, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "STY", &CPU::STY, &CPU::ABS, 4 },{ "STA", &CPU::STA, &CPU::ABS, 4 },{ "STX", &CPU::STX, &CPU::ABS, 4 },{ "XXX", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCC", &CPU::BCC, &CPU::REL, 2 },{ "STA", &CPU::STA, &CPU::IIY, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },{ "STY", &CPU::STY, &CPU::ZPX, 4 },{ "STA", &CPU::STA, &CPU::ZPX, 4 },{ "STX", &CPU::STX, &CPU::ZPY, 4 },{ "XXX", &CPU::XXX, &CPU::IMP, 4 },{ "TYA", &CPU::TYA, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::ABY, 5 },{ "TXS", &CPU::TXS, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 5 },{ "XXX", &CPU::NOP, &CPU::IMP, 5 },{ "STA", &CPU::STA, &CPU::ABX, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 5 },
		{ "LDY", &CPU::LDY, &CPU::IMM, 2 },{ "LDA", &CPU::LDA, &CPU::IIX, 6 },{ "LDX", &CPU::LDX, &CPU::IMM, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },{ "LDY", &CPU::LDY, &CPU::ZP_, 3 },{ "LDA", &CPU::LDA, &CPU::ZP_, 3 },{ "LDX", &CPU::LDX, &CPU::ZP_, 3 },{ "XXX", &CPU::XXX, &CPU::IMP, 3 },{ "TAY", &CPU::TAY, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::IMM, 2 },{ "TAX", &CPU::TAX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "LDY", &CPU::LDY, &CPU::ABS, 4 },{ "LDA", &CPU::LDA, &CPU::ABS, 4 },{ "LDX", &CPU::LDX, &CPU::ABS, 4 },{ "XXX", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCS", &CPU::BCS, &CPU::REL, 2 },{ "LDA", &CPU::LDA, &CPU::IIY, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 5 },{ "LDY", &CPU::LDY, &CPU::ZPX, 4 },{ "LDA", &CPU::LDA, &CPU::ZPX, 4 },{ "LDX", &CPU::LDX, &CPU::ZPY, 4 },{ "XXX", &CPU::XXX, &CPU::IMP, 4 },{ "CLV", &CPU::CLV, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::ABY, 4 },{ "TSX", &CPU::TSX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 4 },{ "LDY", &CPU::LDY, &CPU::ABX, 4 },{ "LDA", &CPU::LDA, &CPU::ABX, 4 },{ "LDX", &CPU::LDX, &CPU::ABY, 4 },{ "XXX", &CPU::XXX, &CPU::IMP, 4 },
		{ "CPY", &CPU::CPY, &CPU::IMM, 2 },{ "CMP", &CPU::CMP, &CPU::IIX, 6 },{ "XXX", &CPU::NOP, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 8 },{ "CPY", &CPU::CPY, &CPU::ZP_, 3 },{ "CMP", &CPU::CMP, &CPU::ZP_, 3 },{ "DEC", &CPU::DEC, &CPU::ZP_, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 5 },{ "INY", &CPU::INY, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::IMM, 2 },{ "DEX", &CPU::DEX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "CPY", &CPU::CPY, &CPU::ABS, 4 },{ "CMP", &CPU::CMP, &CPU::ABS, 4 },{ "DEC", &CPU::DEC, &CPU::ABS, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },
		{ "BNE", &CPU::BNE, &CPU::REL, 2 },{ "CMP", &CPU::CMP, &CPU::IIY, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 8 },{ "XXX", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ZPX, 4 },{ "DEC", &CPU::DEC, &CPU::ZPX, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },{ "CLD", &CPU::CLD, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 7 },{ "XXX", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ABX, 4 },{ "DEC", &CPU::DEC, &CPU::ABX, 7 },{ "XXX", &CPU::XXX, &CPU::IMP, 7 },
		{ "CPX", &CPU::CPX, &CPU::IMM, 2 },{ "SBC", &CPU::SBC, &CPU::IIX, 6 },{ "XXX", &CPU::NOP, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 8 },{ "CPX", &CPU::CPX, &CPU::ZP_, 3 },{ "SBC", &CPU::SBC, &CPU::ZP_, 3 },{ "INC", &CPU::INC, &CPU::ZP_, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 5 },{ "INX", &CPU::INX, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::IMM, 2 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "XXX", &CPU::SBC, &CPU::IMP, 2 },{ "CPX", &CPU::CPX, &CPU::ABS, 4 },{ "SBC", &CPU::SBC, &CPU::ABS, 4 },{ "INC", &CPU::INC, &CPU::ABS, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },
		{ "BEQ", &CPU::BEQ, &CPU::REL, 2 },{ "SBC", &CPU::SBC, &CPU::IIY, 5 },{ "XXX", &CPU::XXX, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 8 },{ "XXX", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ZPX, 4 },{ "INC", &CPU::INC, &CPU::ZPX, 6 },{ "XXX", &CPU::XXX, &CPU::IMP, 6 },{ "SED", &CPU::SED, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "XXX", &CPU::XXX, &CPU::IMP, 7 },{ "XXX", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ABX, 4 },{ "INC", &CPU::INC, &CPU::ABX, 7 },{ "XXX", &CPU::XXX, &CPU::IMP, 7 },
  };
}

void CPU::setFlag(P_FLAGS f, bool cond) {
  if (cond) P |= f;
  else P &= ~f;
}

uint8_t CPU::getFlag(P_FLAGS f) {
  return (P & f) ? 1 : 0;
}

// Huge Thanks
// https://www.nesdev.org/obelisk-6502-guide/reference.html

// This instruction adds the contents of a memory location to the accumulator together with the carry bit. If overflow occurs the carry bit is set, this enables multiple byte addition to be performed.
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
  temp = (uint16_t)A + (uint16_t)fetched_val + (P & C ? 1 : 0);

  // if res > uint8_t size, set carry bit, else set it to 0
  setFlag(C, temp > 0xFF); // Set carry bit in P (since C is already 1 in struct)

  temp &= 0xFF; // can use (uint8_t)sum, but conversion -> compiler decides, while rn we mark explicitly

  // set zero bit, if applicable
  setFlag(Z, !temp);

  // set negative if last bit is set (Xxxxxxxx & 10000000 (0x80))
  setFlag(N, temp & 0x80);

  // set overflow if A and operand has same sign, but res has different -> overflow
  setFlag(V, (((~(A ^ fetched_val)) & (A ^ temp)) & 0x80));

  A = temp;

  return 1; // need 1 extra if page crossed (https://www.nesdev.org/obelisk-6502-guide/reference.html)
}

// A logical AND is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
uint8_t CPU::AND() {
  temp = A & fetched_val;

  setFlag(Z, !temp);

  setFlag(N, temp & 0x80);

  A = temp;

  return 1;
}

// This operation shifts all the bits of the accumulator or memory contents one bit left. Bit 0 is set to 0 and bit 7 is placed in the carry flag. The effect of this operation is to multiply the memory contents by 2 (ignoring 2's complement considerations), setting the carry if the result will not fit in 8 bits.
uint8_t CPU::ASL() {
  temp = (uint16_t)(fetched_val << 1);

  setFlag(C, (temp & 0xFF00) > 0);

  setFlag(Z, !(temp & 0x00FF));

  setFlag(N, (temp & 0x0080));

  // if Implicit mpde, store in accumulator, else in memory
  if (instruction_set[opcode].addrmode == &CPU::IMP) A = temp & 0x00FF;
  else write(abs_addr, (uint8_t)temp & 0x00FF);

  return 0;
}

// This operation shifts all the bits of the accumulator or memory contents one bit left. Bit 0 is set to 0 and bit 7 is placed in the carry flag. The effect of this operation is to multiply the memory contents by 2 (ignoring 2's complement considerations), setting the carry if the result will not fit in 8 bits.
uint8_t CPU::BCC() {
  if (!getFlag(C)) {
    global_cycle++;

    abs_addr = PC + rel_addr;

    // Memory is divided into pages of 256 bytes
    // A page cross happens when the high byte of the address changes
    // old high bits of abs_addr (PC) and new abs_addr have changed -> page changed
    if ((PC & 0xFF00) ^ (abs_addr & 0xFF00)) global_cycle++;

    PC = abs_addr;
  }

  return 0;
}

// If the carry flag is clear then add the relative displacement to the program counter to cause a branch to a new location.
uint8_t CPU::BCS() {
  if (getFlag(C)) {
    global_cycle++;

    abs_addr = PC + rel_addr;

    if ((PC & 0xFF00) ^ (abs_addr & 0xFF00)) global_cycle++;

    PC = abs_addr;
  }

  return 0;
}

// If the zero flag is set then add the relative displacement to the program counter to cause a branch to a new location.
uint8_t CPU::BEQ() {
  if (getFlag(Z)) {
    global_cycle++;

    abs_addr = PC + rel_addr;

    if ((PC & 0xFF00) ^ (abs_addr & 0xFF00)) global_cycle++;

    PC = abs_addr;
  }

   return 0;
}

// This instructions is used to test if one or more bits are set in a target memory location. The mask pattern in A is ANDed with the value in memory to set or clear the zero flag, but the result is not kept. Bits 7 and 6 of the value from memory are copied into the N and V flags.
uint8_t CPU::BIT() {
  temp = A & fetched_val;

  setFlag(Z, !(temp & 0x00FF));

  setFlag(V, fetched_val & 0x40);

  setFlag(N, fetched_val & 0x80);

  return 0;
}

// If the negative flag is set then add the relative displacement to the program counter to cause a branch to a new location.
uint8_t CPU::BMI() {
  if (getFlag(N)) {
    global_cycle++;

    abs_addr = PC + rel_addr;

    if ((PC & 0xFF00) ^ (abs_addr & 0xFF00)) global_cycle++;

    PC = abs_addr;
  }

  return 0;
}

// If the zero flag is clear then add the relative displacement to the program counter to cause a branch to a new location.
uint8_t CPU::BNE() {
  if (!getFlag(Z)) {
    global_cycle++;

    abs_addr = PC + rel_addr;

    if ((PC & 0xFF00) ^ (abs_addr & 0xFF00)) global_cycle++;

    PC = abs_addr;
  }

  return 0;
}

// If the negative flag is clear then add the relative displacement to the program counter to cause a branch to a new location.
uint8_t CPU::BPL() {
  if (!getFlag(N)) {
    global_cycle++;

    abs_addr = PC + rel_addr;

    if ((PC & 0xFF00) ^ (abs_addr & 0xFF00)) global_cycle++;

    PC = abs_addr;
  }

  return 0;
}

// The BRK instruction forces the generation of an interrupt request. The program counter and processor status are pushed on the stack then the IRQ interrupt vector at $FFFE/F is loaded into the PC and the break flag in the status set to one.
// Stack goal:
// [ PC high ]
// [ PC low  ]
// [ status  ]

uint8_t CPU::BRK() {
  // BRK is a 1-byte instruction but 6502 treats it like 2-byte instruction internally (hence, skip 1 extra byte)
  PC++;

  // Push PC (high byte first)
  temp = 0x0100 + SP;
  write(temp, (PC >> 8) & 0x00FF);
  SP--;

  // Push PC (low byte after)
  temp = 0x0100 + SP;
  write(temp, PC & 0x00FF);
  SP--;


  setFlag(B, true); // as it is a BRK interrupt in progress
  setFlag(O, true); // 5th (Unused bit) should always be set

  // push status register
  temp = 0x0100 + SP;
  write(temp, P);
  SP--;

  setFlag(B, false);  // stack stores B = 1 copy now, but real CPU shouldn't have B = 1

  setFlag(I, true);

  // Laod IRQ interrupt in the PC from the 0xFFFE and 0xFFFF (little endian)
  temp  = 0x00FF & read(0xFFFE);  // little endian (low byte first) (doing masking to make sure previous value of temp don't interfare) EDIT: fuck, assignment overwrites prev value of temp lmao, so kinda useless masking, but whatever~
  temp |= (read(0xFFFF) << 8);    // high byte read and shift 8 bits and append low byte here
  PC = temp;

  return 0;
}
