import random
from domain.persoana import Persoana
from domain.validator.persoana_validator import PersoanaValidator

class ServicePers:
    """
    Service pentru gestionarea operațiilor legate de persoane.
    Coordonează validarea și interacțiunea cu repository-ul de persoane.
    """

    def __init__(self, repo_persoane):
        """
        Initializează service-ul cu repository-urile necesare.
        """

        self.__repo_persoane = repo_persoane

    def adaug_persoana(self, id_persoana, nume, adresa):
        """
        Creează și adaugă o persoană nouă în repository.
        Validează: ID-ul, numele și adresa.
        """

        persoana = Persoana(id_persoana, nume, adresa)
        PersoanaValidator(persoana).validate_id_persoana()
        PersoanaValidator(persoana).validate_nume()
        PersoanaValidator(persoana).validate_adresa()
        self.__repo_persoane.adauga(persoana)

    def modific_persoana(self, id_persoana, nume, adresa):
        """
        Modifică o persoană existentă după ID.
        Validează noile câmpuri (nume și adresa).
        """

        persoana = Persoana(id_persoana, nume, adresa)
        PersoanaValidator(persoana).validate_nume()
        PersoanaValidator(persoana).validate_adresa()
        self.__repo_persoane.update(persoana)

    def sterg_persoana(self, id_persoana):
        """
        Șterge o persoană după ID.
        Ridică eroare dacă aceasta nu există.
        """
        self.__repo_persoane.delete(id_persoana)

    def caut_persoana(self, id_persoana):
        """
        Caută și returnează persoana cu ID-ul dat.
        """
        return self.__repo_persoane.find(id_persoana)

    def afisez_persoana(self):
        """
        Returnează lista tuturor persoanelor stocate.
        """
        return self.__repo_persoane.get_all()

    def generez_persoana(self, numar):
        """
        Generează automat un număr dat de persoane aleatorii
        și le adaugă în repository.
        """

        opt_nume = ["Alina", "Marius", "Maria", "Daniela", "Cosmin", "Veronica", "Radu", "Ioana", "Denis", "Alexandra", "Camelia", "George", "Razvan"]
        opt_adresa = ["Cluj-Napoca", "Bucuresti", "Brasov", "Bacau", "Botosani", "Roman", "Constanta", "Iasi", "Timisoara", "Suceava", "Sighisoara", "Sibiu", "Adjud"]

        for i in range (numar):
            id_persoana = random.randint(1, 99999)
            nume = random.choice(opt_nume)
            adresa = random.choice(opt_adresa)
            self.adaug_persoana(id_persoana, nume, adresa)

    def __selection_sort(self, lista, key_func):
        """
        Implementarea algoritmului Selection Sort pe o listă de obiecte.
        Sortează lista 'in-place' pe baza funcției cheie specificate (key_func).
        """
        n = len(lista)
        for i in range(n):
            min_idx = i
            for j in range(i + 1, n):
                if key_func(lista[j]) < key_func(lista[min_idx]):
                    min_idx = j

            lista[i], lista[min_idx] = lista[min_idx], lista[i]

    def sorteaza_persoane_id(self):
        """
        Returnează lista de persoane sortată crescător după ID-ul persoanei
        folosind algoritmul Selection Sort.
        """

        persoane_nesortate = self.__repo_persoane.get_all()
        persoane_sortate = persoane_nesortate[:]

        key_func = Persoana.get_id_persoana

        self.__selection_sort(persoane_sortate, key_func)

        return persoane_sortate

