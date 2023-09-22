import sys
import time
import primesieve


def time_sieve(n):
    start_time = time.perf_counter()
    primes = primesieve.sieve(n)
    end_time = time.perf_counter()
    # print(primes)
    return primes, end_time - start_time


def main():
    try:
        limit = int(sys.argv[1])  # Choose the limit for prime numbers
    except:
        limit = 10_000_000  # Default limit

    sieve_size = ((limit - 1) // 2 + 1 + 7) // 8

    primes, execution_time = time_sieve(limit)
    print(f"Generated {len(primes)} prime numbers up to {limit}")
    print(f"Execution time: {execution_time:.6f} seconds")
    print(f"Memory use: {sieve_size} bytes to sieve, {primes.nbytes} bytes for results")


if __name__ == "__main__":
    main()
