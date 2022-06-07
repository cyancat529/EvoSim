#include "Param.h"
#include <iostream>

Param InitParam(std::string fileName) {
    std::ifstream file(fileName);
    std::vector<std::string> parArr;
    std::string buffer;
    bool pass = true;
    Param p;

    while (getline(file, buffer)) {
        parArr.push_back(buffer);
    }

    if (parArr.size() < 10) pass = false;
    
    if (!pass) {
    notPass:
        if(fileName != "") std::cout << "CONFIG INSERTION FAILED" << std::endl;
        p.numberOfNeurons = 8;
        p.geneSize = 32;
        p.generationLength = 300;
        p.generationSize = 500;
        p.mutation = true;
        p.mutationChance = 0.001;
        p.autorun = true;
        p.autorunNumOfGen = 100;
        p.survivalCrit = 1;
        p.survivalRange = 15;
    }
    else {
        std::cout << "CONFIG INSERTED" << std::endl;
        p.numberOfNeurons = std::stoi(parArr[0]);
        p.geneSize = std::stoi(parArr[1]);
        p.generationLength = std::stoi(parArr[2]);
        p.generationSize = std::stoi(parArr[3]);
        p.mutation = std::stoi(parArr[4]);
        p.mutationChance = std::stof(parArr[5]);
        p.autorun = std::stoi(parArr[6]);
        p.autorunNumOfGen = std::stoi(parArr[7]);
        p.survivalCrit = std::stoi(parArr[8]);
        p.survivalRange = std::stoi(parArr[9]);
    }

    return p;
}
