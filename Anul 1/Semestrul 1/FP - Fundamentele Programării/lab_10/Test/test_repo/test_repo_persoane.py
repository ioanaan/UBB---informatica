import unittest
from repo.repo_exception import RepoException
from domain.persoana import Persoana
from repo.persoana_file_repo import PersoanaFileRepo

class TestPersoanaFileRepo(unittest.TestCase):

    def setUp(self):
        self.test_file = "test_persoane.txt"
        open(self.test_file, "w").close()
        self.repo = PersoanaFileRepo(self.test_file)

    def tearDown(self):
        open(self.test_file, "w").close()

    def test_addPersoana(self):
        p = Persoana(1, "Ana", "Strada Mare")
        self.repo.adauga(p)

        lista = self.repo.get_all()
        self.assertEqual(len(lista), 1)
        self.assertEqual(lista[0].get_id_persoana(), 1)
        self.assertEqual(lista[0].get_nume(), "Ana")
        self.assertEqual(lista[0].get_adresa(), "Strada Mare")

        # Adăugare duplicat -> EROARE
        with self.assertRaises(RepoException):
            self.repo.adauga(Persoana(1, "Alt Nume", "Alta Adresa"))

    def test_updatePersoana(self):
        p = Persoana(1, "Ana", "Strada Veche")
        self.repo.adauga(p)

        updated = Persoana(1, "Maria", "Strada Noua")
        self.repo.update(updated)

        lista = self.repo.get_all()
        self.assertEqual(lista[0].get_nume(), "Maria")
        self.assertEqual(lista[0].get_adresa(), "Strada Noua")

        # Update inexistent -> EROARE
        with self.assertRaises(RepoException):
            self.repo.update(Persoana(10, "X", "Y"))

    def test_deletePersoana(self):
        p = Persoana(1, "Ana", "X")
        self.repo.adauga(p)

        self.repo.delete(1)
        self.assertEqual(len(self.repo.get_all()), 0)

        # Ștergere persoană inexistentă -> EROARE
        with self.assertRaises(RepoException):
            self.repo.delete(10)

    def test_findPersoana(self):
        p = Persoana(1, "Ana", "Adresa")
        self.repo.adauga(p)

        found = self.repo.find(1)
        self.assertEqual(found.get_nume(), "Ana")
        self.assertEqual(found.get_adresa(), "Adresa")

        with self.assertRaises(RepoException):
            self.repo.find(999)