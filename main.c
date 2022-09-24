#define VER "0.1"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void printHelp(){
    printf("TrigonometryCipherTool - console tool for encrypting and decrypting text with Trigonometry symmetric cipher.\n");
    printf("'Z_key' and 'Delta_X_key' are secret keys (can be any number) for encrypting and decoding.\n");
    printf("You can use:\n-e [filename] [Z_key] [Delta_X_key] to encrypt text from [filename];\n");
    printf("-d [filename] [Z_key] [Delta_X_key] to decode text from [filename]\n");
    printf("-i [word] [step-key] to encrypt single word from command line\n");
    printf("-h for help and -v for version\n");
}
void printError(){
    printf("Unknown command! Print '--help'\n");
}

void printVersion(){
    printf("Trigonometry Cipher tool version == %s\nWebsite - https://nichney.ru \nGithub - https://github.com/Karasik-piiiip/TrigonometryCipherTool \n", VER);
}

void encrypt(char filename[], double ZKEY, double DXKEY){
    long long size;
    FILE *fp; // file pointer
    fp = fopen(filename, "r");
    fseek(fp, 0LL, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0LL, SEEK_SET);
    unsigned char buf[size]; // Text to encrypt
    fread(buf, 1, size, fp);
    fclose(fp);

    char newFileName[255] = "enc_";
    strcat(newFileName, filename);
    fp = fopen(newFileName, "w");      

    for( long long i = 0; i < size; i++){
        buf[i] = ((int) buf[i] + (int)(256 * ( cos(ZKEY + (i+1) * DXKEY))) % 256); 
    }
    fwrite(buf, 1, size, fp);

    fclose(fp);  
}

void decrypt(char filename[], double ZKEY, double DXKEY){
    long long size;
    FILE *fp; // file pointer
    fp = fopen(filename, "r");
    fseek(fp, 0LL, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0LL, SEEK_SET);
    unsigned char buf[size]; // Text to decode
    fread(buf, 1, size, fp);
    fclose(fp);

    char newFileName[255] = "dec_";
    strcat(newFileName, filename);
    fp = fopen(newFileName, "w");      

    for( long long i = 0; i < size; i++){
        buf[i] = ((int) buf[i] - (int)(256 * ( cos(ZKEY + (i+1) * DXKEY))) % 256); 
    }
    fwrite(buf, 1, size, fp);

    fclose(fp);  
}


int main(int argc, char *argv[]){
    if (argc == 2){
        if ( strcmp("-h", argv[1]) == 0 || strcmp("-help", argv[1]) == 0  || strcmp("--h", argv[1]) == 0 || strcmp("--help", argv[1]) == 0)
            printHelp(); 
        else if ( strcmp("-v", argv[1]) == 0 || strcmp("-version", argv[1]) == 0  || strcmp("--v", argv[1]) == 0 || strcmp("--version", argv[1]) == 0)
            printVersion(); 
    }

    else if (argc == 5){

        if (strcmp("-d", argv[1]) == 0){ // -d [filename] [zkey] [dxkey]
            char filename[strlen(argv[2]) + 1];
            strcpy(filename, argv[2]);
            decrypt(filename, atof(argv[3]), atof(argv[4]));
        }

        else if (strcmp("-e", argv[1]) == 0){ // -e [filename] [zkey] [dxkey]
            char filename[strlen(argv[2]) + 1];
            strcpy(filename, argv[2]);
            encrypt(filename, atof(argv[3]), atof(argv[4]));
        }
        else
            printError();
    }
    else 
        printError();
    

    return 0;
}