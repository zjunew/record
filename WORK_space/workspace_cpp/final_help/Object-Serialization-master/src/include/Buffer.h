#ifndef BUFFER_H
#define BUFFER_H
#include <fstream>
#include <iostream>
#include <string>
#include <exception>
#include "Typefigure.h"
#include "Seel.h"

class Buffer{
    public:
        explicit Buffer(const std::string& file,const bool state){
            if(state == in)
                fs.open(file,std::ios::in);
            else
                fs.open(file,std::ios::out);
            if(!fs){
                std::ios_base::failure exp("file open failed!");
                throw exp;
            }
                
        }
        ~Buffer(){
            fs.close();
        }

        
        int32_t writebin(const Seel&);
       
        int32_t readbin(Seel& parsel);

        static const bool in = true;
        static const bool out = false;
    private:
        std::fstream fs;
        //char *buf;
};


int32_t Buffer::writebin(const Seel& parsel){

    char *buf = new char[parsel.getbytes()];
    parsel.writebytes(buf);
    fs.write(buf,parsel.getbytes());
    delete[] buf;
    return parsel.getbytes();
}

int32_t Buffer::readbin(Seel& parsel){
    
    char tmp;
    int32_t meta_num;
    size_t atom_size;
    size_t total = 0;
    char* buf;
    fs.read(&tmp,sizeof(char));
    fs.read((char *)&meta_num,sizeof(int32_t));
    fs.read((char*)&atom_size,sizeof(size_t));
    if(parsel.return_type==STRING)
        total = meta_num*atom_size+sizeof(char)+sizeof(int32_t)+sizeof(size_t);
        
    else
        total = atom_size+sizeof(char)+sizeof(int32_t)+sizeof(size_t);
    //
    buf = new char[(int)total];
    //
    fs.seekg(0,std::ios::beg);
    fs.read(buf,total);
    parsel.deserialize_frombytes(buf);
    delete[] buf;

    return total;
}

#endif