#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>

using namespace std;

// definizione di un atleta e le sue proprietà
struct athlete {
    string id;
    string group;
    string belt;
    int weight;

    // Operatore di confronto per std::set
    bool operator<(const athlete& other) const {
        return id < other.id;  // Ordina per ID atleta
    }
};

// definizione di un allenamento
struct training{
    int day;
    int time;
    set<athlete> participants;
};

// definizione di unp scontro randori
struct randori{
    set<pair<athlete, athlete>> participantsCouple;
    int day;
    int time;
};

// definizione delle tipologie di cinture
string getRandomBelt() {
    vector<string> belts = {
            "bianca",
            "gialla",
            "arancione",
            "verde",
            "blu",
            "marrone",
            "nera"
    };
    return belts[rand() % belts.size()];
}

// mappa per dare una classifica di interi alle cinture
map<string, int> beltRanking = {
        {"bianca", 1},
        {"gialla", 2},
        {"arancione", 3},
        {"verde", 4},
        {"blu", 5},
        {"marrone", 6},
        {"nera", 7}
};

// assegnazione random delle cinture
int getRandomWeight(const string& group) {
    if (group == "adulti") {
        return 50 + (rand() % 51); // 50-100kg
    } else if (group == "ragazzi") {
        return 40 + (rand() % 31); // 40-70kg
    } else if (group == "bambini") {
        return 10 + (rand() % 31); // 10-40kg
    }
    return 0;
}

// mappa per classificare i giorni in interi
map<string, int> dayMap = {
        {"lun", 1},
        {"mar", 2},
        {"mer", 3},
        {"gio", 4},
        {"ven", 5},
        {"sab", 6}
};

// genero i file csv contenenti i dettagli degli atleti prodotti casualmente
void generateCSV(int index, const vector<athlete>& dataset) {
    string directory = "combinazioniCSV/";
    string filename = directory + "dataset_" + to_string(index) + ".csv";
    ofstream file(filename);

    for (const auto& p : dataset) {
        file << "Id: " << p.id << ", Group: " << p.group << ", Belt: " << p.belt << ", Peso: " << p.weight << "\n";
    }

    file.close();
    cout << "File " << filename << " generato con successo!\n";
}

//genero i file .asp che avranno all'interno i fatti per modellare la soluzione
void generateASPInput(const int K, int index, const vector<string>& giorni, const vector<int>& orariPomeriggio, const vector<int>& orariMattina, const vector<string>& gruppi, const vector<athlete>& dataset, const int& n_allenamenti_adulti, const int& n_allenamenti_ragazzi, const int& n_allenamenti_bambini){
    string directory = "inputASP/";
    string filename = directory + "input_" + to_string(index) + ".asp";
    ofstream aspFile(filename);
    // Definisci il valore massimo per gruppo
    aspFile << "max_partecipanti(" << K << ", " << "adulti" << ").\n";

    aspFile << "max_partecipanti(" << (3*K)/2 << ", " << "ragazzi" << ").\n";

    aspFile << "max_partecipanti(" << 2*K << ", " << "bambini" << ").\n";

    aspFile << "min_allenamenti(" << n_allenamenti_adulti << ", " << "adulti" << ").\n";

    aspFile << "min_allenamenti(" << n_allenamenti_ragazzi << ", " << "ragazzi" << ").\n";

    aspFile << "min_allenamenti(" << n_allenamenti_bambini << ", " << "bambini" << ").\n";

    // Definisci i giorni
    for (const auto& giorno : giorni) {
        aspFile << "giorno(" << dayMap[giorno] << ").\n";
    }

    // Definisci i gruppi
    for (const auto& gruppo : gruppi) {
        aspFile << "gruppo(" << gruppo << ").\n";
    }

    // Definisci gli orari feriali
    for (const auto& orario : orariPomeriggio) {
        aspFile << "orario_pom(" << orario << ").\n";
    }

    // Definisci gli orari del sabato
    for (const auto& orario : orariMattina) {
        aspFile << "orario_matt(" << orario << ").\n";
    }

    // Aggiungi gli atleti come fatti
    for (const auto& atleta : dataset) {
        aspFile << "atleta("
                << atleta.id << ", "            // ID dell'atleta
                << atleta.group << ", "         // Gruppo
                << beltRanking[atleta.belt] << ", "          // Cintura
                << atleta.weight << ").\n";     // Peso
    }

    aspFile.close();
}

