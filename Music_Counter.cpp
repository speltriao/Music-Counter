//COMPILE WITH GCC FLAGS --std=c++17 -lstdc++fs//

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>


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


namespace fs = std::filesystem;

unsigned int cmp3=0, cm4a=0, cwav=0, cwma=0, cogg=0, caac=0,cflac=0; //Global counting variables//

void hello_msg(){
    std::cout <<"\n";
    std::cout<<CYAN " __  __           _          _____                  _    "RESET    "\n";
    std::cout<<GREEN "|  \\/  |         (_)        / ____|                | |           "RESET "\n";
    std::cout<<YELLOW "| \\  / |_   _ ___ _  ___   | |     ___  _   _ _ __ | |_ ___ _ __ "RESET "\n";
    std::cout<<BLUE "| |\\/| | | | / __| |/ __|  | |    / _ \\| | | | '_ \\| __/ _ \\ '__|"RESET "\n";
    std::cout<<MAGENTA "| |  | | |_| \\__ \\ | (__   | |___| (_) | |_| | | | | ||  __/ |   "RESET "\n";
    std::cout<<RED "|_|  |_|\\__,_|___/_|\\___|   \\_____\\___/ \\__,_|_| |_|\\__\\___|_|   "RESET "\n";
    std::cout<<"\n";
}

std::string menu(){
    char in;
    std::string cust_path;
    while(1){
        std::cout<<"Type 0 to use the current directory as base, or 1 to specify a path: ";
        std::cin>>in;
        std::cout<<"\n";
        if (in=='0') {
            return (fs::current_path());
        }
        else if (in=='1') {
            std::cout<<"Enter the desired path: ";
            std::cin>>cust_path;
            std::cout<<"\n";
            return cust_path;
        }
    }
}

bool txt(){
    std::string yn;
    while(1){
        std::cout<<"Save a list of all music in a .txt file? [Y/n]: ";
        std::cin>>yn;
        if((yn.compare("y")==0)||(yn.compare("Y")==0)||(yn.compare("yes")==0)||(yn.compare("Yes")==0)||(yn.compare("YES")==0)) {
    
            std::cout<<UNDER"\nA .txt file will be saved at:"<<fs::current_path()<<"\n\n"<<RESET;
            return true;
        }
        else if((yn.compare("n")==0)||(yn.compare("N")==0)||(yn.compare("no")==0)||(yn.compare("No")==0)||(yn.compare("NO")==0)) {
            return false;
        }
    }
}

bool is_music(std::string str){ //Check if file is music
    if(str.find(".mp3")!= std::string::npos){
        cmp3++;
        return true;
    }
    else if(str.find(".m4a")!= std::string::npos){
        cm4a++;
        return true;
    }
    else if(str.find(".wav")!= std::string::npos){
        cwav++;
        return true;
    }
    else if(str.find(".wma")!= std::string::npos){
        cwma++;
        return true;
    }
    else if(str.find(".oog")!= std::string::npos){
        cogg++;
        return true;
    }
    else if(str.find(".aac")!= std::string::npos){
        caac++;
        return true;
    }
    else if(str.find(".flac")!= std::string::npos){
        cflac++;
        return true;
    }
    else return false;
}

void write_txt(std::string str){
    static bool exists = false;
    std::ofstream txt;
    if(exists==true){
        txt.open ("Music_Counter.txt", std::ios_base::app); //Append mode
        txt<<"\n"+str;
    }
    else{
        exists=true;
        txt.open("Music_Counter.txt");
        txt<<str;
    }
    txt.close();
}

void list_files(std::string s,bool txt){
    std::string path = s;
    for (const auto & entry : fs::directory_iterator(path)){
        if((entry.is_regular_file())){
            if((is_music(entry.path())&&(txt==true))) write_txt(entry.path());
        }
        else if (entry.is_directory())   list_files(entry.path(),txt);
    }
}

void output(){
    std::cout<<"-----------------------------------\n\n";
    int total=0;
    if (cmp3!=0){
        std::cout<<RED "MP3 files found:"<<cmp3<<"\n";
        total = cmp3;
    }
    if (cm4a!=0){
        std::cout<<GREEN "M4A files found:"<<cm4a<<"\n";
        total = cm4a+total;
    }
    if (cwav!=0){
        std::cout<<YELLOW "WAV files found:" <<cwav<<"\n";
        total = cwav+total;
    }
    if (cwma!=0){
        std::cout<<BLUE "WMA files found:" <<cwma<<"\n";
        total = cwma+total;
    }
    if (cogg!=0){
        std::cout<<MAGENTA "OGG files found:" RESET <<cogg<<"\n";
        total = cogg+total;
    }
    if (caac!=0){
        std::cout<<"AAC files found:"<<caac<<"\n";
        total = caac+total;
    }
    if (cflac!=0){
        std::cout<<CYAN "FLAC files found:" RESET<<cflac<<"\n";
        total = cflac+total;
    }
    std::cout<<RESET"\n-----------------------------------\n";
    std::cout<< BOLD "\nTOTAL OF MUSIC FOUND:" RESET<< total<<"\n\n\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do {
       std::cout<<"Press enter to continue... ";
    }while (std::cin.get() != '\n');
}

int main(){
    hello_msg();
    list_files(menu(),txt());
    output();
    return 0;
}

