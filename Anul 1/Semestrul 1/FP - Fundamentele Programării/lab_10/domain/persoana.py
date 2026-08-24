class Persoana:
    """
    Entitate care reprezintă o persoană.
    Conține informații despre ID, nume și adresă.
    """

    """
    def __init__(self, personID, nume, adresa):
        self.__personID = personID
        self.__nume = nume
        self.__adresa = adresa
    """
    def __init__(self, id_persoana, nume, adresa):
        """
        Creează un obiect Persoana cu datele furnizate.
        """

        self.__data = {
            "id_persoana" : id_persoana,
            "nume" : nume,
            "adresa" : adresa,
        }

    def get_id_persoana(self):
        """
        Returnează ID-ul persoanei.
        """
        return self.__data["id_persoana"]
    
    def get_nume(self):
        """
        Returnează numele persoanei.
        """
        return self.__data["nume"]
    
    def get_adresa(self):
        """
        Returnează adresa persoanei.
        """
        return self.__data["adresa"]

    def set_nume(self, nume):
        """
        Returnează numele persoanei.
        """
        self.__data["nume"] = nume

    def set_adresa(self, adresa):
        """
        Returnează adresa persoanei.
        """
        self.__data["adresa"] = adresa

    def __str__(self):
        """
        Returnează o reprezentare text a persoanei.
        """
        return f"Persoana(ID={self.__data['id_persoana']}, Nume='{self.__data['nume']}', Adresa='{self.__data['adresa']}')"