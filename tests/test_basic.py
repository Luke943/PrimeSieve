import primesieve
import unittest


class SieveTest(unittest.TestCase):
    def test_sieve(self):
        self.assertEqual(primesieve.sieve(2).tolist(), [2])
        self.assertEqual(primesieve.sieve(3).tolist(), [2, 3])
        self.assertEqual(
            primesieve.sieve(30).tolist(), [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
        )

        primes = primesieve.sieve(1000)
        self.assertEqual(primes[:5].tolist(), [2, 3, 5, 7, 11])
        self.assertEqual(primes[-5:].tolist(), [971, 977, 983, 991, 997])
        self.assertEqual(len(primes), 168)

        self.assertEqual(len(primesieve.sieve(1_000_000)), 78_498)

        self.assertRaises(ValueError, primesieve.sieve, 0)
        self.assertRaises(ValueError, primesieve.sieve, -1)
        self.assertRaises(TypeError, primesieve.sieve, "a")

    def test_factors(self):
        self.assertEqual(primesieve.factors(5).shape, (6, 1))
        self.assertEqual(primesieve.factors(6).shape, (7, 2))

        prime_factors = primesieve.factors(20)
        self.assertEqual(prime_factors.shape, (21, 2))
        self.assertEqual(prime_factors[2].tolist(), [2, 0])
        self.assertEqual(prime_factors[3].tolist(), [3, 0])
        self.assertEqual(prime_factors[4].tolist(), [2, 0])
        self.assertEqual(prime_factors[17].tolist(), [17, 0])
        self.assertEqual(prime_factors[20].tolist(), [2, 5])

        prime_factors = primesieve.factors(1000)
        self.assertEqual(prime_factors.shape, (1001, 4))
        self.assertEqual(prime_factors[996].tolist(), [2, 3, 83, 0])
        self.assertEqual(prime_factors[997].tolist(), [997, 0, 0, 0])
        self.assertEqual(prime_factors[998].tolist(), [2, 499, 0, 0])
        self.assertEqual(prime_factors[999].tolist(), [3, 37, 0, 0])
        self.assertEqual(prime_factors[1000].tolist(), [2, 5, 0, 0])

        self.assertRaises(ValueError, primesieve.factors, 0)
        self.assertRaises(ValueError, primesieve.factors, -1)
        self.assertRaises(TypeError, primesieve.factors, "a")


if __name__ == "__main__":
    unittest.main()
