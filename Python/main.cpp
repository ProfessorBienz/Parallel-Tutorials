// main.cpp
#include "src.hpp"
#include "mpi.h"
#include <Python.h>
#include <vector>
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
    Py_Finalize();
}

// --- Call Python send_recv_random ---
double send_recv_random()
{
    initialize();
    atexit(finalize);

    double result = 0.0;
    PyObject *pName = PyUnicode_DecodeFSDefault("main");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != nullptr) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "send_recv_random");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pValue = PyObject_CallObject(pFunc, nullptr);
            if (pValue != nullptr) {
                result = PyFloat_AsDouble(pValue);
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

    return result;
}

void ping_pong_send_and_recv(int N, double* send_array, double* recv_array)
{
    initialize();
    atexit(finalize);

    PyObject *pName = PyUnicode_DecodeFSDefault("main");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "ping_pong_send_and_recv");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pySend = PyList_New(N);
            for (int i = 0; i < N; i++)
                PyList_SetItem(pySend, i, PyFloat_FromDouble(send_array[i]));

            PyObject *pArgs = PyTuple_Pack(2, PyLong_FromLong(N), pySend);
            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue && PyList_Check(pValue)) {
                Py_ssize_t len = PyList_Size(pValue);
                for (Py_ssize_t i = 0; i < len && i < N; i++)
                    recv_array[i] = PyFloat_AsDouble(PyList_GetItem(pValue, i));
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

// --- Part 3: ping-pong Sendrecv ---
void ping_pong_sendrecv(int N, double* send_array, double* recv_array)
{
    initialize();
    atexit(finalize);

    PyObject *pName = PyUnicode_DecodeFSDefault("main");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "ping_pong_sendrecv");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pySend = PyList_New(N);
            for (int i = 0; i < N; i++)
                PyList_SetItem(pySend, i, PyFloat_FromDouble(send_array[i]));

            PyObject *pArgs = PyTuple_Pack(2, PyLong_FromLong(N), pySend);
            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue && PyList_Check(pValue)) {
                Py_ssize_t len = PyList_Size(pValue);
                for (Py_ssize_t i = 0; i < len && i < N; i++)
                    recv_array[i] = PyFloat_AsDouble(PyList_GetItem(pValue, i));
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


// --- Tutorial main entrypoint ---
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
