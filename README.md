# Prime Sieve

Prime Sieve is a C extension module for Python to generate prime numbers and prime factors.

### Key features

- Implement the Sieve of Eratosthenes algorithm to generate prime numbers.
- Sieve the unique prime factors for all numbers in a range.

## Building

Clone the repository then install:

```bash
python -m pip install [-e] path/to/PrimeSieve
```

## Usage

Now you can use the extension module in your Python code:

```python
>>> import primesieve  

>>> primesieve.sieve(100)
array([ 2,  3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
       61, 67, 71, 73, 79, 83, 89, 97], dtype=int64)

>>> primesieve.factors(100) 
array([[ 0,  0,  0],
       [ 0,  0,  0],
       [ 2,  0,  0],
       [ 3,  0,  0],
       [ 2,  0,  0],
        ...,
       [ 2,  3,  0],
       [97,  0,  0],
       [ 2,  7,  0],
       [ 3, 11,  0],
       [ 2,  5,  0]], dtype=int32)
```

Tests for functionality and performance are included in the `test` directory.
