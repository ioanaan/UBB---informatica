from repo.repo_exception import RepoException

class RegistrationRepository:

    """
    Repository pentru gestionarea înregistrărilor (registration).
    Stochează legăturile persoană-eveniment și permite
    adăugarea și listarea acestora.
    """

    def __init__(self):

        """
        Inițializează repository-ul cu o listă goală de înregistrări.
        """

        self.__lista_registrations = []

    def adauga(self, registration):

        """
        Adaugă o înregistrare în repository.
        Verifică dacă există deja o înregistrare cu același ID.
        Ridică RepoException în caz de duplicat.
        """

        for i in self.__lista_registrations:
            if i.get_id_registration() == registration.get_id_registration():
                raise RepoException("Registration cu acest ID deja există!")
        self.__lista_registrations.append(registration)

    def get_all(self):

        """
        Returnează toate înregistrările stocate.
        """

        return self.__lista_registrations

