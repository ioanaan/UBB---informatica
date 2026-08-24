from domain.validator.Validator_exception import ValidatorException

class RegistrationValidator:
    """
    Validator pentru obiectele de tip Registration.
    Asigură corectitudinea ID-urilor folosite la înscriere.
    """

    def __init__(self, registration):
        """
        Reține obiectul Registration care urmează să fie validat.
        """
        self.__registration = registration

    def validate_id_registration(self):
        """
        Verifică dacă ID-ul înscrierii este valid.
        Ridică eroare dacă acesta este nul sau negativ.
        """

        if self.__registration.get_id_registration() is None or self.__registration.get_id_registration() <= 0:
            raise ValidatorException("ID-ul este invalid.")

    def validate_id_persoana(self):
        """
        Verifică dacă ID-ul persoanei este valid.
        Respinge valorile nule sau negative.
        """

        if self.__registration.get_id_persoana() is None or self.__registration.get_id_persoana() <= 0:
            raise ValidatorException("ID-ul este invalid.")

    def validate_id_eveniment(self):
        """
        Verifică dacă ID-ul evenimentului este valid.
        Ridică eroare dacă formatul este incorect.
        """

        if self.__registration.get_id_eveniment() is None or self.__registration.get_id_eveniment() <= 0:
            raise ValidatorException("ID-ul este invalid.")