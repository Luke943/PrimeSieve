# Prime Sieve

Prime Sieve is a C extension module for Python that implements the Sieve of Eratosthenes algorithm to generate prime numbers.

1. The C source code is named `_primesieve.c`.
2. The `setup.py` file is used to build the extension module.

## Building

Clone the repository then run the following command to build and install:

```bash
pip install -e <path to this directory>
```

This requires having a C compiler installed.

## Usage

Now you can use the extension module in your Python code:

```python
import primesieve

primes = primesieve.sieve(100)
print(primes)
```

To test execution speed for sieve up to `N`, you can run:

```bash
python test.py N
```

If `N` is not provided, default value `10,000,000` is used.