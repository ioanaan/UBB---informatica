from domain.registration import Registration
from domain.validator.registration_validator import RegistrationValidator
from repo.repo_exception import RepoException


class ServiceRegistration:
    """
    Service pentru gestionarea înregistrărilor persoanelor la evenimente.
    Coordonează interacțiunea dintre repo-urile de persoane, evenimente și înregistrări.
    """

    def __init__(self, repo_persoane, repo_evenimente, repo_registrations):
        """
        Initializează service-ul cu repository-urile necesare.

        :param repo_persoane: repository-ul care gestionează persoanele
        :param repo_evenimente: repository-ul care gestionează evenimentele
        :param repo_registrations: repository-ul care gestionează înregistrările persoană-eveniment
        """

        self.__repo_persoane = repo_persoane
        self.__repo_evenimente = repo_evenimente
        self.__repo_registrations = repo_registrations

    def inscrie_persoana(self, id_persoana, id_eveniment):
        """
            Inscrie o persoana la un eveniment.
            Verifica daca persoana si evenimentul exista, creeaza o inregistrare noua
            si o valideaza, apoi o adauga in repository-ul de inregistrari.
        """
        self.__repo_persoane.find(id_persoana)
        self.__repo_evenimente.find(id_eveniment)

        id_registration = len(self.__repo_registrations.get_all()) + 1
        registration = Registration(id_registration, id_persoana, id_eveniment)
        RegistrationValidator(registration).validate_id_registration()

        self.__repo_registrations.adauga(registration)

    def sortez_lista(self, id_persoana):
        """
        Returneaza lista de evenimente la care participa persoana cu id-ul dat.
        Evenimentele sunt sortate alfabetic dupa descriere, iar apoi dupa data.
        """

        lista_filtrata = []

        for r in self.__repo_registrations.get_all():
            if r.get_id_persoana() == id_persoana:
                lista_filtrata.append(r)

        lista_evenimente = []

        for r in lista_filtrata:
            id_eveniment = r.get_id_eveniment()
            eveniment = self.__repo_evenimente.find(id_eveniment)
            lista_evenimente.append(eveniment)

        lista_sortata = sorted(lista_evenimente, key=lambda r: (r.get_descriere(), r.get_data()))

        return lista_sortata

    def persoane_cu_cele_mai_multe_evenimente(self):
        """
        Determina persoanele care participa la cele mai multe evenimente.
        Returneaza o lista cu obiectele Persoana care au numarul maxim de inscrieri.
        """

        lista_finala = []
        dicti = {}
        for r in self.__repo_registrations.get_all():
            id_persoana = r.get_id_persoana()
            if id_persoana not in dicti:
                dicti[id_persoana] = 1
            else:
                dicti[id_persoana] += 1

        maxim = max(dicti.values())

        for p in dicti:
            if dicti[p] == maxim:
                lista_finala.append(self.__repo_persoane.find(p))

        return lista_finala

    def evenimente_cu_max_participanti(self):
        """
        Returneaza primele 20% evenimente cu cei mai multi participanti.
        Pentru fiecare eveniment se intoarce tuplul (eveniment, numar_participanti),
        ordonat descrescator dupa numarul de inscrieri.
        """

        lista_finala = []
        dicti = {}
        for r in self.__repo_registrations.get_all():
            id_eveniment = r.get_id_eveniment()
            if id_eveniment not in dicti:
                dicti[id_eveniment] = 1
            else:
                dicti[id_eveniment] += 1

        lista = list(dicti.items())
        lista.sort(key=lambda x: x[1], reverse=True)

        primele = int(len(lista) * 0.2)
        top = lista[:primele]

        for id_eveniment, nr in top:
            eveniment = self.__repo_evenimente.find(id_eveniment)
            lista_finala.append((eveniment, nr))

        return lista_finala

    def evenimente_cu_putini_participanti(self):
        """
        Returnează evenimentele cu cei mai puțini participanți.
        Ordine crescătoare după numărul de înscrieri, limitat la primele 5 rezultate.
        """

        lista_finala = []
        dicti = {}
        for r in self.__repo_registrations.get_all():
            id_eveniment = r.get_id_eveniment()
            if id_eveniment not in dicti:
                dicti[id_eveniment] = 1
            else:
                dicti[id_eveniment] += 1

        lista = list(dicti.items())
        lista.sort(key=lambda x: x[1])
        nr = min(5, len(lista))

        for i in range (nr):

            id_eveniment = lista[i][0]
            nr_participanti = lista[i][1]
            eveniment = self.__repo_evenimente.find(id_eveniment)
            lista_finala.append((eveniment, nr_participanti))

        return lista_finala

    def sortare_dupa_nume_si_descriere(self):

        inregistrari_tot = []

        for r in self.__repo_registrations.get_all():

            try:
                 eveniment = self.__repo_evenimente.find(r.get_id_eveniment())
                 persoana = self.__repo_persoane.find(r.get_id_persoana())
                 inregistrari_tot.append({"eveniment" : eveniment, "persoana" : persoana, "inregistrare" : r})

            except RepoException:
                continue

        inregistrati_sorted = sorted(inregistrari_tot, key=lambda x: (x["eveniment"].get_descriere().lower(), x["persoana"].get_nume().lower()))

        return inregistrati_sorted