% Allenamento sabato solo per gli adulti (orario mattutino)
allenamento(6, Orario, adulti) :- 
    orario_matt(Orario).

% Per ogni giorno (eccetto il sabato), ogni gruppo si allena esattamente una volta in uno degli orari pomeridiani definiti
1 {allenamento(Giorno, Orario, Gruppo) : gruppo(Gruppo)} :- 
    giorno(Giorno), 
    orario_pom(Orario), 
    Giorno != 6.

% Non possono esserci due gruppi diversi che si allenano nello stesso orario nello stesso giorno
:- allenamento(Giorno, Orario, Gruppo1), allenamento(Giorno, Orario, Gruppo2), Gruppo1 != Gruppo2.

% Non devono esserci turni intermedi vuoti
:- allenamento(Giorno, 20, _), not allenamento(Giorno, 18, _).

% Ogni gruppo deve partecipare ad almeno min_allenamenti
N {presente(Id, Giorno, Orario) : allenamento(Giorno, Orario, Gruppo)} :- atleta(Id, Gruppo, _, _), min_allenamenti(N, Gruppo).

% Stabilire se due giorni sono vicini
a_destra(Giorno, Giorno + 1) :- giorno(Giorno), giorno(Giorno + 1).
a_sinistra(Giorno + 1, Giorno) :- giorno(Giorno), giorno(Giorno + 1).
vicino(Giorno1, Giorno2) :- a_destra(Giorno1, Giorno2).
vicino(Giorno1, Giorno2) :- a_sinistra(Giorno1, Giorno2).

% I bambini non si allenano in giorni consecutivi
:- allenamento(Giorno1, _, bambini), allenamento(Giorno2, _, bambini), vicino(Giorno1, Giorno2).

% I bambini non si allenano più di una volta al giorno
:- allenamento(Giorno, Orario1, bambini), allenamento(Giorno, Orario2, bambini), Orario1 != Orario2.

% Solo gli adulti possono allenarsi al terzo turno (20:00)
:- allenamento(Giorno, 20, Gruppo), Gruppo != adulti.

% Non devono esserci turni intermedi vuoti
:- allenamento(Giorno, 20, _), not allenamento(Giorno, 18, _).

% Ogni giorno deve avere almeno due turni occupati
:- not 2 { allenamento(Giorno, Orario, _) : orario_pom(Orario) }.

% Gli atleti possono essere presenti solo agli allenamenti del loro gruppo e possono essere in massimo K per allenamento
2 { presente(Id, Giorno, Orario) : atleta(Id, Gruppo, _, _) } K 
:- allenamento(Giorno, Orario, Gruppo), max_partecipanti(K, Gruppo).

% Posto il sabato mattina
pieno_sabato :- 
    #count{Id : presente(Id, 6, Orario), orario_matt(Orario)} >= K, max_partecipanti(K, adulti).

% Spostamento degli adulti senza posto il sabato al venerdì
:- pieno_sabato, 
   presente(Id, 5, Orario), orario_pom(Orario), 
   not presente(Id, 6, Orario), orario_matt(Orario).

% Lo stesso atleta non può fare allenamenti consecutivi il sabato mattina
:- presente(Id, 6, Orario1), presente(Id, 6, Orario2), Orario1 != Orario2, orario_matt(Orario1), orario_matt(Orario2).

% Lo stesso atleta non può fare allenamenti consecutivi
:- presente(Id, Giorno, Orario1), presente(Id, Giorno, Orario2), Orario1 != Orario2, orario_pom(Orario1), orario_pom(Orario2).

%------------------------------------------- RANDORI PESO --------------------------------------------------------------

% All’interno di ogni gruppo, ogni settimana ciascuno deve poter fare randori (incontro di
%pratica) con tutti quelli della sua categoria di peso o del peso immediatamente inferiore

compatibile_peso_per_randori(Id1, Peso, Id2, Peso) :-
    atleta(Id1, Gruppo, _, Peso), 
    atleta(Id2, Gruppo, _, Peso),
    Id1 < Id2.

compatibile_peso_per_randori(Id1, Peso1, Id2, Peso2) :-
    atleta(Id1, Gruppo, _, Peso1),
    atleta(Id2, Gruppo, _, Peso1 + 1),
    Id1 != Id2,
    Peso2 = Peso1 + 1.
   

:- compatibile_peso_per_randori(Id1, Peso1, Id2, Peso2),
   #count { Giorno, Orario : presente(Id1, Giorno, Orario), presente(Id2, Giorno, Orario) } = 0.

randori_in_allenamento_peso(Id1, Peso1, Id2, Peso2, Giorno, Orario) :-
    compatibile_peso_per_randori(Id1, Peso1, Id2, Peso2),
    presente(Id1, Giorno, Orario),
    presente(Id2, Giorno, Orario),
    Id1 != Id2.

%-------------------------------------------- RANDORI PESO E CINTURA ---------------------------------------------------

%All’interno di ogni gruppo, ogni settimana ciascuno deve poter fare randori due giorni con
%tutti quelli della sua categoria di peso e della sua cintura o della cintura immediatamente
%inferiore

compatibile_cintura_per_randori(Id1, Cintura, Id2, Cintura) :- 
    atleta(Id1, Gruppo, Cintura, Peso),
    atleta(Id2, Gruppo, Cintura, Peso),
    Id1 < Id2.

compatibile_cintura_per_randori(Id1, Cintura1, Id2, Cintura2) :- 
    atleta(Id1, Gruppo, Cintura1, Peso),
    atleta(Id2, Gruppo, Cintura1 + 1, Peso),
    Id1 != Id2,
    Cintura2 = Cintura1 + 1.

:- compatibile_cintura_per_randori(Id1, Cintura1, Id2, Cintura2), 
    #count {Giorno, Orario : presente(Id1, Giorno, Orario), presente(Id2, Giorno, Orario)} < 2.

randori_in_allenamento_cintura(Id1, Cintura1, Peso1, Id2, Cintura2, Peso2, Giorno, Orario) :-
    compatibile_cintura_per_randori(Id1, Cintura1, Id2, Cintura2),
    presente(Id1, Giorno, Orario),
    presente(Id2, Giorno, Orario),
    atleta(Id1, _, _, Peso1),
    atleta(Id2, _, _, Peso2),
    Id1 != Id2.

%---------------------------------------------------------------------------------------------------------------------------------------

% Relazione tra allenamenti e presenze
allenamento_con_presenze(Giorno, Orario, Gruppo, Id) :- 
    allenamento(Giorno, Orario, Gruppo), presente(Id, Giorno, Orario).

%ATTIVARNE o COMMENTARE PER COMPRENDERE I DIVERSI FUNZIONAMENTI
#show allenamento_con_presenze/4.

#show randori_in_allenamento_peso/6.

#show randori_in_allenamento_cintura/8.

%#show num_allenamenti_comuni/7.
%#show presenze_per_allenamento/4.
%#show allenamento/3.
%#show presente/3.
%#show compatibile_peso_per_randori/4.
%#show compatibile_cintura_per_randori/4.
