#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#define limit 1000
#define true 1
#define false 0
//COMPILED WITH GCC//

static int count = 0; //Global variable for counting music files found

void hello_msg(){
    printf("\n");
    printf("  __  __                 _               _____                                         _                 \n");
    printf(" |  \\/  |               (_)             / ____|                                       | |                \n");
    printf(" | \\  / |  _   _   ___   _    ___      | |        ___    _ __   __   __   ___   _ __  | |_    ___   _ __ \n");
    printf(" | |\\/| | | | | | / __| | |  / __|     | |       / _ \\  | '_ \\  \\ \\ / /  / _ \\ | '__| | __|  / _ \\ | '__|\n");
    printf(" | |  | | | |_| | \\__ \\ | | | (__      | |____  | (_) | | | | |  \\ V /  |  __/ | |    | |_  |  __/ | |   \n");
    printf(" |_|  |_|  \\__,_| |___/ |_|  \\___|      \\_____|  \\___/  |_| |_|   \\_/    \\___| |_|     \\__|  \\___| |_|   \n");
    printf("\n");

}

char* get_current_dir(){ //Return the current directory (where the program is)
    static char cwd[limit];
    getcwd(cwd, sizeof(cwd));
    return cwd;
}

char* menu(){
    char in;
    static char cust_path[limit];
    do
    {
        printf("Type 0 to use the current directory as base, or 1 to specify a path \n\n");
        scanf(" %c",&in);
    }while ((in!='0')&&(in!='1'));
    if (in=='0') return get_current_dir();
    else if(in=='1') {
        printf("Enter the desired path: ");
        //scanf("%s",&cust_path);
        flush(stdin);
        gets(cust_path);
        return(cust_path);
    }
}

char is_music(char* string){ //Check if file is music
    if((strstr(string, ".mp3"))||(strstr(string, ".m4a"))||(strstr(string,".wav")||(strstr(string, ".wma"))||(strstr(string, ".ogg")))
    ||(strstr(string, ".aac"))||(strstr(string, ".flac"))) return true;
    else return false;
}

void list_files(char* dire){
    
    char new_dir[limit];
    struct dirent *dir;
    DIR *d = opendir(dire);
    if (!d) return; //Invalid directory

    while (dir = readdir(d)){ //While dir exists
        if ((strcmp(dir->d_name, "."))&&(strcmp(dir->d_name, ".."))){ // Drop ".."(parent directory)"."(current directory)
		    
            if(is_music(dir->d_name)==true) count++;
            strcpy(new_dir,dire); //strcpy(destination,source)  - copy string 'new_dire' to 'dire'
            strcat(new_dir,"/"); //strcat(destination, source) - concatenate string, adding "/"
            strcat(new_dir,dir->d_name); 
            list_files(new_dir);//Recursively search all directories and subdirectories
        }
    }
    closedir(d);
    
}

void output(){
    printf("\nTotal of music found: %d\n\n",count);
}

void flush ( FILE *in ){
  int ch;
  do
    ch = fgetc ( in ); 
  while ( ch != EOF && ch != '\n' ); 
  clearerr ( in );
}

void pause (){
  printf ( "Press [Enter] to continue . . ." );
  fflush (stdout);
  getchar();
} 

int main(void)
{
    hello_msg();
    list_files(menu());
    output();
    pause();
    return 0;
}
