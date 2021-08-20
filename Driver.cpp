#include <cctype>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <sstream>

#include "Driver.hpp"
#include "FinalCode.h"

C0::Driver::~Driver() {
    delete (scanner);
    scanner = nullptr;
    delete (parser);
    parser = nullptr;
    //delete (table);
    //table = nullptr;
}

void C0::Driver::parse(const string& filename) {
    this->filename = filename;
    std::ifstream in_file(filename);
    if (!in_file.good()) {
        exit(EXIT_FAILURE);
    }
    parse_helper(in_file);
    return;
}

void C0::Driver::parse_helper(std::istream &stream) {

    delete (scanner);
    try {
        scanner = new C0::Scanner(&stream);
    }    catch (std::bad_alloc &ba) {
        std::cerr << "Failed to allocate scanner: (" << ba.what() << "), exiting!!\n";
        exit(EXIT_FAILURE);
    }

    delete (parser);
    try {
        parser = new C0::Parser((*scanner) /* scanner */,
                (*this) /* driver */);
    }    catch (std::bad_alloc &ba) {
        std::cerr << "Failed to allocate parser: (" << ba.what() << "), exiting!!\n";
        exit(EXIT_FAILURE);
    }
    const int accept(0);
    if (parser->parse() != accept) {
        std::cerr << "Parse failed!!\n";
    }
    return;
}

void C0::Driver::init() {
    tstack = Stack();
    gDir = 0;
    iStack = new PilaCount();
    wStack = new PilaCount();
    numIf = 0;
    numWhile = 0;
    numTemp = 0;
    numString = 0;
    gType = -1;
    gBase = -1;
    int pos = filename.find(".");
    output = filename.substr(0,pos-1)+".ens";
    dirStack = new PilaCount();
    typeStack = new PilaCount();
    pilaLabel = new PilaCount();
    //gId = "";
}

int C0::Driver::getSizeTable(){
    return tstack.getSize();
}

string C0::Driver::getTablaGlobalString(){
    return tstack.getGlobal()->toString();
}

C0::Table* C0::Driver::getTablaGlobal(){
    return tstack.getGlobal();
}

C0::Table* C0::Driver::getTablaTop(){
    return tstack.top();
}

bool C0::Driver::isInSymbolGlobal(string id){
    return tstack.getGlobal()->isInSymbol(id);
}

string C0::Driver::newLabel(int n) {
    stringstream l;
    l << "L" << n;
    return l.str();
}

string C0::Driver::newTemp() {
    stringstream l;
    l << "t" << numTemp;
    numTemp++;
    return l.str();
}

bool C0::Driver::isInSymbol(string id) {
    return tstack.top()->isInSymbol(id);
}

void C0::Driver::addSymbol(string id) {
    tstack.top()->addSymbol(id);
}

void C0::Driver::setDir(string id, int dir) {
    tstack.top()->setDir(id, dir);

}

void C0::Driver::setType(string id, int type) {
    tstack.top()->setType(id, type);
}

int C0::Driver::getType(string id) {
    return tstack.top()->getType(id);
}

int C0::Driver::getTypeGlobal(string id) {
    return tstack.getGlobal()->getType(id);
}

string C0::Driver::getTypeVarGlobal(string id){
    return tstack.getGlobal()->getTypeVar(id);
}

vector<int> C0::Driver::getArgsGlobal(string id){
    return tstack.getGlobal()->getArgs(id);
}

int C0::Driver::addType(string id, int numItems, int tipoBase){
    int next = tstack.top()->addType(id, tipoBase, numItems);

    return next;
}


void C0::Driver::setVar(string id, string var) {
    // TODO(48) Cambiar el uso de table por tstak, siempre obteniendo la tabla que se encuenta en el top de tstack
    tstack.top()->setTypeVar(id, var);
}