// faccio il parsing dei giorni di allenamento con la relativa lista di partecipanti a quell'allenamento e a ogni allenamento
// se ci sono scontri Randori di peso e/o cintura, vado a elencare gli atleti che potrebbero combattere in quell'allenamento
void parseTraning(const string& filename, vector<training>& vTraining, vector<randori>& vRandoriPeso, vector<randori>& vRandoriCintura) {
    ifstream inputFile(filename);
    string line;

    // Leggi ogni riga del file
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string token;

        // Per ogni allenamento nella riga
        while (iss >> token) {
            // Se è un allenamento valido
            if (token.find("allenamento_con_presenze") != string::npos) {
                size_t pos1 = token.find("(");
                size_t pos2 = token.find(")");
                if (pos1 != string::npos && pos2 != string::npos) {
                    string content = token.substr(pos1 + 1, pos2 - pos1 - 1);
                    stringstream ss(content);
                    string part;
                    vector<string> data;

                    while (getline(ss, part, ',')) {
                        data.push_back(part);
                    }

                    // Parsing dei dati (giorno, ora, gruppo, atleta)
                    if (data.size() == 4) {
                        int day = stoi(data[0]);
                        int time = stoi(data[1]);
                        string group = data[2];
                        string athleteId = data[3];

                        // Cerca allenamento esistente o crea uno nuovo
                        bool found = false;
                        for (auto& t : vTraining) {
                            if (t.day == day && t.time == time) {
                                // Aggiungi l'atleta all'allenamento
                                t.participants.insert(athlete{athleteId, group, "", 0});
                                found = true;
                                break;
                            }
                        }

                        // Se non trovato, crea un nuovo allenamento
                        if (!found) {
                            training newTraining;
                            newTraining.day = day;
                            newTraining.time = time;
                            newTraining.participants.insert(athlete{athleteId, group, "", 0});
                            vTraining.push_back(newTraining);
                        }
                    }
                }
            } else if (token.find("randori_in_allenamento_peso") != string::npos){
                size_t pos1 = token.find("(");
                size_t pos2 = token.find(")");
                if (pos1 != string::npos && pos2 != string::npos) {
                    string content = token.substr(pos1 + 1, pos2 - pos1 - 1);
                    stringstream ss(content);
                    string part;
                    vector<string> data;

                    while (getline(ss, part, ',')) {
                        data.push_back(part);
                    }

                    //Parsing dei dati (Id1, Peso1, Id2, Peso2, Giorno, Ora)
                    if (data.size() == 6){
                        string id1 = data[0];
                        int weight1 = stoi(data[1]);
                        string id2 = data[2];
                        int weight2 = stoi(data[3]);
                        int day = stoi(data[4]);
                        int time = stoi(data[5]);

                        bool found = false;
                        for (auto& r : vRandoriPeso) {
                            if (r.day == day && r.time == time) {
                                // Aggiungi randori all'allenamento
                                r.participantsCouple.insert({athlete{id1, "", "", weight1}, athlete{id2, "", "", weight2}});
                                found = true;
                                break;
                            }
                        }

                        if (!found) {
                            randori newRandori;
                            newRandori.day = day;
                            newRandori.time = time;
                            newRandori.participantsCouple.insert({athlete{id1, "", "", weight1}, athlete{id2, "", "", weight2}});
                            vRandoriPeso.push_back(newRandori);
                        }
                    }
                }

            } else if (token.find("randori_in_allenamento_cintura") != string::npos){
                size_t pos1 = token.find("(");
                size_t pos2 = token.find(")");
                if (pos1 != string::npos && pos2 != string::npos) {
                    string content = token.substr(pos1 + 1, pos2 - pos1 - 1);
                    stringstream ss(content);
                    string part;
                    vector<string> data;

                    while (getline(ss, part, ',')) {
                        data.push_back(part);
                    }

                    //Parsing dei dati (Id1, Cintura1, Peso1, Id2, Cintura2, Peso2, Giorno, Ora)
                    if (data.size() == 8){
                        string id1 = data[0];
                        int belt1 = stoi(data[1]);
                        int weight1 = stoi(data[2]);
                        string id2 = data[3];
                        int belt2 = stoi(data[4]);
                        int weight2 = stoi(data[5]);
                        int day = stoi(data[6]);
                        int time = stoi(data[7]);

                        std::map<int, std::string> beltRankingReversed;

                        // Invertiamo la mappa
                        for (const auto& entry : beltRanking) {
                            beltRankingReversed[entry.second] = entry.first;
                        }

                        string belt1_1 = beltRankingReversed[belt1];
                        string belt2_1 = beltRankingReversed[belt2];

                        bool found = false;
                        for (auto& r : vRandoriCintura) {
                            if (r.day == day && r.time == time) {
                                // Aggiungi randori all'allenamento
                                r.participantsCouple.insert({athlete{id1, "", belt1_1, weight1}, athlete{id2, "", belt2_1, weight2}});
                                found = true;
                                break;
                            }
                        }

                        if (!found) {
                            randori newRandori;
                            newRandori.day = day;
                            newRandori.time = time;
                            newRandori.participantsCouple.insert({athlete{id1, "", belt1_1, weight1}, athlete{id2, "", belt2_1, weight2}});
                            vRandoriCintura.push_back(newRandori);
                        }
                    }
                }
            }
        }
    }
}

