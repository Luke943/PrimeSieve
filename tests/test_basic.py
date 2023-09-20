import primesieve
import unittest


class SieveTest(unittest.TestCase):
    def test_small(self):
        self.assertEqual(primesieve.sieve(2).tolist(), [2])
        self.assertEqual(primesieve.sieve(3).tolist(), [2, 3])
        self.assertEqual(
            primesieve.sieve(30).tolist(), [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
        )

    def test_detail(self):
        primes = primesieve.sieve(1000)
        self.assertEqual(primes[:5].tolist(), [2, 3, 5, 7, 11])
        self.assertEqual(primes[-5:].tolist(), [971, 977, 983, 991, 997])
        self.assertEqual(len(primes), 168)

    def test_large(self):
        self.assertEqual(len(primesieve.sieve(1_000_000)), 78_498)

    def test_error(self):
        self.assertRaises(ValueError, primesieve.sieve, 0)
        self.assertRaises(ValueError, primesieve.sieve, -1)
        self.assertRaises(TypeError, primesieve.sieve, "a")


if __name__ == "__main__":
    unittest.main()
