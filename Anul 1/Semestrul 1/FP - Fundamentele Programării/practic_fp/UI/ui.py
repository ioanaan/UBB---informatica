
class Ui:

    def __init__(self, service_sedinte):

        self.__service_sedinte = service_sedinte

    def __meniu(self):
        print("--- MENIU ȘEDINȚE ---")
        print("1. Adaugă ședinta")
        print("2. Tabel sedinte")
        print("0. Iesire")

    def adaugare(self):
        """
        functia de adaugare.
        Cere sa sa introduca data, ora, subiectul si starea.
        """
        try:
            data = input("data (dd.mm): ")
            ora = input("ora (hh:mm): ")
            subiect = input("subiect: ")
            stare = input("stare (normala/extraordinara): ")
            self.__service_sedinte.adaugare(data, ora, subiect, stare)
            print("Ședinta adaugata cu succes!")

        except Exception as e:
            print(e)

    def show_sedinte_maine(self):
        """
        Functia ce returneaza sedintele din ziua urmatoare.
        """

        print("\nȘedintele de maine :")
        sedinte = self.__service_sedinte.get_sedinte_maine_ordonate()
        if not sedinte:
            print("Nu sunt sedinte programate.")
        else:
            for s in sedinte:
                print(f"{s.get_data()} {s.get_ora()} - {s.get_subiect()}")
        print("")

    def tabel_sedinte(self):
        """
        functia de tabel sedinte dupa data introdusa.
        """

        data = input("data (dd.mm): ")

        sedinte = self.__service_sedinte.get_tabel_sedinte_data(data)
        if not sedinte:
            print("nu sunt sedinte.")
        else:
            print(data)
            print("ORA" "  " "SUBIECT" "  " "STARE")
            for s in sedinte:
                print(f"{s.get_ora()} {s.get_subiect()} {s.get_stare()}")
            print("")

    def start(self):

        while True:

            self.show_sedinte_maine()
            self.__meniu()
            optiune = input("Alege optiunea: ").strip()

            if optiune == "1":
                self.adaugare()

            elif optiune == "2":
                self.tabel_sedinte()

            elif optiune == "0":
                break

            else:
                print("optiune inexistenta")