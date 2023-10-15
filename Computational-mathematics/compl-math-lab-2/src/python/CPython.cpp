//
// Created by Alexey Lapin on 3/23/23.
//

#include "CPython.h"

void CPython::init() {
    Py_Initialize();
    do{
        sys = PyImport_ImportModule("sys");
        sysPath = PyObject_GetAttrString(sys, "path");
        folderPath = PyUnicode_FromString("/Users/aleksejlapin/CLionProjects/Вычмат2/src/python");
        PyList_Append(sysPath, folderPath);

        pName = PyUnicode_FromString("NonlinGrapher");
        if(!pName) break;
        pModule = PyImport_Import(pName);
        if(!pModule) break;
        pDict = PyModule_GetDict(pModule);
        if(!pDict) break;
        return;
    } while (false);
    PyErr_Print();
}

void CPython::clear() {
    Py_XDECREF(pDict);
    Py_XDECREF(pModule);
    Py_XDECREF(pName);

    Py_XDECREF(folderPath);
    Py_XDECREF(sysPath);
    Py_XDECREF(sys);

    Py_Finalize();
}

void CPython::func1() {
    PyObject *pFunc = PyDict_GetItemString(pDict, "func1");
    if(!pFunc || !PyCallable_Check(pFunc)){
        PyErr_Print();
    }
    PyObject *pValue = PyObject_CallObject(pFunc, NULL);
    Py_DECREF(pValue);

}

void CPython::choose_functions_and_plot(int option) {
    PyObject *pFunc = PyDict_GetItemString(pDict, "choose_functions_and_plot");
    PyRun_SimpleString("import numpy");
    PyRun_SimpleString("import matplotlib.pyplot as plt");

    PyImport_ImportModule("numpy");
    PyImport_ImportModule("matplotlib.pyplot");
    if(!pFunc || !PyCallable_Check(pFunc)){
        PyErr_Print();
        return;
    }
    PyObject *pArgs = PyTuple_Pack(1, PyLong_FromLong(option));
    PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
}
