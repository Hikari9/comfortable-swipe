/*
Comfortable Swipe
by Rico Tiongson

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Porting to Python */
#ifdef __COMFORTABLE_SWIPE__PYTHON__
#ifndef __COMFORTABLE_SWIPE__PYTHON_MAIN__
#define __COMFORTABLE_SWIPE__PYTHON_MAIN__

#include <iostream>
#include <Python.h>

// some useful readable macros
// http://python3porting.com/cextensions.html
#if PY_MAJOR_VERSION >= 3
  #define MOD_ERROR_VAL NULL
  #define MOD_SUCCESS_VAL(val) val
  #define MOD_INIT(name) PyMODINIT_FUNC PyInit_##name(void)
  #define MOD_DEF(ob, name, doc, methods) \
          static struct PyModuleDef moduledef = { \
            PyModuleDef_HEAD_INIT, name, doc, -1, methods, }; \
          ob = PyModule_Create(&moduledef);
#else
  #define MOD_ERROR_VAL
  #define MOD_SUCCESS_VAL(val)
  #define MOD_INIT(name) void init##name(void)
  #define MOD_DEF(ob, name, doc, methods) \
          ob = Py_InitModule3(name, methods, doc);
#endif /* PY_MAJOR_VERSION >= 3 */

static PyObject *
test(PyObject * self, PyObject * args, PyObject * kwargs)
{
    std::puts("TESTING FUNCTION");
    Py_RETURN_NONE;
}


// python module methods
static PyMethodDef comfortable_swipe_methods[] = {
    /* The cast of the function is necessary since PyCFunction values
     * only take two PyObject* parameters, and test() takes
     * three.
     */
    {
        "test",
        (PyCFunction) test,
        METH_VARARGS | METH_KEYWORDS,
        "Test"
    },
    {NULL, NULL, 0, NULL}   /* sentinel */
};

// how the python module is defined
MOD_INIT(comfortable_swipe)
{
    PyObject *m;

    MOD_DEF(m, "comfortable_swipe", "Comfortable swipe", comfortable_swipe_methods);

    if (m == NULL)
        return MOD_ERROR_VAL;

    return MOD_SUCCESS_VAL(m);
}

#endif /* __COMFORTABLE_SWIPE__PYTHON_MAIN__ */
#endif /* __COMFORTABLE_SWIPE__PYTHON__ */