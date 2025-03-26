#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to call the Python script to analyze the code
void analyze_code_with_python(const char *code_line) {
    // Prepare the command to run the Python script with the code line as input
    char command[2048];

    // Escape quotes in the code line for the Python script
    snprintf(command, sizeof(command), "python3 analyze_vulnerabilities.py \"%s\"", code_line);

    // Run the Python script
    system(command);
}

int main() {
    // Open the C source code file
    FILE *file = fopen("example_code.c", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read each line from the file
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Remove the newline character if it exists
        line[strcspn(line, "\n")] = '\0';

        // Analyze the current line of code using Python and CodeBERT
        printf("Analyzing line: %s\n", line);
        analyze_code_with_python(line);
    }

    fclose(file);
    return 0;
}
