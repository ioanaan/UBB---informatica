class Eveniment:
    """
    Entitate care reprezintă un eveniment.
    Stochează informații despre: ID, dată, timp și descriere.
    """

    """
    def __init__(self, id_eveniment, data, timp, descriere):
        self.__id_eveniment = id_eveniment
        self.__data = data
        self.__timp = timp 
        self.__descriere = descriere
    """

    def __init__(self, id_eveniment, data, timp, descriere):
        """
        Creează un obiect Eveniment folosind valorile primite.
        """

        self.__data = {
            "id_eveniment": id_eveniment,
            "data": data,
            "timp": timp,
            "descriere": descriere
        }

    def get_id_eveniment(self):
        """
        Returnează ID-ul evenimentului.
        """
        return self.__data['id_eveniment']

    def get_data(self):
        """
        Returnează data evenimentului.
        """
        return self.__data['data']

    def get_timp(self):
        """
        Returnează timpul evenimentului.
        """
        return self.__data['timp']

    def get_descriere(self):
        """
        Returnează descrierea evenimentului.
        """
        return self.__data['descriere']

    def set_data(self, data):
        """
        Actualizează data evenimentului.
        """
        self.__data['data'] = data
    
    def set_timp(self, timp):
        """
        Actualizează timpul evenimentului.
        """
        self.__data['timp'] = timp
    
    def set_descriere(self, descriere):
        """
        Actualizează descrierea evenimentului.
        """
        self.__data['descriere'] = descriere