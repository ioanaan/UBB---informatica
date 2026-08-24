from domain.registration import Registration
from repo.repo_exception import RepoException

class RegistrationFileRepo:

    def __init__(self, filename):

        self.__lista_registrations = []
        self.fName = filename
        self.__load_from_file()

    def __load_from_file(self):

        self.__lista_registrations = []

        try:
            with open(self.fName, "r") as f:
                linie = f.readline().strip()
                while linie != "":
                    valoare_atri = linie.split(";")
                    registration = Registration(int(valoare_atri[0]), int(valoare_atri[1]), int(valoare_atri[2]))
                    self.__lista_registrations.append(registration)
                    linie = f.readline().strip()

        except FileNotFoundError:
            open(self.fName, "w").close()

    def write_file(self):

        with open(self.fName, "w") as f:
            for registration in self.__lista_registrations:
                linie = f"{registration.get_id_registration()};{registration.get_id_persoana()};{registration.get_id_eveniment()}\n"
                f.write(linie)







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
        self.write_file()

    def get_all(self):

        """
        Returnează toate înregistrările stocate.
        """

        return self.__lista_registrations