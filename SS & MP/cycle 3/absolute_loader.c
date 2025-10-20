#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simple 64KB memory array, initialized to 0
unsigned char memory[0xFFFF + 1] = {0};

int main()
{
    FILE *f_object;
    char line[100];
    char prog_name[7];
    char obj_code_str[70];
    char byte_str[3];

    unsigned int prog_start_addr = 0;
    unsigned int exec_start_addr = 0;
    unsigned int rec_addr, rec_len, byte_val;
    int i;

    f_object = fopen("object.txt", "r");
    if (f_object == NULL)
    {
        perror("Error opening object.txt");
        return 1;
    }

    printf("Loading object program into memory...\n");

    while (fgets(line, sizeof(line), f_object) != NULL)
    {

        if (line[0] == 'H')
        {
            // H^COPY  ^001000^000107

            // --- FIX IS HERE ---
            // Use %6c to read exactly 6 chars (including spaces)
            sscanf(line, "H^%6c^%6X", prog_name, &prog_start_addr);
            prog_name[6] = '\0'; // Manually add null terminator
            // --- END FIX ---
        }
        else if (line[0] == 'T')
        {
            // T^001000^1E^141033...
            sscanf(line, "T^%6X^%2X^%s", &rec_addr, &rec_len, obj_code_str);

            for (i = 0; i < rec_len; i++)
            {
                byte_str[0] = obj_code_str[i * 2];
                byte_str[1] = obj_code_str[i * 2 + 1];
                byte_str[2] = '\0';

                sscanf(byte_str, "%X", &byte_val);

                memory[rec_addr + i] = (unsigned char)byte_val;
            }
        }
        else if (line[0] == 'E')
        {
            // E^001000
            sscanf(line, "E^%6X", &exec_start_addr);
        }
    }
    fclose(f_object);

    printf("Loading complete.\n\n");

    // --- Print Memory Dump ---
    printf("--- Memory Contents ---\n");
    printf("Address   Contents (16 bytes per line)\n");
    printf("--------  ------------------------------------------------\n");

    // Use prog_start_addr (now correctly read) as the base
    for (i = 0; i < 16; i++)
    {
        unsigned int line_addr = prog_start_addr + (i * 16);
        printf("%04X      ", line_addr);

        for (int j = 0; j < 16; j++)
        {
            printf("%02X", memory[line_addr + j]);
            if ((j + 1) % 4 == 0)
                printf(" ");
        }
        printf("\n");
    }

    // Use exec_start_addr (which was already working)
    printf("\nProgram execution starts at: %06X\n", exec_start_addr);

    return 0;
}