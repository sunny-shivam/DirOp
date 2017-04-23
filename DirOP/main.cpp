#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fstream>
//#include <boost/array.hpp>

using namespace std;

struct dirent *dir = NULL;

string file_type(int value){
    switch(value){
        case DT_BLK:      return "This is a block device.";

        case DT_CHR:      return "This is a character device.";

        case DT_DIR:      return "(directory)";

        case DT_FIFO:     return "This is a named pipe (FIFO).";

        case DT_LNK:      return "This is a symbolic link.";

        case DT_REG:      return "(regular file)";

        case DT_SOCK:     return "This is a UNIX domain socket.";

        case DT_UNKNOWN:  return "The file type could not be determined.";
        
        default:          return "Invalid option";
    }
}

fstream fptr;

void list_dir_recursively(string path){
    
    DIR *dr = NULL;
    
    char buffer[500];
    string dir_path = "";
    dr = opendir(path.c_str());
    
    if(dr){
        cout<<"\n Output for path : "<<path<<"\n\n";
        while(dir = readdir(dr)){
            strncpy(buffer, dir->d_name, 499);
            if((strcmp(buffer,"..")==0) || (strcmp(buffer,".")==0))continue;
            printf("\n%-20s\t d_type = %d ",buffer, dir->d_type);
            //printf("%s \t size= %d",file_type((int)dir->d_type).c_str(), dir->d_reclen);
            if(dir->d_type != DT_DIR)
            fptr << buffer;
            fptr << "\n";
            
            if(dir->d_type == DT_DIR){
                dir_path = path;
                dir_path += "/";
                dir_path += buffer;
                cout<<"\n sunny- Path = "<<dir_path<<" -- \n";
                fptr << "<" <<dir_path << ">\n\n";
                list_dir_recursively(dir_path);
            }
        }
        closedir(dr);
    }
    else{
        cout<<"\n Can not open dir = "<<path<<endl;
    }
    
}

int main(int argc, char** argv) {
    fptr.open ("/home/sunny/MyProject/dir_output/out.txt", ios::out);
    if(!fptr.is_open()){ 
        cout<<"\n Not able to open output file \n";
        return 0;
    }
    string path = "/media/sunny/MySpace/vSongs";
    fptr <<" Starting - <"<< path <<">\n";
    fptr <<"\n\n";
    list_dir_recursively(path);
    
    
    fptr.close();
    return 0;
}

