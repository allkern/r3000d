#include <stdio.h>
#include <stdint.h>

#include "r3000d.h"

// This sample program reads some code from a PlayStation 1 BIOS ROM file
// and disassembles it.
// Passing a pointer to an r3000d_state struct is optional, if NULL is passed
// then settings will be initialized to default values

int main(void) {
    uint32_t bios[128];

    char buf[512];

    // Set starting address (will be automatically incremented by 4
    // after each r3000d_disassemble call when state is not NULL)
    // Set disassembly options:
    // - print_address: Prepends the current instruction address
    // - print_opcode: Prepends the current instruction's assembly code
    // - hex_memory_offset: Print memory offset as hex
    r3000d_state state;

    state.addr = 0xbfc00000;
    state.print_address = 1;
    state.print_opcode = 1;
    state.hex_memory_offset = 1;

    FILE* file = fopen("SCPH101.BIN", "rb");

    fread(bios, 4, 29, file);

    for (int i = 0; i < 29; i++)
        puts(r3000d_disassemble(buf, bios[i], &state));

    state.addr = 0xbfc00150;

    fseek(file, 0x150, SEEK_SET);
    fread(bios, 4, 128, file);

    for (int i = 0; i < 128; i++)
        puts(r3000d_disassemble(buf, bios[i], &state));

    return 0;
}