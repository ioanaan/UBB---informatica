from domain.eveniment import Eveniment
from repo.repo_exception import RepoException

class EvenimentFileRepo:

    def __init__(self, filename):

            self.__evenimente = []
            self.__fName = filename
            self.__load_from_file()

    def __load_from_file(self):
        """
        Încarcă evenimentele din fișier în repository-ul din memorie.
        """
        self.__evenimente = []

        try:
            with open(self.__fName, "r") as f:
                linie = f.readline().strip()
                while linie != "":
                    valoare_atr = linie.split(";")
                    eveniment = Eveniment(int(valoare_atr[0]), valoare_atr[1], valoare_atr[2], valoare_atr[3])
                    self.__evenimente.append(eveniment)
                    linie = f.readline().strip()

        except FileNotFoundError:
            open(self.__fName, "w").close()

    def write_file(self):
        with open(self.__fName, "w") as f:
            for eveniment in self.__evenimente:
                linie = f"{eveniment.get_id_eveniment()};{eveniment.get_data()};{eveniment.get_timp()};{eveniment.get_descriere()}\n"
                f.write(linie)






    def adauga(self, eveniment):

        """
        Adaugă un eveniment în repository.
        Verifică dacă:
        - există deja un eveniment cu același ID
        - există deja un eveniment la aceeași dată și aceeași oră.

        Ridică RepoException în caz de duplicat.
        """

        for local_eveniment in self.__evenimente:
            if local_eveniment.get_id_eveniment() == eveniment.get_id_eveniment():
                raise RepoException(f"Evenimentul cu ID-ul {eveniment.get_id_eveniment()} există deja!")

            elif local_eveniment.get_data() == eveniment.get_data() and local_eveniment.get_timp() == eveniment.get_timp():
                raise RepoException(
                    f"Există deja eveniment la data {eveniment.get_data()} și la timpul {eveniment.get_timp()}!")

        self.__evenimente.append(eveniment)
        self.write_file()

    def get_all(self):

        """
        Returnează lista cu toate evenimentele stocate.
        """

        return self.__evenimente

    def update(self, eveniment):

        """
        Actualizează evenimentul cu același ID din repository.
        Dacă nu există, ridică RepoException.
        """

        for local_eveniment in self.__evenimente:
            if local_eveniment.get_id_eveniment() == eveniment.get_id_eveniment():
                local_eveniment.set_data(eveniment.get_data())
                local_eveniment.set_timp(eveniment.get_timp())
                local_eveniment.set_descriere(eveniment.get_descriere())
                self.write_file()

                return
        raise RepoException(f"Evenimentul cu ID-ul {eveniment.get_id_eveniment()} nu există!")

    def delete(self, id_eveniment):

        """
        Șterge evenimentul cu ID-ul dat.
        Dacă nu există, ridică RepoException.
        """

        for local_eveniment in self.__evenimente:
            if local_eveniment.get_id_eveniment() == id_eveniment:
                self.__evenimente.remove(local_eveniment)
                self.write_file()
                return

        raise RepoException(f"Evenimentul cu ID-ul {id_eveniment} nu există!")

    def __find_recursiv_aux(self, lista_evenimente, id_cautat, index_curent):
        """
        Caută recursiv un eveniment după ID.
        :return: Obiectul Eveniment dacă este găsit, altfel None.
        """

        # Cazul de Bază (Eșec): Indexul a depășit lista
        if index_curent >= len(lista_evenimente):
            return None

        eveniment_curent = lista_evenimente[index_curent]

        # Cazul de Bază (Succes): Evenimentul a fost găsit
        if eveniment_curent.get_id_eveniment() == id_cautat:
            return eveniment_curent

        # Pasul Recursiv: Continuăm căutarea cu următorul index
        return self.__find_recursiv_aux(lista_evenimente, id_cautat, index_curent + 1)

    def find(self, id_eveniment):

        """
        Caută și returnează evenimentul cu ID-ul dat (IMPLEMENTARE RECURSIVĂ).
        Dacă nu există, ridică RepoException.
        """

        eveniment_gasit = self.__find_recursiv_aux(self.__evenimente, id_eveniment, 0)

        if eveniment_gasit is None:
            raise RepoException(f"Evenimentul cu ID-ul {id_eveniment} nu există!")

        return eveniment_gasit

"""
    def find(self, id_eveniment):

        for local_eveniment in self.__evenimente:
            if local_eveniment.get_id_eveniment() == id_eveniment:
                return local_eveniment

        raise RepoException(f"Evenimentul cu ID-ul {id_eveniment} nu există!")
"""