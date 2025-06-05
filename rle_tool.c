#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to perform Run Length Encoding (compression)
void runLengthEncode(FILE *infp, FILE *outfp) {
    int curr_char, prev_char;
    int count;

    prev_char = fgetc(infp);
    if (prev_char == EOF) {
        return; // Empty input file
    }
    count = 1;

    while ((curr_char = fgetc(infp)) != EOF) {
        if (curr_char == prev_char) {
            count++;
        } else {
            // Write the character and count
            fputc(prev_char, outfp);
            fprintf(outfp, "%d", count);
            prev_char = curr_char;
            count = 1;
        }
    }
    // Write last character and count
    fputc(prev_char, outfp);
    fprintf(outfp, "%d", count);
}

// Function to perform Run Length Decoding (decompression)
void runLengthDecode(FILE *infp, FILE *outfp) {
    int curr_char, count;
    char count_str[20]; // Enough to hold count as string
    int idx;

    while ((curr_char = fgetc(infp)) != EOF) {
        // curr_char is the character to repeat
        if (!isprint(curr_char) && curr_char != '\n' && curr_char != '\t' && curr_char != '\r') {
            fprintf(stderr, "Invalid compressed format: Non-printable character found\n");
            exit(EXIT_FAILURE);
        }

        // Read count as a number following the character
        idx = 0;
        int next_char;
        // Read consecutive digits
        while ((next_char = fgetc(infp)) != EOF && isdigit(next_char)) {
            if (idx < (int)(sizeof(count_str) - 1)) {
                count_str[idx++] = (char)next_char;
            } else {
                fprintf(stderr, "Count number too long in compressed file\n");
                exit(EXIT_FAILURE);
            }
        }
        count_str[idx] = '\0';

        if (idx == 0) {
            fprintf(stderr, "Invalid compressed format: count missing for character '%c'\n", curr_char);
            exit(EXIT_FAILURE);
        }

        // Convert count string to integer
        count = atoi(count_str);

        // Write the character count times
        for (int i = 0; i < count; i++) {
            fputc(curr_char, outfp);
        }

        // If next_char is not EOF and not a digit, it belongs to next run, so ungetc it back
        if (next_char != EOF && !isdigit(next_char)) {
            ungetc(next_char, infp);
        }
    }
}

void printUsage(const char *progName) {
    printf("Usage: %s <mode> <input_file> <output_file>\n", progName);
    printf("Mode:\n");
    printf("  c : compress\n");
    printf("  d : decompress\n");
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    char mode = argv[1][0];
    const char *input_filename = argv[2];
    const char *output_filename = argv[3];

    FILE *infile = fopen(input_filename, "rb");
    if (!infile) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    FILE *outfile = fopen(output_filename, "wb");
    if (!outfile) {
        perror("Error opening output file");
        fclose(infile);
        return EXIT_FAILURE;
    }

    if (mode == 'c') {
        runLengthEncode(infile, outfile);
        printf("File compressed successfully.\n");
    } else if (mode == 'd') {
        runLengthDecode(infile, outfile);
        printf("File decompressed successfully.\n");
    } else {
        fprintf(stderr, "Invalid mode: %c\n", mode);
        printUsage(argv[0]);
        fclose(infile);
        fclose(outfile);
        return EXIT_FAILURE;
    }

    fclose(infile);
    fclose(outfile);

    return EXIT_SUCCESS;
}

