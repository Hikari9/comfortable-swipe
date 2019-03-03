#ifndef __COMFORTABLE_SWIPE__service_python__
#define __COMFORTABLE_SWIPE__service_python__

#include "_index.hpp"
#include <Python.h>

// export as python module
namespace comfortable_swipe::service::python
{
    #define __comfortable_swipe_void_method(method) \
        static PyObject * \
        method(PyObject * self, PyObject * args) \
        { \
            comfortable_swipe::service::method(); \
            Py_RETURN_NONE; \
        }

    // create the python method signatures
    __comfortable_swipe_void_method(status);
    __comfortable_swipe_void_method(start);
    __comfortable_swipe_void_method(stop);
    __comfortable_swipe_void_method(restart);
    // __comfortable_swipe_void_method(autostart);
    __comfortable_swipe_void_method(buffer);
    __comfortable_swipe_void_method(help);
    __comfortable_swipe_void_method(config);
    __comfortable_swipe_void_method(debug);

    #undef __comfortable_swipe_void_method

    // create the method list for C++
    static PyMethodDef methods[] =
    {
        { "status", &status, METH_VARARGS , "checks status of program, autostart, and config" },
        { "start", &start, METH_VARARGS , "starts 3/4-finger gesture service" },
        { "stop", &stop, METH_VARARGS , "stops 3/4-finger gesture service" },
        { "restart", &restart, METH_VARARGS , "stops then starts 3/4-finger gesture service" },
        // { "autostart", &autostart, METH_VARARGS , "automatically run on startup (toggleable)" },
        { "buffer", &buffer, METH_VARARGS , "parses output of libinput debug-events" },
        { "help", &help, METH_VARARGS , "shows the help dialog" },
        { "config", &config, METH_VARARGS , "locates the config file " },
        { "debug", &debug, METH_VARARGS , "logs raw output from input events taken from libinput" },
        { NULL, NULL, 0, NULL } // sentinel
    };

    // create the module configuration
    #if PY_MAJOR_VERSION >= 3
    static struct PyModuleDef module_def =
    {
        PyModuleDef_HEAD_INIT,
        "service",
        "Comfortable swipe service",
        -1,
        methods
    };
    #endif

    PyObject * module;
}

// initialize module
#if PY_MAJOR_VERSION >= 3
    PyMODINIT_FUNC
    PyInit_service(void)
    {
        using comfortable_swipe::service::python::module_def;
        using comfortable_swipe::service::python::module;
        if (module != NULL) return module;
        return module = PyModule_Create(&module_def);
    }
#else /* PY_MAJOR_VERSION < 3 */
    PyMODINIT_FUNC
    initservice(void)
    {
        using comfortable_swipe::service::python::methods;
        using comfortable_swipe::service::python::module;
        if (module != NULL) return;
        module = Py_InitModule("service", methods);
    }
#endif /* PY_MAJOR_VERSION */

#endif /* __COMFORTABLE_SWIPE__service_python__ */
