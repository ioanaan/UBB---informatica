Laborator 3 MAP - Retea de socializare (persistenta in fisier)

Ce face programul
Programul este reteaua de socializare din laboratorul 2: adaug si sterg utilizatori, adaug si
sterg prietenii, afisez numarul de comunitati si cea mai sociabila comunitate. Fata de
laboratorul 2, datele se pastreaza in fisiere text, iar tipul de persistenta (memorie, fisier
sau baza de date) se alege din fisierul de configurare, fara sa modific codul.

Fisierele de date
Datele sunt in folderul data/, cate o entitate pe linie, cu campurile separate prin ";":
- data/users.txt:       id;firstName;lastName;email
- data/friendships.txt: id1;id2;date   (data in format ISO, de exemplu 2026-10-19T10:30)
Am pastrat numele fisierelor in engleza, ca tot proiectul, si am pastrat emailul de la
laboratorul 2 (verific si ca un email sa nu fie folosit de doi utilizatori).
Prietenia (1, 2) si (2, 1) sunt aceeasi prietenie: id-ul ei este perechea cu id-ul mai mic
primul (metoda Friendship.createId), altfel findOne si delete nu ar gasi-o.
Fisierele se citesc si se scriu in UTF-8, cu BufferedReader peste FileReader si BufferedWriter
peste FileWriter, deschise in try-with-resources.

Cum functioneaza factory-ul
In resources/config.properties scrie tipul de persistenta si parametrii lui:
  repository.type=FILE            (MEMORY, FILE sau DATABASE)
  file.users, file.friendships    (caile fisierelor, relative)
  db.url, db.user, db.password    (pentru baza de date)
Main citeste fisierul cu java.util.Properties (in try-with-resources) si il da lui
RepositoryFactory. Factory-ul este singurul loc din program care stie clasele concrete de
repository. Metodele createUserRepository si createFriendshipRepository fac un switch pe tipul
citit si intorc InMemoryRepository, UserFileRepository/FriendshipFileRepository sau
UserDBRepository/FriendshipDBRepository, dar mereu ca tipul abstract Repository<ID, E>.
Ambele repository-uri se creeaza pentru acelasi tip, pentru ca citesc aceeasi cheie.
Daca lipseste o valoare din configurare sau tipul nu este cunoscut (de exemplu SQL), se arunca
ConfigurationException cu un mesaj clar si programul nu porneste.

Ce trebuie schimbat pentru baza de date (laboratorul 4)
UserDBRepository si FriendshipDBRepository exista deja, dar doar ca schelet: implementeaza
Repository, primesc prin constructor validatorul si datele de conectare, iar metodele arunca
UnsupportedOperationException. Factory-ul le creeaza deja pentru repository.type=DATABASE.
La laboratorul 4 trebuie doar sa scriu codul JDBC din metodele lor si sa pun
repository.type=DATABASE in config.properties. Service-urile, UI-ul si Main raman la fel,
pentru ca ele lucreaza doar cu interfata Repository.
Pana atunci, in modul DATABASE programul porneste, dar orice operatie afiseaza in UI mesajul
"Operation not available".

Simple Factory sau Abstract Factory
Am facut un Simple Factory cu switch. Avantajul este ca e simplu si tot ce tine de alegerea
repository-ului e intr-o singura clasa. Dezavantajul este ca nu respecta complet OCP: daca apare
un tip nou de persistenta (de exemplu XML), trebuie modificat switch-ul din factory.
Varianta Abstract Factory ar fi o interfata RepositoryFactory cu cate o implementare pentru
fiecare tip (FileRepositoryFactory, DbRepositoryFactory). Pentru un tip nou as adauga doar o
clasa noua, fara sa modific codul existent, deci respecta mai bine OCP. In schimb sunt mai multe
clase si tot trebuie ales undeva care implementare se foloseste. Pentru trei tipuri fixe am
ales varianta mai simpla.

Fisier lipsa si linii corupte
- Fisier lipsa: aplicatia porneste cu repository-ul gol si afiseaza un mesaj. Fisierul se
  creeaza la prima salvare (FileWriter creeaza fisierul, dar folderul data/ trebuie sa existe).
