#include <string>
#include <fstream>
#include <iostream>
const int MAXURL = 1e5;
const int MAXCOUNT = 100;
const int MAXLEN = 20;

int main()
{
    srand(unsigned(time(NULL)));
    std::ofstream ofs("testdata.in", std::ios::in);
    if(!ofs.is_open()){
        printf("Cannot open file testdata.in\n");
        exit(-1);
    }
    for(int i = 0; i < MAXURL; i++){
        std::string url;
        int count = rand()%MAXCOUNT+1, len = rand()%MAXLEN+1;
        for(int i = 0; i < len; i++){
            char c = rand()%26+'a';
            url += c;
        }
        for(int i = 0; i < count; i++){
            ofs << url << std::endl; 
        }
    }
    return 0;
}

