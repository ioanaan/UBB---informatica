Laborator 1 MAP - expresii cu numere complexe

Ce face programul
Primeste din linia de comanda o expresie de forma n1 op n2 op ... op nk, unde numerele
sunt complexe (a+b*i) si op e unul din + - * /. Verifica daca expresia e scrisa bine
si daca da, afiseaza rezultatul.

Cum am impartit problema in clase
- ComplexNumber tine un numar complex (partea reala si partea imaginara).
- Operation e o interfata cu metoda apply(a, b). Am facut cate o clasa pentru fiecare
  operatie: Addition, Subtraction, Multiplication, Division. Fiecare face singura calculul.
- OperationFactory primeste simbolul ("+", "-" etc.) si da inapoi operatia potrivita.
  Am facut-o Singleton.
- ComplexNumberParser e o interfata pentru citirea unui numar din text. AlgebraicFormParser
  o implementeaza si citeste numere de forma 2+3*i, 5-6*i, -2+i.
- ExpressionParser e o interfata pentru citirea toata expresiei. CommandLineExpressionParser
  o implementeaza: verifica forma expresiei (checkStructure), citeste numerele
  (parseOperands), ia operatia de la fabrica si face un obiect Expression.
- Expression tine numerele si operatia si calculeaza rezultatul in evaluate().
- InvalidExpressionException e aruncata cand ceva e gresit (forma expresiei, un numar
  sau operatorul). Main o prinde si afiseaza mesajul.
- Main creeaza obiectele si le leaga intre ele.

Numerele le tin intr-un array simplu (ComplexNumber[], in diagrama apare ComplexNumber[*]),
fara colectii predefinite. In fabrica aleg operatia cu switch, nu cu Map.

Principiile SOLID

S (Single Responsibility) - fiecare clasa face un singur lucru. Citirea e in parsere,
calculul e in Expression si in clasele de operatii, afisarea e in Main. Parserele nu
afiseaza nimic, doar arunca exceptia.

O (Open/Closed) - daca vreau o operatie noua, fac o clasa noua care
implementeaza Operation si adaug un case in fabrica. Expression si parserele raman la fel.
La fel, daca vreau alt mod de scriere a numerelor, fac alta clasa care implementeaza
ComplexNumberParser.

L (Liskov) - oricare din cele 4 operatii poate fi folosita in locul interfetei Operation
si Expression merge la fel, pentru ca toate primesc doua numere si dau un numar.

I (Interface Segregation) - interfetele sunt mici, fiecare are o singura metoda.
Citirea unui numar si citirea expresiei sunt interfete separate.

D (Dependency Inversion) - Expression lucreaza cu interfata Operation, nu cu Addition
sau alta clasa concreta. CommandLineExpressionParser lucreaza cu interfata
ComplexNumberParser. Obiectele de care au nevoie le primesc prin constructor, iar
clasele concrete le alege doar Main.

Sabloane de proiectare

Strategy - Operation si cele 4 clase. Expression apeleaza operation.apply() si nu stie
ce operatie e de fapt, deci nu am nevoie de if-uri in Expression.

Factory - OperationFactory.create() transforma simbolul in obiectul de operatie. Asa
crearea operatiilor e intr-un singur loc.

Singleton - OperationFactory are constructor privat, un camp static instance si metoda
statica getInstance(), deci exista o singura fabrica in tot programul.

Cum se vad in diagrama
- Liniile punctate cu triunghi (implements) arata ce clase respecta fiecare interfata:
  cele 4 operatii spre Operation, AlgebraicFormParser spre ComplexNumberParser,
  CommandLineExpressionParser spre ExpressionParser.
- InvalidExpressionException extinde Exception (linie plina cu triunghi). E singura
  mostenire de clasa.
- Romburile (agregare) sunt acolo unde o clasa tine alt obiect intr-un camp primit prin
  constructor: Expression tine numerele (2..*) si operatia (1), iar
  CommandLineExpressionParser tine parserul de numere (1) si fabrica (1). Nu e compozitie
  pentru ca obiectele nu sunt create de clasa care le tine.
- Liniile punctate cu sageata (dependenta) sunt acolo unde o clasa doar foloseste alta pe
  moment: fabrica creeaza operatiile, parserul creeaza Expression, Main creeaza
  obiectele, iar parserele si fabrica arunca InvalidExpressionException.
- La OperationFactory se vede Singleton: stereotipul <<Singleton>>, instance si
  getInstance() subliniate (statice) si constructorul cu "-" (privat).
