from controller.service_sedinte import SedinteService
from repository.sedinta_filerepo import SedinteFileRepo
from domain.validator import SedintaValidator
from UI.ui import Ui

def main():

    repo_sedinte = SedinteFileRepo("sedinte.txt")
    validator = SedintaValidator()
    service_sedinte = SedinteService(repo_sedinte, validator)
    ui = Ui(service_sedinte)
    ui.start()

main()