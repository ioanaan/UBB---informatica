from controller.service_pers import ServicePers
from controller.service_eve import ServiceEve
from controller.service_add import ServiceRegistration
from repo.persoana_file_repo import PersoanaFileRepo
from repo.eveniment_file_repo  import EvenimentFileRepo
from repo.registration_file_repo import RegistrationFileRepo
from ui.ui import UI

def main():
    """
    Inițializează repository-urile, serviciile și interfața utilizator.
    Pornește aplicația și gestionează execuția programului.
    """

    repo_persoana = PersoanaFileRepo("persoane.txt")
    repo_eveniment = EvenimentFileRepo("evenimente.txt")
    repo_registrations = RegistrationFileRepo("inscrieri.txt")
    service_pers = ServicePers(repo_persoana)
    service_eve = ServiceEve(repo_eveniment)
    serviceadd = ServiceRegistration(repo_persoana, repo_eveniment, repo_registrations)
    ui = UI(service_pers, service_eve, serviceadd)
    ui.start()

main()