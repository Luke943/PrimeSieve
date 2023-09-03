from distutils.core import setup, Extension

module = Extension(
    name="primesieve._primesieve",
    sources=["primesieve/_primesieve.c"],
)

setup(
    name="primesieve",
    version="1.0",
    description="Prime number sieve C extension",
    ext_modules=[module],
)
