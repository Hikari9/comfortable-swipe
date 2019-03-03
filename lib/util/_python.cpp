#ifndef __COMFORTABLE_SWIPE__util_python__
#define __COMFORTABLE_SWIPE__util_python__

#include "_index.hpp"
#include <Python.h>

// export as python module
namespace comfortable_swipe::util::python
{
    // create the python method signatures
    static PyObject *
    autostart_filename(PyObject * self, PyObject * args)
    {
        return Py_BuildValue("s", comfortable_swipe::util::autostart_filename());
    }

    static PyObject *
    conf_filename(PyObject * self, PyObject * args)
    {
        return Py_BuildValue("s", comfortable_swipe::util::conf_filename);
    }


    #undef __comfortable_swipe_void_method

    // create the method list for C++
    static PyMethodDef methods[] =
    {
        { "autostart_filename", &autostart_filename, METH_VARARGS, "the location of the autostart file" },
        { "conf_filename", &conf_filename, METH_VARARGS, "the location of the configuration file" },
        { NULL, NULL, 0, NULL } // sentinel
    };

    // create the module configuration
    #if PY_MAJOR_VERSION >= 3
    static struct PyModuleDef module_def =
    {
        PyModuleDef_HEAD_INIT,
        "util",
        "Comfortable swipe utility",
        -1,
        methods
    };
    #endif

    PyObject * module;
}

// initialize module
#if PY_MAJOR_VERSION >= 3
    PyMODINIT_FUNC
    PyInit_util(void)
    {
        using comfortable_swipe::util::python::module_def;
        using comfortable_swipe::util::python::module;
        if (module != NULL) return module;
        return module = PyModule_Create(&module_def);
    }
#else /* PY_MAJOR_VERSION < 3 */
    PyMODINIT_FUNC
    initutil(void)
    {
        using comfortable_swipe::util::python::methods;
        using comfortable_swipe::util::python::module;
        if (module != NULL) return;
        module = Py_InitModule("util", methods);
    }
#endif /* PY_MAJOR_VERSION */

#endif /* __COMFORTABLE_SWIPE__util_python__ */
