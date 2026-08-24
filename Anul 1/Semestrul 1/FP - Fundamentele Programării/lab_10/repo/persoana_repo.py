from repo.repo_exception import RepoException

class PersoanaRepository:

    """
    Repository pentru gestionarea persoanelor.
    Stochează persoane în memorie și permite operații CRUD:
    adăugare, căutare, actualizare, ștergere și listare.
    """


    def __init__(self):

        """
        Inițializează repository-ul cu o listă goală de persoane.
        """

        self.__persoane = []

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
                return

        raise RepoException(f"Persoana cu ID-ul {id_persoana} nu există!")

    def find(self, id_persoana):

        """
        Caută și returnează persoana cu ID-ul dat.
        Dacă nu există, ridică RepoException.
        """

        for local_persoana in self.__persoane:
            if local_persoana.get_id_persoana() == id_persoana:
                return local_persoana
        raise RepoException(f"Persoana cu ID-ul {id_persoana} nu există!")