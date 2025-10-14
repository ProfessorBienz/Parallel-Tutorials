// main.cpp
#include "src.hpp"
#include "mpi.h"
#include <Python.h>
#include <iostream>
#include <cstdlib>

// Expect these to be provided via your build system (like before)
// PY_SITE_PACKAGES and PY_MODULE_PATH are used to set sys.path.

void initialize()
{
    if (!Py_IsInitialized()) {
        Py_Initialize();
        PyRun_SimpleString("import sys, sysconfig, site");
        PyRun_SimpleString("sys.path.append(\"" PY_SITE_PACKAGES "\")");
        PyRun_SimpleString("sys.path.append(\"" PY_MODULE_PATH "\")");
    }
}

void finalize()
{
    if (Py_IsInitialized()) {
        Py_Finalize();
    }
}

void transpose_call(const char* py_func_name, double* A, double* AT, int local_n, int global_n)
{
    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    initialize();
    atexit(finalize);

    PyObject *pName = PyUnicode_DecodeFSDefault("main");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, py_func_name);
        if (pFunc && PyCallable_Check(pFunc)) {
            int size = local_n * global_n;

            PyObject* pyLocalN  = PyLong_FromLong(local_n);
            PyObject* pyGlobalN = PyLong_FromLong(global_n);
            PyObject* pyA = PyList_New(size);
            for (long i = 0; i < size; ++i) {
                PyObject* v = PyFloat_FromDouble(A[i]);
                PyList_SetItem(pyA, i, v);
            }

            PyObject* pArgs = PyTuple_New(3);
            PyTuple_SetItem(pArgs, 0, pyA);
            PyTuple_SetItem(pArgs, 1, pyLocalN);
            PyTuple_SetItem(pArgs, 2, pyGlobalN);
            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue && PyList_Check(pValue)) {
                for (int i = 0; i < size; i++)
                    AT[i] = PyFloat_AsDouble(PyList_GetItem(pValue, i));
                Py_DECREF(pValue);
            } else {
                PyErr_Print();
            }
        } else {
            PyErr_Print();
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }
}

void transpose(double* A, double* AT, int local_n, int global_n)
{
    transpose_call("transpose", A, AT, local_n, global_n);
}

void transpose_datatype(double* A, double* AT, int local_n, int global_n)
{
    transpose_call("transpose_datatype", A, AT, local_n, global_n);
}

void transpose_alltoall(double* A, double* AT, int local_n, int global_n)
{
    transpose_call("transpose_alltoall", A, AT, local_n, global_n);
}

int tutorial_main(int argc, char* argv[])
{
    initialize();
    atexit(finalize);

    PyObject *pName = PyUnicode_DecodeFSDefault("main");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != nullptr) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "main");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pValue = PyObject_CallObject(pFunc, nullptr);

            PyObject *sysModules = PyImport_GetModuleDict();
            PyObject *mpi4pyModule = PyDict_GetItemString(sysModules, "mpi4py");
            PyRun_SimpleString("import sys; sys.stdout.flush()");

            if (mpi4pyModule != nullptr)
                MPI_Init(&argc, &argv);

            if (pValue != nullptr) {
                Py_DECREF(pValue);
            } else {
                PyErr_Print();
                return -1;
            }
        } else {
            PyErr_Print();
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
    }

    MPI_Finalize();

    return 0;
}

