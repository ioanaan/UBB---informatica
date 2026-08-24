from domain.eveniment import Eveniment
from domain.validator.eveniment_validator import EvenimentValidator

class ServiceEve:
    """
    Service pentru gestionarea operațiilor legate de evenimente.
    Coordonează validarea și interacțiunea cu repository-ul de evenimente.
    """

    def __init__(self, repo_evenimente):
        """
        Initializează service-ul cu repository-urile de persoane și evenimente.
        """
        self.__repo_evenimente = repo_evenimente

    def adaug_eveniment(self, id_eveniment, data, timp, descriere):
        """
        Creează și adaugă un eveniment nou în repository.
        Validează: id, data, timp și descriere.
        """

        eveniment = Eveniment(id_eveniment, data, timp, descriere)
        EvenimentValidator(eveniment).validate_id_eveniment()
        EvenimentValidator(eveniment).validate_data()
        EvenimentValidator(eveniment).validate_timp()
        EvenimentValidator(eveniment).validate_descriere()
        self.__repo_evenimente.adauga(eveniment)

    def modific_eveniment(self, id_eveniment, data, timp, descriere):
        """
        Modifică un eveniment existent după ID.
        Validează noile câmpuri (data, timp, descriere).
        """

        eveniment = Eveniment(id_eveniment, data, timp, descriere)
        EvenimentValidator(eveniment).validate_data()
        EvenimentValidator(eveniment).validate_timp()
        EvenimentValidator(eveniment).validate_descriere()
        self.__repo_evenimente.update(eveniment)

    def sterg_eveniment(self, id_eveniment):
        """
        Șterge un eveniment după ID.
        Ridică eroare dacă acesta nu există.
        """
        self.__repo_evenimente.delete(id_eveniment)

    def caut_eveniment(self, id_eveniment):
        """
        Caută și returnează evenimentul cu ID-ul dat.
        """
        return self.__repo_evenimente.find(id_eveniment)

    def afisez_eveniment(self):
        """
        Returnează lista tuturor evenimentelor stocate.
        """
        return self.__repo_evenimente.get_all()

    def __shake_sort(self, lista, key_func):
        """
        Implementarea algoritmului Shake Sort (Cocktail Shaker Sort)
        pe o listă de obiecte, folosind o funcție cheie (key_func).
        Sortează lista 'in-place'.
        """
        n = len(lista)
        schimbat = True
        start = 0
        end = n - 1

        while schimbat:
            schimbat = False

            for i in range(start, end):

                if key_func(lista[i]) > key_func(lista[i + 1]):
                    lista[i], lista[i + 1] = lista[i + 1], lista[i]
                    schimbat = True

            if not schimbat:
                break

            schimbat = False
            end = end - 1

            for i in range(end - 1, start - 1, -1):

                if key_func(lista[i]) > key_func(lista[i + 1]):
                    lista[i], lista[i + 1] = lista[i + 1], lista[i]
                    schimbat = True

            start = start + 1

    def sorteaza_evenimente_id(self):
        """
        Returnează lista de evenimente sortată crescător după ID
        folosind algoritmul Shake Sort.
        """

        evenimente_nesortate = self.__repo_evenimente.get_all()
        evenimente_sortate = evenimente_nesortate[:]

        key_func = Eveniment.get_id_eveniment

        self.__shake_sort(evenimente_sortate, key_func)

        return evenimente_sortate