from menu.menu import *
from repo.repo_exception import RepoException
from domain.validator.Validator_exception import ValidatorException

class UI:
    """
    Interfața utilizator pentru gestionarea persoanelor, evenimentelor
    și înscrierilor. Coordonează interacțiunea cu utilizatorul și serviciile.
    """

    def __init__(self, servicep, servicev, serviceadd):
        """
        Inițializează clasa UI cu serviciile necesare aplicației.
        """

        self.__service_pers = servicep
        self.__service_eve = servicev
        self.__serviceadd = serviceadd

    def read_data_type(self, text, data_type):
        """
        Citește o valoare de la tastatură și o convertește la tipul cerut.
        Repetă citirea până când tipul este valid.
        """
        while True:

            data = input(text)

            try:
                data = data_type(data)
                return data

            except ValueError:
                print("Invalid type!")

    def adauga_Persoana(self):
        """
        Adaugă o nouă persoană citind datele de la utilizator.
        """

        id_persoana = self.read_data_type("ID persoană: ", int)
        nume = self.read_data_type("Nume persoană: ", str)
        adresa = self.read_data_type("Adresă persoană: ", str)
        self.__service_pers.adaug_persoana(id_persoana, nume, adresa)

    def modifica_Persoana(self):
        """
        Modifică o persoană existentă după ID, cu date noi.
        """

        id_persoana = self.read_data_type("ID persoană de modificat: ", int)
        nume = self.read_data_type("Noul nume: ", str)
        adresa = self.read_data_type("Noua adresă: ", str)
        self.__service_pers.modific_persoana(id_persoana, nume, adresa)

    def sterge_Persoana(self):
        """
        Șterge o persoană din sistem după ID.
        """

        id_persoana = self.read_data_type("ID persoană de șters: ", int)
        self.__service_pers.sterg_persoana(id_persoana)

    def cauta_Persoana(self):
        """
        Caută și afișează o persoană după ID.
        """

        id_persoana = self.read_data_type("ID persoană căutată: ", int)

        try:
            persoana = self.__service_pers.caut_persoana(id_persoana)
            print(f"ID: {persoana.get_id_persoana()}, Nume: {persoana.get_nume()}, Adresă: {persoana.get_adresa()}")
        except RepoException as e:
            print(e.get_message())

    def afiseaza_Persoana(self):
        """
        Afișează toate persoanele înregistrate.
        """

        persoane = self.__service_pers.afisez_persoana()
        for p in persoane:
            print(f"{p.get_id_persoana()}, {p.get_nume()}, {p.get_adresa()}")

    def genereaza_Persoana(self):
        """
        Generează un număr ales de persoane aleatorii.
        """

        numar = self.read_data_type("Câte persoane să se genereze: ", int)
        self.__service_pers.generez_persoana(numar)

        persoane = self.__service_pers.afisez_persoana()
        for p in persoane:
            print(p)

    def sorteaza_si_afiseaza_persoane(self):
        """
        Afișează lista de persoane sortată crescător după ID
        folosind Selection Sort.
        """
        print("--- Lista Persoanelor Sortate după ID ---")
        persoane_sortate = self.__service_pers.sorteaza_persoane_id()
        for p in persoane_sortate:
            print(f"ID: {p.get_id_persoana()}, Nume: {p.get_nume()}, Adresă: {p.get_adresa()}")


    def adauga_Eveniment(self):
        """
        Adaugă un eveniment nou, citind datele necesare de la utilizator.
        """

        id_eveniment = self.read_data_type("ID eveniment: ", int)
        data = self.read_data_type("Dată eveniment (de tip: DD.MM.YYYY): ", str)
        timp = self.read_data_type("Timp eveniment (ex: 13.00): ", str)
        descriere = self.read_data_type("Descriere eveniment: ", str)
        self.__service_eve.adaug_eveniment(id_eveniment, data, timp, descriere)

    def modifica_Eveniment(self):
        """
        Modifică un eveniment existent, actualizând datele acestuia.
        """

        id_eveniment = self.read_data_type("ID eveniment de modificat: ", int)
        data = self.read_data_type("Noua dată: ", str)
        timp = self.read_data_type("Noul timp: ", str)
        descriere = self.read_data_type("Noua descriere: ", str)
        self.__service_eve.modific_eveniment(id_eveniment, data, timp, descriere)

    def sterge_Eveniment(self):
        """
        Șterge un eveniment după ID.
        """

        id_eveniment = self.read_data_type("ID eveniment de șters: ", int)
        self.__service_eve.sterg_eveniment(id_eveniment)

    def cauta_Eveniment(self):
        """
        Caută și afișează un eveniment după ID.
        """

        id_eveniment = self.read_data_type("ID eveniment căutat: ", int)
        try:
            eveniment = self.__service_eve.caut_eveniment(id_eveniment)
            print(
                f"ID: {eveniment.get_id_eveniment()}, Dată: {eveniment.get_data()}, Timp: {eveniment.get_timp()}, Descriere: {eveniment.get_descriere()}")
        except RepoException as e:
            print(e.get_message())

    def afiseaza_Eveniment(self):
        """
        Afișează toate evenimentele existente.
        """

        eveniemente = self.__service_eve.afisez_eveniment()
        for e in eveniemente:
            print(f"{e.get_id_eveniment()}, {e.get_data()}, {e.get_timp()}, {e.get_descriere()}")

    def inscriere_Persoana(self):
        """
        Înscrie o persoană la un eveniment.
        """

        id_persoana = self.read_data_type("ID persoană de înregistrat: ", int)
        id_eveniment = self.read_data_type("ID eveniment la care se înregistrează: ", int)
        self.__serviceadd.inscrie_persoana(id_persoana, id_eveniment)

    def sortare_Lista(self):
        """
        Afișează evenimentele unei persoane sortate alfabetic după descriere
        și apoi după dată.
        """

        id_persoana = self.read_data_type("ID persoană pentru sortarea listei: ", int)
        for e in self.__serviceadd.sortez_lista(id_persoana):
            print(f"{e.get_descriere()}, {e.get_data()}, {e.get_timp()}")

    def persoane_cu_cele_mai_multe_evenimente(self):
        """
        Afișează persoanele care participă la cele mai multe evenimente.
        """

        for p in self.__serviceadd.persoane_cu_cele_mai_multe_evenimente():
            print(f"{p.get_id_persoana()}, {p.get_nume()}, {p.get_adresa()}")

    def evenimente_cu_maxim_participanti(self):
        """
        Afișeazăprimele 20% evenimente cu cei mai multi participanti.
        """

        for e, nr in self.__serviceadd.evenimente_cu_max_participanti():
            print(f"{e.get_id_eveniment()}, {e.get_data()}, {e.get_timp()}, {e.get_descriere()}, Participanți: {nr}")

    def evenimente_cu_putini_participanti(self):
        """
        Afișează top 5 evenimente unde participă cele mai puține persoane.
        """

        for e, nr in self.__serviceadd.evenimente_cu_putini_participanti():
            print(f"{e.get_id_eveniment()}, {e.get_data()}, {e.get_timp()}, {e.get_descriere()}, Participanți: {nr}")

    def sorteaza_si_afiseaza_evenimente_id(self):
        """
        Afișează lista de evenimente sortată crescator
        după ID folosind Shake Sort.
        """
        print("--- Lista Evenimentelor Sortate după ID (Shake Sort) ---")
        evenimente_sortate = self.__service_eve.sorteaza_evenimente_id()
        for e in evenimente_sortate:
            print(f"ID: {e.get_id_eveniment()}, Dată: {e.get_data()}, Timp: {e.get_timp()}, Descriere: {e.get_descriere()}")

    def sorteaza_registrations_nume(self):

        print("---Lista inregistrari sortate dupa nume---")
        inregistrari_sortate = self.__serviceadd.sortare_dupa_nume_si_descriere()

        for item in inregistrari_sortate:
            e = item["eveniment"]
            p = item["persoana"]

            print(f"[Eveniment ID: {e.get_id_eveniment()}] {e.get_descriere()}")
            print(f"Înscrisă: {p.get_nume()} (ID: {p.get_id_persoana()})\n")

    def start(self):
        """
        Afișează meniul principal și gestionează comenzile introduse de utilizator.
        """

        while True:

            meniu_principal()
            optiunea = self.read_data_type("Introdu optiunea: ", int)

            try:
                if optiunea == 1:
                    self.adauga_Persoana()

                elif optiunea == 2:
                    self.adauga_Eveniment()

                elif optiunea == 3:
                    self.modifica_Persoana()

                elif optiunea == 4:
                    self.modifica_Eveniment()

                elif optiunea == 5:
                    self.sterge_Persoana()

                elif optiunea == 6:
                    self.sterge_Eveniment()

                elif optiunea == 7:
                    self.cauta_Persoana()

                elif optiunea == 8:
                    self.cauta_Eveniment()

                elif optiunea == 9:
                    self.genereaza_Persoana()

                elif optiunea == 10:
                    self.afiseaza_Persoana()

                elif optiunea == 11:
                    self.afiseaza_Eveniment()

                elif optiunea == 12:
                    self.inscriere_Persoana()

                elif optiunea == 13:
                    self.sortare_Lista()

                elif optiunea == 14:
                    self.persoane_cu_cele_mai_multe_evenimente()

                elif optiunea == 15:
                    self.evenimente_cu_maxim_participanti()

                elif optiunea == 16:
                    self.evenimente_cu_putini_participanti()

                elif optiunea == 17:
                    self.sorteaza_si_afiseaza_persoane()

                elif optiunea == 18:
                    self.sorteaza_si_afiseaza_evenimente_id()

                elif optiunea == 19:
                    self.sorteaza_registrations_nume()

                elif optiunea == 0:
                    break

            except (RepoException, ValidatorException) as e:
                print("Execution error")
                print(e.get_message())