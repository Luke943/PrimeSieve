from distutils.core import setup, Extension

module = Extension(
    "primesieve",
    sources=["primesieve.c"],
)

setup(
    name="primesieve",
    version="1.0",
    description="Prime number sieve C extension",
    ext_modules=[module],
)
