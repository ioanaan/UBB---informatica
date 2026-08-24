from domain.validat_exception import ValidatorException
from datetime import datetime

class SedintaValidator:
    def validate(self, sedinta):
        """
        Valideaza starea, subiectul, data si ora.
        """
        erori = []

        try:
            datetime.strptime(sedinta.get_data(), "%d.%m")
        except ValueError:
            erori.append("Data invalida")

        try:
            datetime.strptime(sedinta.get_ora(), "%H:%M")
        except ValueError:
            erori.append("Ora invalida")

        stari_valide = ["normala", "extraordinara"]
        if sedinta.get_stare() not in stari_valide:
            erori.append("Stare invalida")

        if sedinta.get_subiect() == "":
            erori.append("Subiectul vid!")

        if len(erori) > 0:
            raise ValidatorException(", ".join(erori))