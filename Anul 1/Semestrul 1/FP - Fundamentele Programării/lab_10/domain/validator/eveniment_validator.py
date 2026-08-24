from domain.validator.Validator_exception import ValidatorException

class EvenimentValidator:
    """
    Validator pentru obiectele de tip Eveniment.
    Se ocupă de verificarea corectitudinii datelor introduse.
    """

    def __init__(self, eveniment):
        """
        Reține evenimentul care urmează să fie validat.
        """
        self.__eveniment = eveniment

    def validate_id_eveniment(self):
        """
        Verifică dacă ID-ul evenimentului este valid.
        Ridică eroare dacă ID-ul este nul sau negativ.
        """

        if self.__eveniment.get_id_eveniment() is None or self.__eveniment.get_id_eveniment() <= 0:
            raise ValidatorException("ID-ul nu este valid!")

    def validate_data(self):
        """
        Verifică dacă data introdusă conține doar caractere permise.
        Respinge date care conțin litere.
        """

        for c in "abcdefghijklmnopqrstuvwzyx":
            if c in self.__eveniment.get_data():
                raise ValidatorException("Data nu este validă!")

    def validate_timp(self):
        """
        Verifică dacă timpul introdus nu conține litere.
        Acceptă doar valori formate corect.
        """

        for c in "abcdefghijklmnopqrstuvwzyx":
            if c in self.__eveniment.get_timp():
                raise ValidatorException("Timpul nu este valid!")

    def validate_descriere(self):
        """
        Verifică dacă descrierea evenimentului este corectă.
        Respinge descrierile care conțin cifre.
        """

        for c in "1234567890":
            if c in self.__eveniment.get_descriere():
                raise ValidatorException("Descrierea nu este validă!")