// funzione per scrivere gli allenamenti ordinati nella directory outputOrdinato/ per semplificare la lettura delle soluzioni
void writeSortedOutput(const vector<training>& vTraining, const vector<randori>& vRandoriPeso, const vector<randori>& vRandoriCintura, const string& filename) {
    ofstream outputFile(filename);

    // Definizione dell'ordine dei giorni della settimana
    vector<string> giorni = {"LUNEDI", "MARTEDI", "MERCOLEDI", "GIOVEDI", "VENERDI", "SABATO"};

    // Ordina gli allenamenti per giorno, ora e gruppo
    map<int, map<int, map<string, set<string>>>> traningPerDay;  // Giorno -> Ora -> Gruppo -> Atleti
    map<int, map<int, map<string, randori>>> randoriPerDayWeight; //Giorno -> Ora -> Gruppo -> Coppia(Atleta1, Atleta2)
    map<int, map<int, map<string, randori>>> randoriPerDayBelt; //Giorno -> Ora -> Gruppo -> Coppia(Atleta1, Atleta2)

    // Organizza gli allenamenti nella mappa
    for (const auto& t : vTraining) {
        string group = t.participants.begin()->group;  // Si assume che tutti gli atleti in un allenamento siano dello stesso gruppo
        traningPerDay[t.day][t.time][group];  // Inizializza la mappa se non esiste

        // Aggiungi gli atleti all'allenamento
        for (const auto& atleta : t.participants) {
            traningPerDay[t.day][t.time][group].insert(atleta.id);
        }
    }

    for (const auto& r : vRandoriPeso) {
        string group = "";
        for (const auto& t : vTraining) {
            if (t.day == r.day && t.time == r.time) {
                if (!t.participants.empty()) {
                    group = t.participants.begin()->group;  // Prendi il gruppo del primo partecipante
                    break;
                }
            }
        }

        // Inizializza la mappa per il giorno e l'ora, se non esistono
        randoriPerDayWeight[r.day][r.time][group] = randori();

        // Itera su tutte le coppie di atleti
        for (const auto& couple : r.participantsCouple) {
            // Aggiungi entrambi gli atleti della coppia alla mappa
            randoriPerDayWeight[r.day][r.time][group].participantsCouple.insert(couple);
        }
    }

    for (const auto& r : vRandoriCintura) {
        string group = "";
        for (const auto& t : vTraining) {
            if (t.day == r.day && t.time == r.time) {
                if (!t.participants.empty()) {
                    group = t.participants.begin()->group;  // Prendi il gruppo del primo partecipante
                    break;
                }
            }
        }

        // Inizializza la mappa per il giorno e l'ora, se non esistono
        randoriPerDayBelt[r.day][r.time][group] = randori();

        // Itera su tutte le coppie di atleti
        for (const auto& couple : r.participantsCouple) {
            // Aggiungi entrambi gli atleti della coppia alla mappa
            randoriPerDayBelt[r.day][r.time][group].participantsCouple.insert(couple);
        }
    }


    // Scrivi nel file output
    for (int day = 1; day <= 6; ++day) {  // I giorni vanno da 1 (lunedì) a 6 (sabato)
        // Se esistono allenamenti per quel giorno
        if (traningPerDay.find(day) != traningPerDay.end()) {
            for (const auto& timeEntry : traningPerDay[day]) {
                int time = timeEntry.first;
                for (const auto& groupEntry : timeEntry.second) {
                    string group = groupEntry.first;
                    const set<string>& partecipants = groupEntry.second;

                    string groupUpper = group;
                    std::transform(groupUpper.begin(), groupUpper.end(), groupUpper.begin(), ::toupper);

                    // Scrivi il giorno e l'orario
                    outputFile << "------------------------";
                    outputFile << " giorno " << giorni[day - 1] << " alle " << time << " gruppo " << groupUpper;
                    outputFile << " ------------------------\n";

                    // Scrivi i partecipanti
                    bool first = true;
                    for (const auto& athleteId : partecipants) {
                        if (!first) {
                            outputFile << ", ";
                        }
                        outputFile << athleteId;
                        first = false;
                    }

                    if ((randoriPerDayWeight.find(day) != randoriPerDayWeight.end()) &&
                        (randoriPerDayWeight[day].find(time) != randoriPerDayWeight[day].end()) &&
                        (randoriPerDayWeight[day][time].find(group) != randoriPerDayWeight[day][time].end())){

                        // Accedi alle coppie di atleti del gruppo corrente per il giorno e ora
                        const set<pair<athlete, athlete>>& randoriCoppie = randoriPerDayWeight[day][time][group].participantsCouple;
                        outputFile << "\n******************";
                        outputFile << " Randori per PESO ";
                        outputFile << "******************\n";

                        // Scrivi le coppie di atleti
                        for (const auto& couple : randoriCoppie) {
                            outputFile << "|" << couple.first.id << " " << couple.first.weight << "Kg| VS |" << couple.second.id << " " << couple.second.weight << "Kg|\n";
                        }
                    }

                    if ((randoriPerDayBelt.find(day) != randoriPerDayBelt.end()) &&
                        (randoriPerDayBelt[day].find(time) != randoriPerDayBelt[day].end()) &&
                        (randoriPerDayBelt[day][time].find(group) != randoriPerDayBelt[day][time].end())){

                        // Accedi alle coppie di atleti del gruppo corrente per il giorno e ora
                        const set<pair<athlete, athlete>>& randoriCoppie = randoriPerDayBelt[day][time][group].participantsCouple;
                        outputFile << "\n******************";
                        outputFile << " Randori per PESO e CINTURA ";
                        outputFile << "********\n";

                        // Scrivi le coppie di atleti
                        for (const auto& couple : randoriCoppie) {
                            outputFile << "|" << couple.first.id << " " << couple.first.weight << "Kg " << couple.first.belt << "| VS |" << couple.second.id << " " << couple.second.weight << "Kg " << couple.second.belt << "|\n";
                        }
                    }

                    outputFile << "\n\n";  // Aggiungi una linea vuota tra gli allenamenti
                }
            }
        }
    }
}

