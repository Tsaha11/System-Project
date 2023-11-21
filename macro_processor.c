#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODE_SIZE 1000
#define MAX_MACRO_SIZE 50

char code[MAX_CODE_SIZE];
char expanded_code[MAX_CODE_SIZE];
char macro_table[MAX_MACRO_SIZE][MAX_CODE_SIZE];
int macro_count = 0;

void process_macro_definitions() {
    char *token;
    char *rest = code;

    while ((token = strtok_r(rest, "\n", &rest))) {
        if (token[0] == '#' && token[1] == 'd' && token[2] == 'e' && token[3] == 'f') {
            // Extract macro name and body
            char *macro_name;
            char *macro_body;
            strtok_r(token, " ", &macro_name);
            macro_body = strtok_r(NULL, "", &macro_body);

            // Store in macro table
            strcpy(macro_table[macro_count], macro_body);
            macro_count++;
        }
    }
}

void expand_macros() {
    char *token;
    char *rest = code;
    expanded_code[0] = '\0';

    while ((token = strtok_r(rest, "\n", &rest))) {
        if (token[0] != '#') {
            // Check if the line has a macro invocation
            for (int i = 0; i < macro_count; i++) {
                char *macro_name;
                char *macro_args;
                strtok_r(macro_table[i], " ", &macro_name);
                macro_args = strtok_r(NULL, "", &macro_args);

                if (strstr(token, macro_name) != NULL) {
                    char expanded_line[MAX_CODE_SIZE];
                    sprintf(expanded_line, macro_table[i], macro_args);
                    strcat(expanded_code, expanded_line);
                }
            }
        } else {
            // Keep non-macro lines unchanged
            strcat(expanded_code, token);
        }
        strcat(expanded_code, "\n");
    }
}

void assemble() {
    // In a real assembler, you'd convert the expanded code into 8086 assembly language instructions
    // For simplicity, just print the expanded code
    printf("Assembling:\n%s\n", expanded_code);
}

void execute() {
    // Example: Simulate execution of the generated machine code
    // For simplicity, just print the execution steps
    printf("Executing:\n%s\n", expanded_code);
}

int main() {
    // Read source code into the 'code' array
    // For simplicity, let's assume the code contains macro definitions and invocations
    strcpy(code, "#define ADD_MACRO(x, y) ADD x, y\nADD_MACRO(5, 3)");

    process_macro_definitions();
    expand_macros();
    assemble();
    execute();

    return 0;
}