#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#define limit 1000
#define true 1
#define false 0
//COMPILED WITH GCC//

static int count = 0; //Global variable for counting music files found

char* get_current_dir(){ //Return the current directory (where the program is)
    static char cwd[limit];
    getcwd(cwd, sizeof(cwd));
    return cwd;
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

int main(void)
{
    char input;
    list_files(get_current_dir());
    printf("Total of music found: %d\n\n",count);
    printf("Press Enter to exit...");
    scanf("%c",&input);
    if (input==10) exit(0); //Char 10 is the "Enter" in ASCII//
    return 0;
}
