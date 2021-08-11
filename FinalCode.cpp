/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FinalCode.cpp
 * Author: ulises
 * 
 * Created on 6 de julio de 2021, 19:36
 */

#include "FinalCode.h"

C0::FinalCode::FinalCode() {
}

C0::FinalCode::FinalCode(const FinalCode& orig) {
}

C0::FinalCode::~FinalCode() {
}

C0::FinalCode::FinalCode(string name, vector<C0::Quad> ci) {
    this->ci = ci;
    file.open(name);
}

void C0::FinalCode::translate() {
    if (file.is_open()) {
        for (unsigned int i = 0; i < ci.size(); i++) {
            processQuad(ci[i]);
        }
    }
    file.close();
}

void C0::FinalCode::processQuad(Quad q) {
    string arg1, arg2, inst, res;
    arg1 = q.getArg1();
    arg2 = q.getArg2();
    res = q.getRes();
    inst = q.getOp();

    if (inst == "+") {
        file << "ADD " << arg1 << ", " << arg2 << endl;
        file << "MOVE .A, " << res << endl;
    }
    else if (inst == "-") {
        file << "SUB " << arg1 << ", " << arg2 << endl;
        file << "MOVE .A, " << res << endl;
    }
    else if (inst == "*") {
        file << "MUL " << arg1 << ", " << arg2 << endl;
        file << "MOVE .A, " << res << endl;
    }
    else if (inst == "/") {
        file << "DIV " << arg1 << ", " << arg2 << endl;
        file << "MOVE .A, " << res << endl;
    } else if (inst == "||") {
        file << "OR " << arg1 << ", " << arg2 << endl;
        file << "MOVE .A, " << res << endl;
    } else if (inst == "&&") {
        file << "AND " << arg1 << ", " << arg2 << endl;
        file << "MOVE .A, " << res << endl;
    } else if (inst == ">") {
        file << "CMP " << arg2 << ", " << arg1 << endl;
        file << "BN $5" << endl;
        file << "MOVE #0, " << res << endl;
        file << "BR $3" << endl;
        file << "MOVE #1," << res << endl;
    } else if (inst == "<") {
        file << "CMP " << arg1 << ", " << arg2 << endl;
        file << "BN $5" << endl;
        file << "MOVE #0, " << res << endl;
        file << "BR $3" << endl;
        file << "MOVE #1," << res << endl;
    } else if (inst == "==") {
        file << "CMP " << arg1 << ", " << arg2 << endl;
        file << "BZ $5" << endl;
        file << "MOVE #0, " << res << endl;
        file << "BR $3" << endl;
        file << "MOVE #1," << res << endl;
    } else if (inst == "!=") {
        file << "CMP " << arg1 << ", " << arg2 << endl;
        file << "BN $5" << endl;
        file << "MOVE #1, " << res << endl;
        file << "BR $3" << endl;
        file << "MOVE #0," << res << endl;
    } else if (inst == "label") {
        file << res << ":";
    } else if (inst == "ifFalse") {
        file << "CMP #0, " << arg1 << endl;
        file << "BZ " << res << endl;
    } else if (inst == "goto") {
        file << "BR " << res << endl;
    } else if (inst == "printi") {
        file << "WRINT " << arg1 << endl;
    } else if (inst == "prints") {
        file << "WRSTR " << arg1 << endl;
    } else if (inst == "string") {
        file << arg1 << ": DATA" << res << endl;
    } else if (inst == "end") {
        file << "HALT" << endl;
    }

}