#include <stdio.h>

char *read_file(int len, char *filename);
void write_file(int len, char *filename, char *output);

int main() {
    
        printf("Welcome to the read and write program\n");
       
        // Prompts user to select a choice from above list
     
                char *input = read_file(0, "/Users/Desktop/message.txt");
                printf("input = \n|%s|\n", input);
                write_file(0, "/Users/Desktop/message.txt", "/Users/Desktop/out.txt");
                free(input);
                input = NULL;
                 return 0;

}

char *read_file(int len, char *filename) {
    FILE *fp = fopen(filename, "r"); //open file for reading
    if (fp==NULL) { // file does not exist, throw error
        printf("File can not found.\n");
        exit(1);
    }

    if (len == 0) { //if length is 0, count length of file
        while (getc(fp) != EOF) { //go through file until EOF read
            len++;
            printf("length = %d\n", len); //increment the size of file for each char read
            rewind(fp); //rewind to beginning of file
        }

        char *input = (char*) malloc(len + 1);
        //allocate memory for string input, plus one for null
        if (input == NULL) { //if there is no string to read
            printf("Error: Memory not allocated! ");
            //show error
            exit(2);
        }

        int j = 0;
        for (j = 0; j < len; j++) { //read in chars from file to string
            input[j] = getc(fp);
            input[j] = '\0'; //puts null at end of string
        }
            fclose(fp);
            return input;
        }
    }

        void write_file(int len, char *filename, char *output) {
            FILE *fp = fopen(filename, "w"); //open file for writing
            if (fp == NULL) { //if no file, throw error, exit program
                printf("File can not open.\n");
                exit(3);
            }

            int j = 0;
            if (len == 0) { //if length is 0
                while (output[j] != '\0') { //read file until null
                    putc(output[j++], fp); //writing each char to ptrFile
                }
            } else { //  there is already a known length
                for (j = 0; j < len; j++) {
                    putc(output[j], fp);
                }
            }
            fclose(fp); //close file
        }