- Linie corupta sau invalida: linia este raportata (numarul liniei si motivul) si ignorata,
  iar restul fisierului se incarca normal. Am ales asa pentru ca o singura linie gresita nu ar
  trebui sa ma lase fara toate celelalte date. Sunt tratate: camp care nu e numar
  (NumberFormatException), data gresita (DateTimeParseException), numar gresit de campuri
  (verificat de mine, RepositoryException), date care nu trec de validator (ValidationException)
  si id duplicat (save intoarce entitatea).
  Prinderea se face in loadData, in jurul fiecarei linii, pentru ca doar acolo se poate trece
  la linia urmatoare. Nu este o exceptie ascunsa, pentru ca fiecare linie ignorata e afisata.
- Daca fisierul exista dar nu poate fi citit sau scris, IOException este impachetata in
  RepositoryException (exception chaining: exceptia originala ramane ca si cauza).
La incarcare folosesc super.save si nu save, pentru ca save din AbstractFileRepository ar
rescrie fisierul chiar in timp ce il citesc.
Pentru test am fisierele data/users_corrupt.txt si data/friendships_corrupt.txt, care contin
linii corupte; se folosesc schimband caile din config.properties.

Tratarea exceptiilor
Exceptiile proprii sunt unchecked (extind RuntimeException) si sunt in pachetul exceptions:
ValidationException, DuplicateEntityException, EntityNotFoundException, RepositoryException si
ConfigurationException. Validatorul, repository-ul si service-ul doar le arunca; ele se prind
in ConsoleUI, unde se afiseaza un mesaj, iar programul continua. Erorile de la pornire
(configurare gresita, fisier care nu poate fi citit) se prind in Main.
Am separat ConfigurationException de RepositoryException ca din mesaj sa se vada direct daca
trebuie reparat config.properties sau fisierele de date.

Unde este validarea
Validatorul verifica un singur obiect, fara sa stie de alte date: id pozitiv, nume cu litera
mare, email cu "@", prietenie cu doi utilizatori diferiti, data prieteniei. El este folosit de
repository la save si update, deci si datele citite din fisier trec prin validator.
Regulile care au nevoie de alte date sunt in service: daca utilizatorii exista cand adaug o
prietenie, daca emailul e deja folosit, stergerea prieteniilor cand sterg un utilizator.
Validatorul nu are acces la repository si nu trebuie sa aiba, altfel ar face doua lucruri.

Principiile SOLID
S (Single Responsibility) - fiecare clasa are o singura treaba: validatorii verifica,
repository-urile pastreaza datele, service-urile au regulile, ConsoleUI citeste si afiseaza,
factory-ul alege repository-ul, Main citeste configurarea si leaga totul.
O (Open/Closed) - pentru o entitate noua scriu un validator nou si un repository nou, fara sa
modific InMemoryRepository sau AbstractFileRepository. La factory OCP nu e respectat complet
(vezi mai sus).
L (Liskov) - InMemoryRepository, UserFileRepository si FriendshipFileRepository pot fi
folosite oriunde se cere un Repository, iar service-urile merg la fel; respecta contractul din
Javadoc-ul interfetei (de exemplu delete(null) arunca IllegalArgumentException). Scheletele DB
inca arunca UnsupportedOperationException, deci vor respecta contractul abia dupa
laboratorul 4.
D (Dependency Inversion) - service-urile, UI-ul si Main depind de interfata Repository, nu de
clasele concrete. Clasele concrete le creeaza doar factory-ul. Repository-urile primesc
validatorul prin constructor, ca interfata Validator. ConsoleUI implementeaza interfata UI.

Sabloane de proiectare
Factory - RepositoryFactory creeaza repository-ul potrivit dupa tipul din configurare.
Template Method - AbstractFileRepository scrie o singura data citirea si scrierea fisierului
(loadData, writeToFile); subclasele scriu doar cum devine o linie entitate si invers
(extractEntity, createEntityAsString).
Strategy - interfata Validator, cu UserValidator si FriendshipValidator. Repository-ul primeste
validatorul in constructor si apeleaza validate() fara sa stie ce validator e.
Decorator - BufferedReader "imbraca" un FileReader si ii adauga citirea pe linii si un buffer;
la fel BufferedWriter peste FileWriter. Amandoua sunt tot Reader/Writer, deci se pot folosi in
locul obiectului pe care il imbraca.

Observatie
Constructorul din AbstractFileRepository apeleaza loadData, care apeleaza extractEntity, o
metoda suprascrisa in subclase. La acel moment campurile subclasei nu sunt inca initializate.
La mine nu e o problema, pentru ca UserFileRepository si FriendshipFileRepository nu au campuri
proprii si extractEntity foloseste doar linia primita.
