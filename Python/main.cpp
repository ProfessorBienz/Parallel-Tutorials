// https://docs.python.org/3/extending/embedding.html

#include "src.hpp"
#include "mpi.h"
#include <Python.h>

void initialize()
{
    Py_Initialize();
    
    PyRun_SimpleString("import sys, sysconfig, site");
    
    PyRun_SimpleString("sys.path.append(\"" PY_SITE_PACKAGES "\")");
    PyRun_SimpleString("sys.path.append(\"" PY_MODULE_PATH "\")");

    
    
}

void finalize()
{
    Py_Finalize();
}

double generate_random()
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pValue;

    double result = 0.0;

    // Initialize Python Interpreter
    initialize();
    atexit(finalize);

    // Find file
    pName = PyUnicode_DecodeFSDefault("main");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "generate_random");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pValue = PyObject_CallObject(pFunc, nullptr);
            if (pValue != NULL) {
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

    Py_Finalize();
    return result;
}

void generate_random_array(int N, double* arr)
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pValue;

    // Initialize Python Interpreter
    initialize();
    atexit(finalize);

    // Find file
    pName = PyUnicode_DecodeFSDefault("main");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "generate_random_array");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pArgs = PyTuple_Pack(1, PyLong_FromLong(N));
            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue && PyList_Check(pValue)) {
                Py_ssize_t len = PyList_Size(pValue);
                for (Py_ssize_t i = 0; i < len && i < N; i++) {
                    arr[i] = PyFloat_AsDouble(PyList_GetItem(pValue, i));
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

    Py_Finalize();
}

double time_random_array_generation(int N, double* arr)
{
    double elapsed = 0.0;

    PyObject *pName, *pModule, *pFunc;
    PyObject *pValue;

    // Initialize Python Interpreter
    initialize();
    atexit(finalize);

    // Find file
    pName = PyUnicode_DecodeFSDefault("main");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        PyObject *pFunc = PyObject_GetAttrString(pModule, "time_random_array_generation");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pArgs = PyTuple_Pack(1, PyLong_FromLong(N));
            PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue != NULL) {
                elapsed = PyFloat_AsDouble(pValue);
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

    Py_Finalize();
    return elapsed;
}


// Return 0
int tutorial_main(int argc, char* argv[])
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pValue;

    // Initialize Python Interpreter
    initialize();
    atexit(finalize);

    // Find file
    pName = PyUnicode_DecodeFSDefault("main");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL)
    {
        // Find function within file
        pFunc = PyObject_GetAttrString(pModule, "main");

        if (pFunc && PyCallable_Check(pFunc))
        {
            pValue = PyObject_CallObject(pFunc, nullptr);

            PyObject *sysModules = PyImport_GetModuleDict();
            PyObject *mpi4pyModule = PyDict_GetItemString(sysModules, "mpi4py");
            PyRun_SimpleString("import sys; sys.stdout.flush()");
            
            
            // Only pass MPI_Init test if loaded mpi4py module
            if (mpi4pyModule != NULL)
                MPI_Init(&argc, &argv);

            if (pValue != NULL)
            {
                Py_DECREF(pValue);
            }
            else 
            {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                printf("Call Failed\n");
                return -1;
            }
        }
        else
        {
            if (PyErr_Occurred())
                PyErr_Print();
            printf("Cannot find function %s\n", "main");
        }

        Py_DECREF(pFunc);
        Py_DECREF(pModule);
    }
    else
    {
        PyErr_Print();
        printf("Failed to locate file %s\n", "main.py");
    }

    MPI_Finalize();

    return 0;
}

