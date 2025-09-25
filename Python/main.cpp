// main.cpp
#include "src.hpp"
#include "mpi.h"
#include <Python.h>
#include <iostream>

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

// --- Utility: build args (send_array, N) ---
PyObject* build_args(double* sendbuf, int N) {
    PyObject *pySend = PyList_New(N);
    for (int i = 0; i < N; i++) {
        PyList_SetItem(pySend, i, PyFloat_FromDouble(sendbuf[i])); // steals ref
    }

    PyObject *pyN = PyLong_FromLong(N);

    PyObject *pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, pySend); // steals pySend
    PyTuple_SetItem(pArgs, 1, pyN);    // steals pyN

    return pArgs; // caller must DECREF
}

// --- Wrapper: allgather_simple ---
void allgather_simple(double* sendbuf, double* recvbuf, int N)
{
    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    initialize();
    atexit(finalize);

    PyObject *pName = PyUnicode_DecodeFSDefault("main");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "allgather_simple");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pArgs = build_args(sendbuf, N);
            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue && PyList_Check(pValue)) {
                Py_ssize_t len = PyList_Size(pValue);
                for (Py_ssize_t i = 0; i < len && i < N * num_procs; i++) {
                    recvbuf[i] = PyFloat_AsDouble(PyList_GetItem(pValue, i));
                }
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

// --- Wrapper: allgather_pairwise ---
void allgather_pairwise(double* sendbuf, double* recvbuf, int N)
{
    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    initialize();
    atexit(finalize);

    PyObject *pName = PyUnicode_DecodeFSDefault("main");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "allgather_pairwise");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pArgs = build_args(sendbuf, N);
            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue && PyList_Check(pValue)) {
                Py_ssize_t len = PyList_Size(pValue);
                for (Py_ssize_t i = 0; i < len && i < N * num_procs; i++) {
                    recvbuf[i] = PyFloat_AsDouble(PyList_GetItem(pValue, i));
                }
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

// --- Wrapper: allgather_ring ---
void allgather_ring(double* sendbuf, double* recvbuf, int N)
{
    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    initialize();
    atexit(finalize);

    PyObject *pName = PyUnicode_DecodeFSDefault("main");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "allgather_ring");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pArgs = build_args(sendbuf, N);
            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue && PyList_Check(pValue)) {
                Py_ssize_t len = PyList_Size(pValue);
                for (Py_ssize_t i = 0; i < len && i < N * num_procs; i++) {
                    recvbuf[i] = PyFloat_AsDouble(PyList_GetItem(pValue, i));
                }
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

// --- Entry point ---
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

