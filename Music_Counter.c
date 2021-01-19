#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

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
    char yn[3];

    while(1){
        printf("Save a list of all music in a .txt file? [Y/n]: ");
        scanf(" %s",yn);
        if((strcmp(yn, "y")==0)||((strcmp(yn, "Y")==0)||((strcmp(yn, "yes")==0)||((strcmp(yn, "Yes")==0)||((strcmp(yn, "YES")==0)))))) {
            printf(YELLOW "\nA .txt file will be saved at: %s"RESET,get_current_dir());
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
        scanf(" %s",in);
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
void write_txt(char* string){
    static char exists = false;
    FILE * fp;
    char name[20]="music_counter.txt";
    if( exists == true ) {// append file
        fp = fopen(name,"a+");
        fprintf(fp,"%s\n",string);
        
    }
    else if (exists == false) {// create empty file
        exists = true;
        fp = fopen(name,"w");
        fprintf(fp,"%s\n",string);
    }
}
int list_files(char txt,char* dire){
    static int count = 0; //static variable for counting music files found
    char new_dir[limit];
    struct dirent *dir;
    DIR *d = opendir(dire);

    if (!d)  return; //Invalid directory
    
    while (dir = readdir(d)){ //While dir exists
        if ((strcmp(dir->d_name, "."))&&(strcmp(dir->d_name, ".."))){ // Drop ".."(parent directory)"."(current directory)
            if(is_music(dir->d_name)==true){
                if(txt==true) write_txt(dir->d_name);//Write to txt file
                count++;
            } 
            strcpy(new_dir,dire); //strcpy(destination,source)  - copy string 'new_dire' to 'dire'
            strcat(new_dir,"/"); //strcat(destination, source) - concatenate string, adding "/"
            strcat(new_dir,dir->d_name); 
            list_files(txt,new_dir);//Recursively search all directories and subdirectories
        }
    }
    closedir(d);
    return count;
}

void pause(){
    flush(stdin);
    printf("\nPress [Enter] to continue . . .");
    flush(stdout);
    getchar();
} 

int main(void){
    hello_msg();
    printf(RED "\nTotal of music found: %d\n"RESET ,list_files(txt(),menu()));
    pause();
    return 0;
}