int main() {

    // vettori per la creazione dei fatti in ASP
    vector<string> days = {"lun", "mar", "mer", "gio", "ven", "sab"};
    vector<int> afternoonHours = {16, 18, 20};
    vector<int> morningHours = {8, 10};
    vector<string> group = {"adulti", "ragazzi", "bambini"};

    srand(time(0));

    // IMPORTANTE: capienza Tatami
    int k = 15;

    // numero di allenamenti minimi per ogni atleta in base al corso di appartenenza
    int n_training_min_adults = 4;
    int n_training_min_teens = 3;
    int n_training_min_children = 2;

    //capienza tatami per diverse categorie
    int numSpaceTatamiA = k;
    int numSpaceTatamiT = (3 * k) / 2;
    int numSpaceTatamiC = 2 * k;

    //IMPORTANTE numero massimo di iscritti per ogni corso: per non avere un eccessivo sovraffollamento così ASP genererà sempre una soluzione
    int numMaxA = (7 * numSpaceTatamiA) / 4;
    int numMaxT = (5 * numSpaceTatamiT) / 3;
    int numMaxC = (3 * numSpaceTatamiC) / 2;

    // numero di iscritti casuale per ogni corso, >= capienza tatami e <= numero massimo di iscritti alla settimana
    int numAdults = numSpaceTatamiA + rand() % (numMaxA - numSpaceTatamiA + 1);
    int numTeens = numSpaceTatamiT + rand() % (numMaxT - numSpaceTatamiT + 1);
    int numChildren = numSpaceTatamiC + rand() % (numMaxC - numSpaceTatamiC + 1);

    // stampe di controllo per vedere la capienza settimanale
    cout << "Numero max ADULTI: " << numMaxA << ", Numero max RAGAZZI: " << numMaxT << ", Numero max BAMBINI: " << numMaxC << "\n";
    cout << "Numero Tatmi ADULTI: " << numSpaceTatamiA << ", Numero tatami RAGAZZI: " << numSpaceTatamiT << ", Numero tatami BAMBINI: " << numSpaceTatamiC << "\n";
    cout << "Numero atleti ADULTI: " << numAdults << ", Numero atleti RAGAZZI: " << numTeens << ", Numero atleti BAMBINI: " << numChildren << "\n";

    // cronometro per il tempo totale per analizzare 100 combinazioni diverse di istanze
    auto startTotale = chrono::high_resolution_clock::now();

    // genero le 100 istanze differenti di atleti per corso
    for (int combination = 0; combination < 100; ++combination) {
        // stampa di controllo
        cout << "\n************************************" << " DATASET " << combination + 1
             << " ************************************\n";

        // vettore con all'interno tutti gli atleti iscritti per la settimana
        vector<athlete> dataset;

        // Generazione atleti adulti
        for (int i = 0; i < numAdults; ++i) {
            dataset.push_back({"a" + to_string(i + 1), "adulti", getRandomBelt(), getRandomWeight("adulti")});
        }

        // Generazione atleti ragazzi
        for (int i = 0; i < numTeens; ++i) {
            dataset.push_back({"r" + to_string(i + 1), "ragazzi", getRandomBelt(), getRandomWeight("ragazzi")});
        }

        // Generazione atleti bambini
        for (int i = 0; i < numChildren; ++i) {
            dataset.push_back({"b" + to_string(i + 1), "bambini", getRandomBelt(), getRandomWeight("bambini")});
        }

        // scrivo le combinazioni di atleti nella directory combinazioniCSV/
        generateCSV(combination + 1, dataset);

        // ulteriore cronometro per vedere quanto impiega ASP per generare una soluzione a una sola combinazione
        auto start = chrono::high_resolution_clock::now();

        // genero nella directory inputASP/ tutti i 100 file asp che hanno all'interno i fatti necessari per modellare una soluzione
        generateASPInput(k, combination + 1, days, afternoonHours, morningHours, group, dataset,
                         n_training_min_adults,
                         n_training_min_teens, n_training_min_children);

        // parte il programma randori.asp in cui ho tutte le regole fondamentali per la soluzione e le stampo all'interno della directory outputASP/
        string outputFileName = "outputASP/output_" + to_string(combination + 1) + ".txt";
        string inputFileName = "inputASP/input_" + to_string(combination + 1) + ".asp";
        string command = "clingo --time-limit=300 -n 1 " + inputFileName + " ./randori.asp > " + outputFileName;
        system(command.c_str());

        // stop al cronometro e calcolo il tempo impiegato
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        //stampe di controllo
        cout << "Output salvato in " << outputFileName << std::endl;
        cout << "Tempo impiegato per generare " << outputFileName << ": " << elapsed.count() << " secondi"
             << endl;

        // vettori per il riordinamento dell'output ottenuto da ASP
        vector<training> vTraining;
        vector<randori> vRandoriPeso;
        vector<randori> vRandoriCintura;

        // all'interno della directory outputOrdinato/ ci saranno tutte le soluzioni dei 100 test in modo ordinato e pià facilmente leggibile
        string outputTidyFileName = "outputOrdinato/output_ordinato_" + to_string(combination + 1) + ".txt";

        // faccio il parsing della directory outputASP/ nella directory outputOrdinato/ per semplificare la lettura dei risultati
        parseTraning(outputFileName, vTraining, vRandoriPeso, vRandoriCintura);
        writeSortedOutput(vTraining, vRandoriPeso, vRandoriCintura, outputTidyFileName);
    }// fine for combinazioni

    // calcolo il tempo totale impiegato per le 100 combinaizoni
    auto endTotale = chrono::high_resolution_clock::now();
    chrono::duration<double> timeTotal = endTotale - startTotale;

    // stampa di controllo
    cout << "\n----------------------------------------------------------" << endl;
    cout << "Tempo totale di esecuzione: " << timeTotal.count() << endl;

    return 0;
} // fine main
