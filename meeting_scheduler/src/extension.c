#include <Python.h>
#include "tools/connector.h"
#include "tools/resetter.h"
#include "tools/scheduler.h"

#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))

struct module_state {
    PyObject* error;
};

PyDoc_STRVAR(initialize__doc__,
"initialize()\n\n"
"Initializes connectiont to the database\n"
);

static PyObject *initialize(PyObject *self, PyObject *args) {
    int ret = connector_initialize();
    if (ret) {
        PyErr_SetString(PyExc_Exception, "Connection Error");
        return NULL;
    }
    Py_RETURN_NONE;
}

PyDoc_STRVAR(reset__doc__,
"reset(seed, num) -> int\n\n"
"Resets database\n\n"
"Arguments:\n"
"        seed {int} -- seed\n"
"        num {str} -- number of meetings\n"
);

static PyObject *reset(PyObject *self, PyObject *args) {
    long seed, num;
    if (!PyArg_ParseTuple(args, "ll", &seed, &num)) {
        return NULL;
    }
    int ret = resetter_reset(seed, num);
    if (ret) {
        PyErr_SetString(PyExc_Exception, "Reset Error");
        return NULL;
    }
    Py_RETURN_NONE;
}

PyDoc_STRVAR(schedule__doc__,
"schedule(verbose, fn) -> int\n\n"
"Schedules meetings from database\n\n"
"Arguments:\n"
"        verbose {int} -- verbose level, 0, 1, 2\n"
"        fn {str} -- file name\n"
);

static PyObject *schedule(PyObject *self, PyObject *args) {
    long verbose;
    const char *fn;
    if (!PyArg_ParseTuple(args, "ls", &verbose, &fn)) {
        return NULL;
    }
    FILE *fout = 0;
    if (strcmp(fn, "stdout")) {
        fout = fopen(fn, "wb");
    } else {
        fout = stdout;
    }
    if (verbose && !fout) {
        PyErr_SetString(PyExc_Exception, "Cannot open file");
        return NULL;
    }
    unsigned out;
    int ret = scheduler_schedule(&out, verbose, fout);
    if (ret) {
        PyErr_SetString(PyExc_Exception, "Schedule error");
        return NULL;
    }
    return PyLong_FromLong(out);
}

PyDoc_STRVAR(finalize__doc__,
"finalize()\n\n"
"Finalizes connectiont to the database\n"
);

static PyObject *finalize(PyObject *self, PyObject *args) {
    connector_finalize();
    Py_RETURN_NONE;
}

static PyMethodDef meetingscheduler_methods[] = {
    {"initialize", (PyCFunction)initialize, METH_VARARGS, initialize__doc__},
    {"reset", (PyCFunction)reset, METH_VARARGS, reset__doc__},
    {"schedule", (PyCFunction)schedule, METH_VARARGS, schedule__doc__},
    {"finalize", (PyCFunction)finalize, METH_VARARGS, finalize__doc__},
    {0}
};

static int meetingscheduler_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int meetingscheduler_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "meetingscheduler",
    NULL,
    sizeof(struct module_state),
    meetingscheduler_methods,
    NULL,
    meetingscheduler_traverse,
    meetingscheduler_clear,
    NULL
};

PyMODINIT_FUNC PyInit_meetingscheduler(void) {
    PyObject *module = PyModule_Create(&moduledef);
    if (!module) return NULL;
    return module;
}

