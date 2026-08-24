from repo.repo_exception import RepoException

class EvenimentRepository:

    """
    Repository pentru gestionarea evenimentelor.
    Stochează evenimentele în memorie și oferă operații de bază: adaugare,
    căutare, actualizare, ștergere și listare.
    """


    def __init__(self):

        """
        Inițializează repository-ul cu o listă goală de evenimente.
        """

        self.__evenimente = []

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
                raise RepoException(f"Există deja eveniment la data {eveniment.get_data()} și la timpul {eveniment.get_timp()}!")

        self.__evenimente.append(eveniment)

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
                return

        raise RepoException(f"Evenimentul cu ID-ul {id_eveniment} nu există!")

    def find(self, id_eveniment):

        """
        Caută și returnează evenimentul cu ID-ul dat.
        Dacă nu există, ridică RepoException.
        """

        for local_eveniment in self.__evenimente:
            if local_eveniment.get_id_eveniment() == id_eveniment:
                return local_eveniment

        raise RepoException(f"Evenimentul cu ID-ul {id_eveniment} nu există!")