import sys
import time
import primesieve


def time_factors(n):
    start_time = time.perf_counter()
    prime_factors = primesieve.factors(n)
    end_time = time.perf_counter()
    return prime_factors, end_time - start_time


def main():
    try:
        limit = int(sys.argv[1])  # Choose the limit for factors
    except:
        limit = 1_000_000  # Default limit

    prime_factors, execution_time = time_factors(limit)
    print(
        f"Generated up to {len(prime_factors[0])} unique prime factors for each number up to {limit}"
    )
    print(f"Execution time: {execution_time:.6f} seconds")
    print(f"Memory use: {prime_factors.nbytes} bytes for results")


if __name__ == "__main__":
    main()
