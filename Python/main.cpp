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


// Return 0
int tutorial_main(int argc, char* argv[])
{
    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

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

