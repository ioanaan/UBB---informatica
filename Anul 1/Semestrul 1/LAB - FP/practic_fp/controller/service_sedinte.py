from datetime import date, datetime, timedelta
from domain.sedinta import Sedinta

class SedinteService:
    def __init__(self, repo, vali):
        self.__repo = repo
        self.__vali = vali

    def adaugare(self, data, ora, subiect, stare):
        """
        adauga o sedinta dupa ce o valideaza
        :return:
        """
        sedinta = Sedinta(data, ora, subiect, stare)
        self.__vali.validate(sedinta)
        self.__repo.adaugare(sedinta)

    def get_sedinte_maine_ordonate(self):
        """
        ordoneaza sedintele supa criteriu
        :return: sedintele sortate dupa data
        """
        toate_sedintele = self.__repo.get_all()

        #data de maine
        maine_dt = date.today() + timedelta(days=1)
        data_maine_str = maine_dt.strftime("%d.%m")

        sedinte_maine = [s for s in toate_sedintele if s.get_data() == data_maine_str]

        sedinte_maine.sort(key=lambda x: x.get_ora())

        return sedinte_maine

    def get_tabel_sedinte_data(self, data):

        """
        face tabelul cu toate sedintele din data introdusa si respectiv peste 3 zile
        :param data:
        :return: sedintele respective
        """
        sedinte_all = self.__repo.get_all()

        sedinte_cu_data = [ s for s in sedinte_all if s.get_data() == data ]

        return sedinte_cu_data