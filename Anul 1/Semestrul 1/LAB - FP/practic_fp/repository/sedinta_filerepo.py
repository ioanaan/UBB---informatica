from repository.repo_exception import RepoException
from domain.sedinta import Sedinta
from datetime import date
class SedinteFileRepo:

    def __init__(self, filename):

        self.__sedinte = []
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):

        self.__sedinte = []

        try:
            with open(self.__filename, "r") as f:
                for linie in f:
                    linie = linie.strip()
                    if linie:
                        val = linie.split(',')
                        sedinta = Sedinta(val[0], val[1], val[2], val[3])
                        self.__sedinte.append(sedinta)

        except FileNotFoundError:
            open(self.__filename, "w").close()

    def __save_file(self):
        """
        Salveaza in fisier sedinta
        """
        with open(self.__filename, "w") as f:
            for s in self.__sedinte:
                linie = f"{s.get_data()},{s.get_ora()},{s.get_subiect()},{s.get_stare()}\n"
                f.write(linie)

    def adaugare(self, sedinta_noua):
        """
        Adaugă o sedinta în repository.
        Ridică RepoException în caz de duplicat sau daca se
        incearca a se inregistra cu o data dinainte.
        """
        data_azi = date.today().strftime("%d/%m")

        if sedinta_noua.get_data() < data_azi:
            #nu se poate adauga o sedinta in urma
            raise RepoException("in urma nu se poate")

        for s in self.__sedinte:
            if s.get_subiect() == sedinta_noua.get_subiect() and s.get_stare() == sedinta_noua.get_stare():
                raise RepoException("Sedinta exista")

        self.__sedinte.append(sedinta_noua)
        self.__save_file()

    def get_all(self):
        return self.__sedinte