string C0::Driver::getVar(string id) {
    // TODO(49) Cambiar el uso de table por tstak, siempre obteniendo la tabla que se encuenta en el top de tstack
    return tstack.top()->getTypeVar(id);
}

C0::Expresion C0::Driver::add(Expresion e1, Expresion e2) {
    Expresion e;
    if (e1.getType() == e2.getType()) {
        e = Expresion(newTemp(), e1.getType());
        addQuad(Quad("+", e1.getDir(), e2.getDir(), e.getDir()));
        return e;
    }
    e.setType(-1);
    return e;
}

C0::Expresion C0::Driver::sub(Expresion e1, Expresion e2) {
    Expresion e3;
    if (e1.getType() == e2.getType()) {
        e3 = Expresion(newTemp(), e1.getType());
        addQuad(Quad("-", e1.getDir(), e2.getDir(), e3.getDir()));
        return e3;
    }
    e3.setType(-1);
    return e3;
}

C0::Expresion C0::Driver::mul(Expresion e1, Expresion e2) {
    Expresion e3;
    if (e1.getType() == e2.getType()) {
        e3 = Expresion(newTemp(), e1.getType());
        addQuad(Quad("*", e1.getDir(), e2.getDir(), e3.getDir()));
        return e3;
    }
    e3.setType(-1);
    return e3;
}

C0::Expresion C0::Driver::div(Expresion e1, Expresion e2) {
    Expresion e3;
    if (e1.getType() == e2.getType()) {
        e3 = Expresion(newTemp(), e1.getType());
        addQuad(Quad("/", e1.getDir(), e2.getDir(), e3.getDir()));
        return e3;
    }
    e3.setType(-1);
    return e3;
}

C0::Expresion C0::Driver::mod(Expresion e1, Expresion e2){
    Expresion e3;
    if (e1.getType() == e2.getType()) {
        e3 = Expresion(newTemp(), e1.getType());
        addQuad(Quad("%", e1.getDir(), e2.getDir(), e3.getDir()));
        return e3;
    }
    e3.setType(-1);
    return e3;

}

C0::Expresion C0::Driver::number(string num) {
    Expresion e3(num, 0);
    return e3;
}

C0::Expresion C0::Driver::ident(string id) {
    // TODO(51) Buscar el id en la tabla de la cima de la pila
    int type = tstack.top()->getType(id);

    // TODO(52) En caso de que el id no exista en la tabla de la cima buscar en la tabla global
    if (type == -1){
        type = tstack.getGlobal()->getType(id);
    }
    // TODO(53) Cambiar el uso de table por tstak, siempre obteniendo la tabla que se encuenta en el top de tstack
    //int type = table->getType(id);
    Expresion e2(id, type);
    return e2;
}

C0::Expresion C0::Driver::_or(Expresion e1, Expresion e2) {
    Expresion e3;
    if (e1.getType() == e2.getType()) {
        e3 = Expresion(newTemp(), e1.getType());
        addQuad(Quad("or", e1.getDir(), e2.getDir(), e3.getDir()));
        return e3;
    }
    e3.setType(-1);
    return e3;
}

C0::Expresion C0::Driver::_and(Expresion e1, Expresion e2) {
    Expresion e3;
    if (e1.getType() == e2.getType()) {
        e3 = Expresion(newTemp(), e1.getType());
        addQuad(Quad("and", e1.getDir(), e2.getDir(), e3.getDir()));
        return e3;
    }
    e3.setType(-1);
    return e3;
}

C0::Expresion C0::Driver::gt(Expresion e1, Expresion e2) {
    Expresion e3;
    if (e1.getType() == e2.getType()) {
        e3 = Expresion(newTemp(), e1.getType());
        addQuad(Quad(">", e1.getDir(), e2.getDir(), e3.getDir()));
        return e3;
    }
    e3.setType(-1);
    return e3;
}

