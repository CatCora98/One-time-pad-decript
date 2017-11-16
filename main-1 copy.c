

/* 
 * File:   main.c
 * Author: Lettuce
 *
 * Created on October 8, 2017, 9:04 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *read_file(int len, char *filename);
void make_rand_key(int length, char *key);
void write_file(int len, char *filename, char *output);
void encrypt(char *clear_file, char *key_file, char *cipher_file);
void decrypt(char *key_file, char *cipher_file, char *message_file);

int main(int argc, const char * argv[]) {
                                 
    int choice = 0;
    // Loop until choice == 4
    while(choice != 4){
        printf("Welcome to the one time pad encryption\n");
        printf("Encrypt a file: 1\n");
        printf("Decrypt a file: 2\n");
        printf("Exit: 3\n");
        // Prompts user to select a choice from above list
        printf("Enter a choice: ");
        //gets the choice from user
        scanf("%d", &choice);
        switch (choice){
            case 1: 
                printf("Encrypting the message: ");
                encrypt("/Users/Desktop/test.txt", "/Users/Desktop/key.txt",
                         "/Users/Desktop/cipher.txt");
                printf("Your secrete message is ready.\n\n");
                break;
            case 2: // choice 2
                printf("Decrypting your message : ");
                decrypt("/Users/Desktop/key.txt", "/Users/Desktop/cipher.txt",
                         "/Users/Desktop/message.txt");
                break;
            case 3: // choice 3
                printf("Out the program \n\n");
                exit(51);
                break;
            default: // default set
                printf("Error input! Please try again.\n\n");
                break;
        }
    }
    return 0;
}

char *read_file(int len, char *filename){
    FILE *ptrFile = fopen(filename, "r"); //open file for reading
    if(!ptrFile){                         // file does not exist, throw error
        fputs("File can not found.\n", stderr);
        exit(1);
    }
    
    if(len == 0){                                     //if length is 0, count length of file
        while(getc(ptrFile) != EOF){                 //go through file until EOF read
            len++;                                    //increment the size of file for each char read
        }
        rewind(ptrFile);                                   //rewind to beginning of file
    }
    
    char *string = (char*) malloc(len+1);                //allocate memory for string input, plus one for null
    int j = 0;
    for(j = 0; j < len; j++){                             //read in chars from file to string
        string[j] = getc(ptrFile);
        
    }
    string[j] = '\0';                              //puts null at end of string
    
    if(string == NULL){                            //if there is no string to read
        fputs("No string to read.\n", stderr);       //show error
        return NULL;                               //return nothing
    }

    fclose(ptrFile);  
    return string;  
}

void write_file(int len, char *filename, char *output){
    FILE *ptrFile = fopen(filename, "w");                      //open file for writing
    if(ptrFile == NULL){                                       //if no file, throw error, exit program
        printf("File can not open.\n");
        exit(3);
    }
    
    int j = 0;
    if(len == 0){                                             //if length is 0
        while(output[j] != '\0'){                           //read file until null
              putc(output[j++], ptrFile);                   //writing each char to ptrFile
        }
    } else {                                                //  there is already a known length
        for(j=0; j < len; j++){
            putc(output[j], ptrFile);
        }
    }
    
    fclose(ptrFile); //close file
    return;
}



void make_rand_key(int length, char *key){
    
    srand((char)time(NULL));                        //seed the random generator
    
    int i = 0;
    for(i = 0; i < length; i++){
        key[i] = (char)rand() % 256;                //input a random char into key
        if(key[i] == EOF){                          //if EOF, make the value -2
            key[i] = EOF - 1;
        }
        if(key[i] == 0){                            //if null, make it 1
            key[i] = 1;
        }
    }
    key[i] = '\0';                                      //add null at end
    
    return; //
}

void encrypt(char *clear_file, char *key_file, char *cipher_file){
    int length = 0;                          //declare and initialize length  
    FILE *pointerKey = fopen(key_file, "w"); //open files  
    FILE *pointerCipher = fopen(clear_file, "r");
    
    
    char *input = read_file(length, clear_file); //read in contents from clear file, assign them to input
    printf("%s\n", input);                         //print input read in, to be used in console
    length = (int)strlen(input);                 //get length of the clear text to be used
    char key[length+1];                           //initialize char array key 
    char cipher[length+1];                      //initialize char array cipher 
    
    make_rand_key(length, key);
    
    write_file(length, key_file, key);          //write the key to file
    
    for(int i = 0; i < length; i++){ //go through clear file and key file, exclusive or'ing each byte to be put into cipher
        cipher[i] = input[i] ^ key[i];
    }
    printf("\n");
    cipher[length] = '\0';
    
    write_file(length, cipher_file, cipher); //write the cipher to file
    fclose(pointerKey);                           //close both files
    fclose(pointerCipher);
}

void decrypt(char *key_file, char *cipher_file, char *message_file){
    int len = 0;                                  //declare and initialize length
    FILE *ptrk = fopen(key_file, "r");            //open all files  
    FILE *ptrc = fopen(cipher_file, "r");
    FILE *ptrm = fopen(message_file, "w");
    
    char *key = read_file(len, key_file);           //read key file
    len = (int) strlen(key);                        //get length of key to be used
    char *cipher = read_file(len, cipher_file);     //read cipher file
    char message[len+1];                            //clear out size for char array message
    
    for(int i = 0; i < len; i++){ 
        message[i] = key[i] ^ cipher[i];        //This is the most essential part of lab, XOR
    }
    printf("%s\n\n", message);                  //print message result after XOR
    
    write_file(len, message_file, message);       //write the decrypted message to file
    fclose(ptrm);                                 //close all files
    fclose(ptrk);
    fclose(ptrc);
}

