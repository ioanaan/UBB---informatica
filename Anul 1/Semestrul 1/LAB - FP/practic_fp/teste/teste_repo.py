from domain.sedinta import  Sedinta
from repository.repo_exception import RepoException
from repository.sedinta_filerepo import SedinteFileRepo


def test_adaugare():

    """

    :return:
    """

    f_test = "test_sedinte.txt"
    open(f_test, "w").close()

    repo = SedinteFileRepo(f_test)

    s1 = Sedinta("20.02", "08:00", "informatii", "normala")
    repo.adaugare(s1)

    assert len(repo.get_all()) == 1
    assert repo.get_all()[0].get_data() == "20.02"

    repo2 = SedinteFileRepo(f_test)
    assert len(repo2.get_all()) == 1

    try:
        repo2.adaugare(s1)
        assert False
        assert str(e)
    except RepoException:
        assert True

if __name__ == "__main__":
    try:
        test_adaugare()
        print("merge")
    except AssertionError as e:
        print("eroare")
    except Exception as e:
        print("nu ok")
