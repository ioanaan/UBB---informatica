class Registration:
    """
    Entitate care reprezintă o înscriere la un eveniment.
    Conține ID-ul înscrierii, ID-ul persoanei și ID-ul evenimentului.
    """

    def __init__(self, id_registration, id_persoana, id_eveniment):
        """
        Creează o nouă înregistrare între o persoană și un eveniment.
        """

        self.__data = {
            'id_registration': id_registration,
            'id_persoana': id_persoana,
            'id_eveniment': id_eveniment
        }

    def get_id_registration(self):
        """
        Returnează ID-ul înregistrării.
        """
        return self.__data['id_registration']

    def get_id_persoana(self):
        """
        Returnează ID-ul persoanei înscrise.
        """
        return self.__data['id_persoana']

    def get_id_eveniment(self):
        """
        Returnează ID-ul evenimentului la care este înscrisă persoana.
        """
        return self.__data['id_eveniment']