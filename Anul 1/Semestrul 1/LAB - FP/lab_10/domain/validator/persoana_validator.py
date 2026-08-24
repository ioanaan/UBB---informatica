from domain.validator.Validator_exception import ValidatorException

class PersoanaValidator:
    """
    Validator pentru obiectele de tip Persoana.
    Verifică validitatea datelor introduse.
    """

    def __init__(self, persoana):
        """
        Reține persoana care urmează să fie validată.
        """
        self.__persoana = persoana

    def validate_id_persoana(self):
        """
        Verifică dacă ID-ul persoanei este valid.
        Ridică eroare dacă ID-ul este nul sau negativ.
        """

        if self.__persoana.get_id_persoana() is None or self.__persoana.get_id_persoana() <= 0:
            raise ValidatorException("ID-ul nu este valid.")

    def validate_nume(self):
        """
        Verifică dacă numele nu conține cifre.
        Respinge numele introduse incorect.
        """

        for c in "1234567890":
            if c in self.__persoana.get_nume():
                raise ValidatorException("Numele nu este valid!")

    def validate_adresa(self):
        """
        Verifică dacă adresa nu conține cifre.
        Asigură introducerea unei adrese corecte.
        """

        for c in "1234567890":
            if c in self.__persoana.get_adresa():
                raise ValidatorException("Adresa nu este validă!")