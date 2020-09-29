import unittest
from load import load

class AddTest(unittest.TestCase):
    def setUp(self):
        module = load('writenew')
    def test_addition(self):
        self.assertEqual(module.main_fun(1,"job.txt"), 2)

    def test_addition(self):
        self.assertEqual(module.main_fun(2,"job.txt"), 3)

if __name__ == "__main__":
    unittest.main()
