#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>

static PyObject *
primesieve_sieve(PyObject *self, PyObject *args)
{
    Py_ssize_t input;
    if (!PyArg_ParseTuple(args, "n", &input))
    {
        PyErr_SetString(PyExc_TypeError, "Input must be an integer");
        return NULL;
    }

    if (input < 2)
    {
        PyErr_SetString(PyExc_ValueError, "Input must be greater than or equal to 2");
        return NULL;
    }

    size_t n = (size_t)input;
    size_t num_primes = (n - 1) / 2 + 1;
    size_t num_bytes = (num_primes + 7) / 8;

    unsigned char *is_prime = malloc(num_bytes);
    if (!is_prime)
    {
        PyErr_NoMemory();
        return NULL;
    }

    // Initialize bit array to all ones(all numbers are considered prime initially)
    memset(is_prime, 0xFF, num_bytes);

    size_t sqrt_n = (size_t)sqrt(n);
    for (size_t i = 3; i <= sqrt_n; i += 2)
    {
        if (is_prime[(i - 1) / 2 / 8] & (1 << ((i - 1) / 2 % 8)))
        {
            for (size_t j = i * i; j <= n; j += 2 * i)
            {
                is_prime[(j - 1) / 2 / 8] &= ~(1 << ((j - 1) / 2 % 8));
            }
        }
    }

    size_t count = 0;
    for (size_t i = 0; i < num_primes; i++)
    {
        if (is_prime[i / 8] & (1 << (i % 8)))
        {
            count++;
        }
    }

    PyObject *prime_array = PyArray_SimpleNew(1, (npy_intp[]){count}, NPY_INTP);
    if (!prime_array)
    {
        free(is_prime);
        PyErr_SetString(PyExc_MemoryError, "Failed to allocate memory for the NumPy array");
        return NULL;
    }

    *((Py_ssize_t *)PyArray_GETPTR1(prime_array, (npy_intp)0)) = 2;
    npy_intp index = 1;
    for (Py_ssize_t i = 1; i < num_primes; i++)
    {
        if (is_prime[i / 8] & (1 << (i % 8)))
        {
            *((Py_ssize_t *)PyArray_GETPTR1(prime_array, index++)) = 2 * i + 1;
        }
    }

    free(is_prime);
    return prime_array;
}

PyDoc_STRVAR(primesieve_sieve_doc,
             "primes(n, /)\n"
             "--\n\n"
             "Return an array of prime numbers <= n using the Sieve of Eratosthenes.\n");

static PyObject *
primesieve_factors(PyObject *self, PyObject *args)
{
    int n;
    if (!PyArg_ParseTuple(args, "i", &n))
    {
        PyErr_SetString(PyExc_TypeError, "Input must be an integer");
        return NULL;
    }

    if (n < 2)
    {
        PyErr_SetString(PyExc_ValueError, "Input must be greater than or equal to 2");
        return NULL;
    }

    n++;
    int prod = 1;
    int max_unique_factors = -1;
    int small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    while (prod < n)
    {
        prod *= small_primes[++max_unique_factors];
    }

    char *factor_counts = malloc(sizeof(char) * n);
    PyObject *prime_factors = (PyArrayObject *)PyArray_Zeros(2, (npy_intp[]){n, max_unique_factors}, PyArray_DescrFromType(NPY_INT), 0);
    if (!factor_counts || !prime_factors)
    {
        free(factor_counts);
        Py_XDECREF(prime_factors);
        PyErr_NoMemory();
        return NULL;
    }
    memset(factor_counts, 0x00, sizeof(char) * n);

    for (int i = 2; i < n; i++)
    {
        if (factor_counts[i])
        {
            continue;
        }
        for (int j = i; j < n; j += i)
        {
            *(int *)PyArray_GETPTR2(prime_factors, j, factor_counts[j]++) = i;
        }
    }

    free(factor_counts);
    return prime_factors;
}

PyDoc_STRVAR(primesieve_factors_doc,
             "factors(n, /)\n"
             "--\n\n"
             "Return a 2d array with unique prime factors for each number <= n.\n");

static PyMethodDef prime_methods[] = {
    {"sieve", (PyCFunction)primesieve_sieve, METH_VARARGS, primesieve_sieve_doc},
    {"factors", (PyCFunction)primesieve_factors, METH_VARARGS, primesieve_factors_doc},
    {NULL, NULL, 0, NULL} // Sentinel
};

static struct PyModuleDef primesievemodule = {
    PyModuleDef_HEAD_INIT,
    "_primesieve",
    PyDoc_STR("Prime number sieve -- C extension"),
    -1, // Don't have any state so can be set to -1.
    prime_methods};

PyMODINIT_FUNC PyInit__primesieve(void)
{
    import_array(); // Initialize NumPy
    return PyModule_Create(&primesievemodule);
}
