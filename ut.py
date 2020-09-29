import unittest
from load import load

class AddTest(unittest.TestCase):
    def test_addition(self):
        module = load('writenew')
        self.assertEqual(module.main_fun(1,"job.txt"), 2)


if __name__ == "__main__":
    unittest.main()
