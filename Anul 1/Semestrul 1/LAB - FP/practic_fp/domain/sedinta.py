class Sedinta:

    def __init__(self, data, ora, subiect, stare):
        self.__data = data
        self.__ora = ora
        self.__subiect = subiect
        self.__stare = stare

    def get_data(self):
        return self.__data

    def get_ora(self):
        return self.__ora

    def get_subiect(self):
        return self.__subiect

    def get_stare(self):
        return self.__stare

    def set_data(self, data):
        self.__data = data

    def set_ora(self, ora):
        self.__ora = ora

    def set_subiect(self, subiect):
        self.__subiect = subiect

    def set_stare(self, stare):
        self.__stare = stare