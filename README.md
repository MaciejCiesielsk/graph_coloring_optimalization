TODO:
 - gotowy szkielet projektu ktory dziala jako tako
 - metaheurystyka TABU
 - sortowanie numerkow w generatorze
 - naprawić kod tabu.cpp - na pewno nie jest optymalny
 - warunek stopu - max 3 min na instancje
 - zaliczenie 13 stycznia

  Tak jak greedy alhorithm, tylko ze bierzemy randomowe i & j i sprawdzamy czy w tej samej kolumnie sa sasiadami - jezeli tak to zabronione. Generujemy kolejna iteracje z randomowymi i jezeli jest wartosc =< to wpierdalamy do Tabu listy. Potem dostrajanie.
 Mozna sprawdzac sasiadow nie wszystkich. Np kilku tylko, bo potem mozemy ich dropnac.