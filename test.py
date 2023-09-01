import primesieve
import sys
import time


def time_sieve(n):
    start_time = time.time()
    primes = primesieve.sieve(n)
    end_time = time.time()
    # print(primes)
    return primes, end_time - start_time


def main():
    try:
        limit = int(sys.argv[1])  # Choose the limit for prime numbers
    except:
        limit = 10_000_000  # Default limit

    primes, execution_time = time_sieve(limit)
    print(f"Generated {len(primes)} prime numbers up to {limit}")
    print(f"Execution time: {execution_time:.6f} seconds")


if __name__ == "__main__":
    main()