C0::Expresion C0::Driver::gte(Expresion e1, Expresion e2) {
    Expresion e3;
    if (e1.getType() == e2.getType()) {
        e3 = Expresion(newTemp(), e1.getType());
        addQuad(Quad(">=", e1.getDir(), e2.getDir(), e3.getDir()));
        return e3;
    }
    e3.setType(-1);
    return e3;
}


C0::Expresion C0::Driver::lt(Expresion e1, Expresion e2) {
    Expresion e3;
    if (e1.getType() == e2.getType()) {
        e3 = Expresion(newTemp(), e1.getType());
        addQuad(Quad("<", e1.getDir(), e2.getDir(), e3.getDir()));
        return e3;
    }
    e3.setType(-1);
    return e3;
}

C0::Expresion C0::Driver::lte(Expresion e1, Expresion e2) {
    Expresion e3;
    if (e1.getType() == e2.getType()) {
        e3 = Expresion(newTemp(), e1.getType());
        addQuad(Quad("<=", e1.getDir(), e2.getDir(), e3.getDir()));
        return e3;
    }
    e3.setType(-1);
    return e3;
}

C0::Expresion C0::Driver::equal(Expresion e1, Expresion e2) {
    Expresion e3;
    if (e1.getType() == e2.getType()) {
        e3 = Expresion(newTemp(), e1.getType());
        addQuad(Quad("==", e1.getDir(), e2.getDir(), e3.getDir()));
        return e3;
    }
    e3.setType(-1);
    return e3;
}

C0::Expresion C0::Driver::distinct(Expresion e1, Expresion e2) {
    Expresion e3;
    if (e1.getType() == e2.getType()) {
        e3 = Expresion(newTemp(), e1.getType());
        addQuad(Quad("!=", e1.getDir(), e2.getDir(), e3.getDir()));
        return e3;
    }
    e3.setType(-1);
    return e3;
}

C0::Expresion C0::Driver::_not(Expresion e1){
    Expresion e2 = Expresion(newTemp(), e1.getType());
    addQuad(Quad("!", e1.getDir(), "", e2.getDir()));
    return e2;
}

void C0::Driver::asign(string id, Expresion e2) {
    int type = tstack.top()->getType(id);
    if (type == e2.getType()) {
        addQuad(Quad("=", e2.getDir(), "", id));
    }
}

void C0::Driver::_if(Expresion e, int n) {
    stringstream l;
    l << n;
    addQuad(Quad("ifFalse", e.getDir(), "goto", "LELSE"+l.str()));
}

void C0::Driver::_while(Expresion e, int n) {
    stringstream l, l2;
    l << "Lew" << n;
    addQuad(Quad("ifFalse", e.getDir(), "", l.str()));

}

void C0::Driver::_goto(string label, int n) {
    stringstream l;
    l << label << n;
    addQuad(Quad("goto", "", "", l.str()));
}

void C0::Driver::_label(string id) {
    stringstream l;
    l << id;
    addQuad(Quad("label", "", "", l.str()));
}

void C0::Driver::printCI() {
    cout << "Codigo intermedio " << ci.size() << endl;
    for (Quad q : ci) {
        if (q.getOp() == "=")
            cout << "\t\t" << q.getRes() << " " << q.getOp() << " " << q.getArg1() << endl;

        else if (q.getOp() == "label")
            cout << q.getRes() << ": " << endl;
        else if (q.getOp() == "ifFalse")
            cout << "\t\t" << q.getOp() << " " << q.getArg1() << " goto " << q.getRes() << endl;

        else if (q.getOp() == "goto")
            cout << "\t\t" << q.getOp() << " " << q.getRes() << endl;

        else if (q.getArg2() == "")
            cout << "\t\t" << q.getRes() << " = " << q.getOp() << " " << q.getArg1() << endl;
        else
            cout << "\t\t" << q.getRes() << " = " << q.getArg1() << " " << q.getOp() << " " << q.getArg2() << endl;

    }
}

