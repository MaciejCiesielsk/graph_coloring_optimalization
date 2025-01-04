TODO:
 - naprawić kod tabu.cpp - na pewno nie jest optymalny
 - zaliczenie 20 bądź 27 stycznia - da nam znac ziutek, ale raczej 27 o 11:45, przed standradowa sala

  Tak jak greedy alhorithm, tylko ze bierzemy randomowe i & j i sprawdzamy czy w tej samej kolumnie sa sasiadami - jezeli tak to zabronione. Generujemy kolejna iteracje z randomowymi i jezeli jest wartosc =< to wpierdalamy do Tabu listy. Potem dostrajanie.
 Mozna sprawdzac sasiadow nie wszystkich. Np kilku tylko, bo potem mozemy ich dropnac.



 najlepsze solucje:
 - gc500 - 70/1000 - sprawdzić czy dla mniejszych działa, dla 100/1000 dalo 82
 - queen6 - 9 daje idk lol - nie wazne jakie dane, idk idk man
 - gc1000 - 100/1000 daje 153, 100/2000 też niestety, 200/1000 dalo 146, ale po bardzo dlugim czasie, przy limicie 3 minut daje 152 dla 1000/2000
 - miles250 - 2/250 daje 8 czyli G, dla tego 1000/2000 sie wywala, daje jakies 6, dodac +2 lol


wyniki:
- queen6 - 9
- miles250 - daje 6 nw czemu, daje 8 dla malych warunkow np 2/250
- gc500 - 82
- gc1000 - 152
- le450_5a - 11


 SPRAWOZDANIE:
 Tabu Search GCC
 wykres slupkowy w procentach, punkt 2 z wykresów
 punkt 1 z algorytmow (ws z wykresow) - losowe generowanie naszym generatorem, rozne gestosci grafu
 pseudokod nie ma byc 1 do 1 jak kod, ma za duzo niezajmowac
 dodac do slupknowego wartosci bezwzgledne
 w tabelce z wynikami dac tylko swoje wyniki, bez optymalynch - nazwa pliku/twoj wynik

 moze byc troche wiekszy niz 7 wierzcholkow

 Opis dokladnie ma dotyczyc algorytmu

 if/for itd itp pogrubić w pseudokodzie

 25-1000, gestosci np 50, 70, 40% wykres z randomowymi, dac podzialke, 


 jakw yglada zaliczenie
 sprawko do niedzieli 23:59:59
 im wczesniej wyslesz tym lepiej
 sprawdzamy 2/3 instancje, max 3 minuty na kazda instancje
 wyniki w tabeli też zależnie od tego warunku 3min
 moze sie wynik czasem roznic
 być może będzie random instancja - rzadki chwyt, ale moze sie pojawic



 EWENTUALNIE MOZNA SIE POJAWIC 13stego stycznia, po godzinie danych zajec, czyli 9, 10:45,12:45, 14:30,
