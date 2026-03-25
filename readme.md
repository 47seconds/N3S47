The NES Emulation in C++ by 47seconds

# CPU
NES CPU is implemented on 6502 based 8-bit processor, with 16-bit addressing (0x0000 → 0xFFFF, each address store 1 byte (8-bit) data, 64 KB memory) and is little endian

## Instruction codes and opcodes
The 6502 has 56 of instruction including instructions for operations such as addition, subtraction, AND, OR, ROR, etc.
The 6502 processor has a total of 256 possible opcodes, but only 151 were used originally, arranged into 56 instructions which the NES used.

Instruction = meaning
Opcode = binary representation

Instruction	    LDA #$10	Load value 0x10 into register A
Opcode	        0xA9	    Binary code CPU actually reads
Machine code	A9 10	    Opcode + operand

Also, multiple addressing modes:
There are multiple opcodes for LDA depending on how the value is fetched:

Addr. Mode	Opcode 	Meaning
Immediate	0xA9	LDA #value
Zero Page	0xA5	LDA $00
Absolute	0xAD	LDA $1234
Indexed (X)	0xBD	LDA $1234,X

## Registers
The 6502 processor has six 8-bit registers, with the exception of the Program Counter, which is 16-bit. The registers are as follows:
1. Accumulator(A) - The accumulator can read and write to memory. It is used to store arithmetic and logic results such as addition and subtraction.
2. X Index(X) - The x index is can read and write to memory. It is used primarily as a counter in loops, or for addressing memory, but can also temporarily store data like the accumulator.
3. Y Index(Y) - Much like the x index, however they are not completely interchangeable. Some operations are only available for each register.
4. Flag(P) - The register holds value of 7 different flags which can only have a value of 0 or 1 and hence can be represented in a single register. The bits represent the status of the processor.
5. Stack Pointer(SP) - The stack pointer hold the address to the current location on the Stack. The stack is a way to store data by pushing or popping data to and from a section of memory.
6. Program Counter(PC) - This is a 16-bit register unlike other registers which are only 8-bit in length, it indicates where the processor is in the program sequence.

## Flags

Instructions that save or restore the flags map them to bits in the architectural 'P' register as follows:
```
7  bit  0
---- ----
NV1B DIZC
|||| ||||
|||| |||+- Carry
|||| ||+-- Zero
|||| |+--- Interrupt Disable
|||| +---- Decimal
|||+------ (No CPU effect; see: the B flag)
||+------- (No CPU effect; always pushed as 1)
|+-------- Overflow
+--------- Negative


Initial     At Power 	    After Reset
A, X, Y 	0 	            unchanged
PC 	        ($FFFC) 	    ($FFFC)
S    	    $00 - 3 = $FD 	S -= 3      // 0x0100 - 0x01FF -> 0x0100 + SP, hence SP from 00 - FF (look wiki for why -3) (SP-- on stack push and vice versa)
C 	        0 	            unchanged
Z 	        0 	            unchanged
i 	        1 	            1
d 	        0 	            unchanged 
v 	        0 	            unchanged
n 	        0 	            unchanged
```

## Addressing Modes
Addressing modes and instruction timings are the same as those in the standard 6502.

1. Indexed Addressing: Indexed addressing modes use the X or Y register to help determine the address. The 6502 has six main indexed addressing modes.
2. Other addressing

## Memory Map
```
Address range 	Size 	Device
$0000–$07FF 	$0800 	2 KB internal RAM
$0800–$0FFF 	$0800 	Mirrors of $0000–$07FF
$1000–$17FF 	$0800
$1800–$1FFF 	$0800
$2000–$2007 	$0008 	NES PPU registers
$2008–$3FFF 	$1FF8 	Mirrors of $2000–$2007 (repeats every 8 bytes)
$4000–$4017 	$0018 	NES APU and I/O registers
$4018–$401F 	$0008 	APU and I/O functionality that is normally disabled. See CPU Test Mode.
$4020–$FFFF     $BFE0   Unmapped. Available for cartridge use.
• $6000–$7FFF   $2000   Usually cartridge RAM, when present.
• $8000–$FFFF 	$8000   Usually cartridge ROM and mapper registers.
```
