#include <bits/stdc++.h>
const int MAXBLOCK = 2e3; // max blocks in 
const int BASE = 97; // used as hash value
const int MAXOCCRC = 100; // the number of url we want to get at last

struct Data
{
    std::string url_name; // name of the url
    int url_count; // occurrences of the url
    Data(){}
    Data(std::string name, int count):url_name(name), url_count(count){}
    bool operator < (const Data &rhs)const
    {
        if(url_count != rhs.url_count)return url_count > rhs.url_count;
        else return url_name < rhs.url_name;
    }
};

void Map(std::ifstream &ifs, std::string output_dir)
{
    // @Map: divide different urls into different files
    // @param:
    //      @ifs: stringstream of the input file
    //      @output_dir: output directory
    // @ret: void
    std::ofstream *ofs = new std::ofstream[MAXBLOCK];
    for(int i = 0; i < MAXBLOCK; i++){
        std::string output_file = output_dir+std::to_string(i)+".txt";
        ofs[i].open(output_file.c_str(), std::ios::out|std::ios::trunc);
        if(!ofs[i].is_open()){
            printf("Cannot open file %s\n", output_file.c_str());
            exit(-1);
        }
    }
    std::string s;
    while(ifs >> s){
        int hash = 0;
        for(auto c: s){
            hash = (hash*BASE+c)%MAXBLOCK;
        }
        ofs[hash] << s << std::endl;
    }
    for(int i = 0; i < MAXBLOCK; i++){
        ofs[i].close();
    }
    delete[] ofs;
}

void Reduce(std::string output_dir)
{
    // Reduce: sort all the urls in different files, and select the top 100 urls from each file to get the final result
    // @param
    //      @output_dir: output directory
    // @ret: void
    std::string map_dir = output_dir+"/tmp/";
    std::vector<Data> url_tot;
    for(int i = 0; i < MAXBLOCK; i++){
        std::string filename = map_dir+std::to_string(i)+".txt"; //filename of each blocks
        std::ifstream ifs(filename, std::ios::in);
        std::string s;
        std::unordered_map<std::string, int> url_num; //count the ocurrencies of each urls
        while(ifs >> s){
            url_num[s]++;
        }
        std::vector<Data> url_file;
        for(auto p: url_num){
            url_file.push_back(Data(p.first, p.second));
        }
        sort(url_file.begin(), url_file.end()); // get the top 100 urls that appear most in this block
        int num = 0;
        for(auto p: url_file){
            if(num >= MAXOCCRC)break;
            else num++;
            url_tot.push_back(p);
        }
        ifs.close();
    }
    sort(url_tot.begin(), url_tot.end()); // get the top 100 urls that appear most in all blocks
    std::string output_file = output_dir+"/result.txt";
    std::ofstream ofs(output_file.c_str(), std::ios::out|std::ios::trunc);
    if(!ofs.is_open()){
        printf("Cannot open file %s\n", output_file.c_str());
        exit(-1);
    }
    int num = 0;
    for(auto data: url_tot){
        if(num >= MAXOCCRC)break;
        else num++;
        ofs << data.url_name << " " << data.url_count << std::endl; 
    }
    ofs.close();
}

int main(int argc, char* argv[])
{
    if(argc != 3){
        printf("Usage: %s input_file output_directory\n", argv[0]);
        exit(-1);
    }
    std::ifstream ifs(argv[1], std::ios::in);
    if(!ifs.is_open()){
        printf("Cannot open file %s\n", argv[1]);
        exit(-1);
    }
    std::string map_dir = std::string(argv[2])+"/tmp/";
    std::string cmd = "mkdir -p "+map_dir;
    if(system(cmd.c_str())){
        printf("Cannot create directory\n");
        exit(-1);
    }
    Map(ifs, map_dir);
    ifs.close();
    Reduce(std::string(argv[2]));
    return 0;
}

