from domain.persoana import Persoana
from repo.repo_exception import RepoException

class PersoanaFileRepo:

    def __init__(self, filename):

        self.__persoane = []
        self.__fName = filename
        self.__load_from_file()

    def __load_from_file(self):

        self.__persoane = []

        try:
            with(open(self.__fName, "r")) as f:
                linie = f.readline().strip()
                while linie != "":
                    valoare_atri = linie.split(";")
                    persoana = Persoana(int(valoare_atri[0]), valoare_atri[1], valoare_atri[2])
                    self.__persoane.append(persoana)
                    linie = f.readline().strip()

        except FileNotFoundError:
            open(self.__fName, "w").close()

    def write_file(self):

        with open(self.__fName, "w") as f:
            for persoana in self.__persoane:
                linie = f"{persoana.get_id_persoana()};{persoana.get_nume()};{persoana.get_adresa()}\n"
                f.write(linie)







    def adauga(self, persoana):

        """
        Adaugă o persoană în repository.
        Verifică dacă există deja o persoană cu același ID.
        Ridică RepoException în caz de duplicat.
        """

        for local_persoana in self.__persoane:
            if local_persoana.get_id_persoana() == persoana.get_id_persoana():
                raise RepoException(f"Persoana cu ID-ul {persoana.get_id_persoana()} există deja!")

        self.__persoane.append(persoana)
        self.write_file()

    def get_all(self):

        """
        Returnează lista cu toate persoanele stocate.
        """

        return self.__persoane


    def update(self, persoana):

        """
        Actualizează persoana cu același ID din repository.
        Dacă persoana nu există, ridică RepoException.
        """

        for local_persoana in self.__persoane:
            if local_persoana.get_id_persoana() == persoana.get_id_persoana():
                local_persoana.set_nume(persoana.get_nume())
                local_persoana.set_adresa(persoana.get_adresa())
                self.write_file()

                return

        raise RepoException(f"Persoana cu ID-ul {persoana.get_id_persoana()} nu există!")

    def delete(self, id_persoana):

        """
        Șterge persoana cu ID-ul dat.
        Dacă nu există, ridică RepoException.
        """

        for local_persoana in self.__persoane:
            if local_persoana.get_id_persoana() == id_persoana:
                self.__persoane.remove(local_persoana)
                self.write_file()
                return

        raise RepoException(f"Persoana cu ID-ul {id_persoana} nu există!")

    def find(self, id_persoana):

        """
        Caută și returnează persoana cu ID-ul dat (IMPLEMENTARE RECURSIVĂ).
        Dacă nu există, ridică RepoException.
        """

        persoana_gasita = self.__find_recursiv_aux(self.__persoane, id_persoana, 0)

        if persoana_gasita is None:
            raise RepoException(f"Persoana cu ID-ul {id_persoana} nu există!")

        return persoana_gasita

    def __find_recursiv_aux(self, lista_persoane, id_cautat, index_curent):
        """
        Caută recursiv o persoană după ID.
        :return: Obiectul Persoana dacă este găsit, altfel None.
        """

        if index_curent >= len(lista_persoane):
            return None

        persoana_curenta = lista_persoane[index_curent]

        if persoana_curenta.get_id_persoana() == id_cautat:
            return persoana_curenta

        return self.__find_recursiv_aux(lista_persoane, id_cautat, index_curent + 1)

"""
    def find(self, id_persoana):

        
        #Caută și returnează persoana cu ID-ul dat.
        #Dacă nu există, ridică RepoException.
        
        for local_persoana in self.__persoane:
            if local_persoana.get_id_persoana() == id_persoana:
                return local_persoana

        raise RepoException(f"Persoana cu ID-ul {id_persoana} nu există!")
"""