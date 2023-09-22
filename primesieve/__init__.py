"""
This module provides a C extension for generating prime numbers.

It contains the following function:

    * sieve - returns all prime numbers up to a given limit.
    * factors - returns the unique prime factors of each number up to a given limit.
"""

from ._primesieve import sieve, factors

__all__ = ["sieve", "factors"]
