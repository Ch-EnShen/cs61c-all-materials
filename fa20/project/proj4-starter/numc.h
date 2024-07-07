#include "matrix.h"

/*
 * Defines the struct that represents the object
 * Has the default PyObject_HEAD so it can be a python object
 * It also has the matrix that is being wrapped
 * is of type PyObject
 */
typedef struct {
    PyObject_HEAD
    matrix* mat;
    PyObject *shape;
} Matrix61c;

/* Function definitions */
static int init_rand(PyObject *self, int rows, int cols, double low, double high);
static int init_fill(PyObject *self, int rows, int cols, double val);
static int init_1d(PyObject *self, int rows, int cols, PyObject *lst);
static int init_2d(PyObject *self, PyObject *lst);
static void Matrix61c_dealloc(Matrix61c *self);
static PyObject *Matrix61c_new(PyTypeObject *type, PyObject *args, PyObject *kwds);
static int Matrix61c_init(PyObject *self, PyObject *args, PyObject *kwds);
static PyObject *Matrix61c_to_list(Matrix61c *self);
static PyObject *Matrix61c_repr(PyObject *self);
static PyObject *Matrix61c_set_value(Matrix61c *self, PyObject* args);
static PyObject *Matrix61c_get_value(Matrix61c *self, PyObject* args);
static PyObject *Matrix61c_add(Matrix61c* self, PyObject* args);
static PyObject *Matrix61c_sub(Matrix61c* self, PyObject* args);
static PyObject *Matrix61c_multiply(Matrix61c* self, PyObject *args);
static PyObject *Matrix61c_neg(Matrix61c* self);
static PyObject *Matrix61c_abs(Matrix61c *self);
static PyObject *Matrix61c_pow(Matrix61c *self, PyObject *pow, PyObject *optional);

