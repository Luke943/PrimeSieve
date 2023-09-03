"""
This module provides a C extension for generating prime numbers.

It contains the following function:

    * sieve - returns all prime numbers up to a given limit.
"""

from ._primesieve import sieve

__all__ = ["sieve"]
