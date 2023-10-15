//
// Created by Alexey Lapin on 3/23/23.
//

#ifndef COMPLMATH2_CPYTHON_H
#define COMPLMATH2_CPYTHON_H

#include <Python.h>
class CPython {
public:
    CPython(){
        init();
    }
    ~CPython(){
        clear();
    }
    void func1();
    void choose_functions_and_plot(int option);
    PyObject * getDict(){
        return pDict;
    }
private:
    void init();
    void clear();
    PyObject *sys, *sysPath, *folderPath, *pName, *pModule, *pDict;
};


#endif //COMPLMATH2_CPYTHON_H
