#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

#define limit 1000
#define true 1
#define false 0

//COLORS//
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

//BOLD TEXT//
#define BOLD "\e[1;37m"

//UNDERLINE//
#define UNDER "\e[4;37m"

void hello_msg(){
    printf("\n");
    printf(CYAN " __  __           _          _____                  _    "RESET "\n");
    printf(GREEN "|  \\/  |         (_)        / ____|                | |           "RESET "\n");
    printf(YELLOW "| \\  / |_   _ ___ _  ___   | |     ___  _   _ _ __ | |_ ___ _ __ "RESET "\n");
    printf(BLUE "| |\\/| | | | / __| |/ __|  | |    / _ \\| | | | '_ \\| __/ _ \\ '__|"RESET "\n");
    printf(MAGENTA "| |  | | |_| \\__ \\ | (__   | |___| (_) | |_| | | | | ||  __/ |   "RESET "\n");
    printf(RED "|_|  |_|\\__,_|___/_|\\___|   \\_____\\___/ \\__,_|_| |_|\\__\\___|_|   "RESET "\n");
    printf("\n");


}
void flush(FILE *in){
    int ch;

    do{
        ch = fgetc (in); 
    }while(ch != EOF && ch != '\n'); 
    clearerr(in);
}

char* get_current_dir(){ //Return the current directory (where the program is)
    static char cwd[limit];

    getcwd(cwd, sizeof(cwd));
    return cwd;
}

char txt(){
    char yn[4];

    while(1){
        printf("Save a list of all music in a .txt file? [Y/n]: ");
        scanf("%s",yn);
        if((strcmp(yn, "y")==0)||((strcmp(yn, "Y")==0)||((strcmp(yn, "yes")==0)||((strcmp(yn, "Yes")==0)||((strcmp(yn, "YES")==0)))))) {
            printf(UNDER"\nA .txt file will be saved at: %s"RESET,get_current_dir());
            printf("\n\n");
            return true;
        }
        if (((strcmp(yn, "n")==0)||((strcmp(yn, "N")==0)||((strcmp(yn, "no")==0)||((strcmp(yn, "No")==0)||((strcmp(yn, "NO")==0))))))){
             printf("\n");
            return false;
        }
    }
}
char* menu(){
    char in[limit];
    static char cust_path[limit];

    while(1){
        printf("Type 0 to use the current directory as base, or 1 to specify a path: ");
        scanf("%s",in);
        printf("\n");
        if (strcmp(in,"0")==0) {
            flush(stdin);
            return get_current_dir();
        }
        else if(strcmp(in,"1")==0) {
            flush(stdin);
            printf("Enter the desired path: ");
            scanf("%[^\n]%*c",&cust_path);
            printf("\n");
            return cust_path;
        }
    }
}

char is_music(char* string){ //Check if file is music
    if((strstr(string, ".mp3"))||(strstr(string, ".m4a"))||(strstr(string,".wav")||(strstr(string, ".wma"))||(strstr(string, ".ogg")))
    ||(strstr(string, ".aac"))||(strstr(string, ".flac"))) return true;
    return false;
}

int count_music(char* music){ //return the position of array
    //mp3, m4a, wav, wma, ogg, aac, flac
    //[0]  [1]  [2]  [3]  [4]  [5]   [6]
    if((strstr(music, ".mp3"))){
        return 0;
    }
    else if ((strstr(music, ".m4a"))){
        return 1;
    }
    else if ((strstr(music, ".wav"))){
        return 2;
    }
    else if ((strstr(music, ".wma"))){
        return 3;
    }
    else if ((strstr(music, ".ogg"))){
        return 4;
    }
    else if ((strstr(music, ".aac"))){
        return 5;
    }
    else if ((strstr(music, ".flac"))){
        return 6;
    }
}

void write_txt(char* string){
    static char exists = false;
    FILE * fp;
    char name[20]="music_counter.txt";
    if( exists == true ) {// append file
        fp = fopen(name,"a");
        fprintf(fp,"%s\n",string);
        
    }
    else{// create empty file
        exists = true;
        fp = fopen(name,"w");
        fprintf(fp,"%s\n",string);
    }
    fclose(fp);
}
int* list_files(char txt, char* dire){
                            //mp3, m4a, wav, wma, ogg, aac, flac
                            //[0]  [1]  [2]  [3]  [4]  [5]   [6]
    static int contador[7]={   0,   0,   0,   0,   0,   0,    0 };
    char new_dir[limit];
    struct dirent *dir;
    DIR *d = opendir(dire);

    if (!d)  return; //Invalid directory
    
    while (dir = readdir(d)){ //While dir exists
        if ((strcmp(dir->d_name, "."))&&(strcmp(dir->d_name, ".."))){ // Drop ".."(parent directory)"."(current directory)
            if(is_music(dir->d_name)==true){//Check if file is music
                if(txt==true) {
                    write_txt(dir->d_name);//Write music to txt file
                }
                contador[count_music(dir->d_name)]++;
            } 
            strcpy(new_dir,dire); //strcpy(destination,source)  - copy string 'new_dire' to 'dire'
            strcat(new_dir,"/"); //strcat(destination, source) - concatenate string, adding "/"
            strcat(new_dir,dir->d_name); 
            list_files(txt,new_dir);//Recursively search all directories and subdirectories
        }
    }
    closedir(d);
    return contador;
}

void pauser(){
    flush(stdin);
    printf("\nPress [Enter] to continue . . .");
    flush(stdout);
    getchar();
} 

void output(int* contador){
    printf("-----------------------------------\n");
    int total=0;

    if (contador[0]!=0){
        printf(RED "MP3 files found: %d\n" RESET,contador[0]);
        total = contador[0];
    }
    if (contador[1]!=0){
        printf(GREEN "M4A files found:%d\n" RESET,contador[1]);
        total = contador[1]+total;
    }
    if (contador[2]!=0){
        printf(YELLOW "WAV files found:%d\n" RESET,contador[2]);
        total = contador[2]+total;
    }
    if (contador[3]!=0){
        printf(BLUE "WMA files found:%d\n" RESET,contador[3]);
        total = contador[3]+total;
    }
    if (contador[4]!=0){
        printf(MAGENTA "OGG files found:%d\n"RESET,contador[4]);
        total = contador[4]+total;
    }
    if (contador[5]!=0){
        printf("AAC files found:%d\n",contador[5]);
        total = contador[5]+total;
    }
    if (contador[6]!=0){
        printf(CYAN "FLAC files found:%d\n"RESET,contador[6]);
        total = contador[6]+total;
    }
    printf("-----------------------------------\n");
    printf(BOLD"TOTAL OF MUSIC FOUND: %d\n" RESET, total);
    
}

int main(void){
    hello_msg();
    output(list_files(txt(),menu()));
    pauser();
    return 0;
}
