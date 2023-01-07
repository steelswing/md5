/*
Ну вы же понимаете, что код здесь только мой?
Well, you do understand that the code here is only mine?
 */

/* 
 * File:   main.cpp
 * Author: LWJGL2
 *
 * Created on 13 июня 2022 г., 18:11
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#ifdef _WIN32
#include "color.h"
#endif

#include "md5.h"
#include <string>
#include <fstream>

using namespace std;

#ifndef _WIN32
#include <experimental/filesystem>
namespace fs = experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif
/*
 * 
 */
int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "Use md5 <path/to/file>" << std::endl;
        return 0;
    }

    std::string fileName = argv[1];


    if (!fs::exists(fileName.c_str())) {
        std::cout << "File " << fileName << " is not exists." << std::endl;
        return 0;
    }

    //Start opening your file
    std::ifstream inBigArrayfile;
    inBigArrayfile.open(fileName.c_str(), std::ios::binary | std::ios::in);

    //Find length of file
    inBigArrayfile.seekg(0, std::ios::end);
    long Length = inBigArrayfile.tellg();
    inBigArrayfile.seekg(0, std::ios::beg);

    //read in the data from your file
    char * InFileData = new char[Length];
    inBigArrayfile.read(InFileData, Length);

    //Calculate MD5 hash
    std::string localMD5 = md5(InFileData, Length);
    //Clean up
    delete [] InFileData;

    std::cout << "Name=" << fileName << ", MD5=" << localMD5 << std::endl;
    return 0;
}

