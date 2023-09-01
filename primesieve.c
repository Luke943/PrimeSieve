#include <Python.h>
#include <math.h>
// #include <time.h>

static PyObject *primesieve_sieve(PyObject *self, PyObject *args)
{
    // clock_t start_time = clock();
    int n;
    if (!PyArg_ParseTuple(args, "i", &n))
    {
        PyErr_SetString(PyExc_ValueError, "Input must be an integer");
        return NULL;
    }

    if (n < 2)
    {
        PyErr_SetString(PyExc_ValueError, "Input must be greater than or equal to 2");
        return NULL;
    }

    int num_primes = (n - 1) / 2 + 1;
    int num_bytes = (num_primes + 7) / 8;

    unsigned char *is_prime = (unsigned char *)malloc(num_bytes);
    if (!is_prime)
    {
        PyErr_NoMemory();
        return NULL;
    }

    // Initialize bit array to all ones (all numbers are considered prime initially)
    memset(is_prime, 0xFF, num_bytes);

    // clock_t init_time = clock();
    // printf("Initialization time: %f seconds\n", (double)(init_time - start_time) / CLOCKS_PER_SEC);

    int sqrt_n = (int)sqrt(n);
    for (int i = 3; i <= sqrt_n; i += 2)
    {
        if (is_prime[(i - 1) / 2 / 8] & (1 << ((i - 1) / 2 % 8)))
        {
            for (int j = i * i; j <= n; j += 2 * i)
            {
                is_prime[(j - 1) / 2 / 8] &= ~(1 << ((j - 1) / 2 % 8));
            }
        }
    }

    // clock_t sieve_time = clock();
    // printf("Sieve time: %f seconds\n", (double)(sieve_time - init_time) / CLOCKS_PER_SEC);

    int count = 0;
    for (int i = 0; i < num_primes; i++)
    {
        if (is_prime[i / 8] & (1 << (i % 8)))
        {
            count++;
        }
    }

    PyObject *prime_list = PyTuple_New(count);
    PyTuple_SetItem(prime_list, 0, PyLong_FromLong(2));
    int index = 1;
    for (int i = 1; i < num_primes; i++)
    {
        if (is_prime[i / 8] & (1 << (i % 8)))
        {
            PyTuple_SetItem(prime_list, index++, PyLong_FromLong(2 * i + 1));
        }
    }

    // clock_t PyList_time = clock();
    // printf("PyList time: %f seconds\n", (double)(PyList_time - sieve_time) / CLOCKS_PER_SEC);

    free(is_prime);

    return prime_list;
}

static PyMethodDef prime_methods[] = {
    {"sieve", primesieve_sieve, METH_VARARGS, "Generate prime numbers using the Sieve of Eratosthenes."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef primesievemodule = {
    PyModuleDef_HEAD_INIT,
    "primesieve",
    NULL,
    -1,
    prime_methods};

PyMODINIT_FUNC PyInit_primesieve(void)
{
    return PyModule_Create(&primesievemodule);
}
