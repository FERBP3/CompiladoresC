/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FinalCode.h
 * Author: ulises
 *
 * Created on 6 de julio de 2021, 19:36
 */

#ifndef FINALCODE_H
#define FINALCODE_H
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "Quad.h"

namespace C0{
class FinalCode {
public:
    FinalCode();
    FinalCode(string name, vector<Quad> ci);
    FinalCode(const FinalCode& orig);
    virtual ~FinalCode();
    void translate();
    void processQuad(Quad q);
private:
    ofstream file;
    vector<C0::Quad> ci;
    

};
}

#endif /* FINALCODE_H */