void C0::Driver::printSymTab() {
    cout << "Tabla de símbolos" << endl;
    /*
    for (Symbol s : table->getSymTab()) {
        cout << s.getId() << "\t" << s.getDir() << "\t" << s.getType() << "\t" << s.getTypeVar() << endl;
    }
    */
}

void C0::Driver::writew(Expresion e) {
    addQuad(Quad("printi", e.getDir(), "", ""));
}

void C0::Driver::writes(string s,int c) {
    stringstream ss;
    ss << c;
    addQuad(Quad("prints", ss.str(), "", ""));
    addString(s);
}

void C0::Driver::generateStrings() {
    for (unsigned int i = 0; i < strings.size(); i++) {
        addQuad(Quad("string",strings[i],"",""));
    }

}

void C0::Driver::addString(string s){
    strings.push_back(s);
}

void C0::Driver::translate() {
    FinalCode fc(output, ci);
    fc.translate();
}

void C0::Driver::addQuad(Quad q) {
    ci.push_back(q);
}

// TODO(54) Programar la funcion miembro que envuelve a getName de la tabla de tipos
string C0::Driver::getNameTop(int id){
    return tstack.top()->getName(id);
}

string C0::Driver::getNameGlobal(int id){
    return tstack.getGlobal()->getName(id);
}

string C0::Driver::getClaseTop(string name){
    return tstack.top()->getClase(name);
}

string C0::Driver::getClaseGlobal(string name){
    return tstack.getGlobal()->getClase(name);
}

// TODO(55) Programar la funcion miembro que envuelve a getTam de la tabla de tipos
int C0::Driver::getTam(int id){
    return tstack.top()->getTam(id);
}

int C0::Driver::getTamGlobal(int id){
    return tstack.getGlobal()->getTam(id);
}

// TODO(56) Programar la funcion miembro que envuelve a getTipoBase de la tabla de tipos
int C0::Driver::getTipoBase(int id){
    return tstack.top()->getTipoBase(id);
}

int C0::Driver::getTipoBaseGlobal(int id){
    return tstack.getGlobal()->getTipoBase(id);
}

// TODO(57) Programar la funcion miembro que envuelve a getNumImtes de la tabla de tipos
int C0::Driver::getNumItems(int id){
    return tstack.top()->getNumItems(id);
}

// Funcion miembro que envuelve a getBase de la tabla de tipos
C0::Table* C0::Driver::getBase(int id){
    return tstack.top()->getBase(id);
}

C0::Table* C0::Driver::getBaseGlobal(int id){
    //printf("id getBase: %d\n", id);
    return tstack.getGlobal()->getBase(id);
}

// TODO(59) Programar la funcion miembro que envuelve a setBase de la tabla de tipos   
void C0::Driver::setBase(int id, Table* base){
    tstack.top()->setBase(id, base);
}

void C0::Driver::setArgsFunc(string id, vector<int> args){
    tstack.top()->setArgs(id, args);
}


bool C0::Driver::variable(string id){
    if(isInSymbol(id) || gBase == 0){
        cerr<<"La variable ya fue declarada o no puede ser de tipo void"<<endl;
        return false;
    }else{
        addSymbol(id);
        setType(id, gType);
        setDir(id, gDir);
        setVar(id, "variable");
        gDir+= getTam(gType);
        return true;
    }
}


//Función miembro que envuelva un push a tstack
void C0::Driver::pushTstack(){
    tstack.push();
}

//Función miembro que retorna un Table* al hacer pop a tstack
C0::Table* C0::Driver::popTstack(){
    return tstack.pop();
}

//Función miembro que añade el tipo struct a la tabla de tipos
// Como consejo usar la función miembro de Table setBase(Table *t)
int C0::Driver::addTypeStruct(string name, Table* t){
    int index = tstack.top()->addTypeStruct(name, t);
    //printf("addTypeStruct Driver:\n %s\n\n", t.toString().c_str());
    return index;
}

