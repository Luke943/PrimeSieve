from distutils.core import setup, Extension
import os

import numpy as np

NUMPY_INCLUDE = os.path.join(os.path.dirname(np.__file__), "core", "include")

module = Extension(
    name="primesieve._primesieve",
    sources=["primesieve/_primesieve.c"],
    include_dirs=[NUMPY_INCLUDE],
)

setup(
    name="primesieve",
    version="1.0",
    description="Prime number sieve C extension",
    ext_modules=[module],
    install_requires=["numpy"],
)
