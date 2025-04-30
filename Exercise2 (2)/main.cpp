#include <cmath> // contiene floor
#include <iostream>
#include <numeric> //per funzioni numeriche, contiene iota (per inizializzare un vettore con una sequenza)
#include <iostream>
#include <sstream>
#include <chrono> 	//misura il tempo di esecuzione
					//https://en.cppreference.com/w/cpp/chrono

#include "SortingAlgorithm.hpp"
using namespace std;

template<typename T>
string ArrayToString(const vector<T>& v)		//funzione accetta un riferimento costante a un vector di elm di tipo T
{
    string str;
    ostringstream toString;						//elm vengono inseriti in ostringstream che poi li formatta in una stringa
    toString << "[ ";
    for (const T& e: v)							//per ogni elm in vettore v viene creata una variabile e che è un riferimento costante all'elm corrente, elm non verrà modificato (const), & evita la copia dell'elemento migliorando l'efficienza
        toString << e << " ";
    toString << "]";

    return toString.str();
}

struct ClassObj				//definisce la struttura ClassObj che contiene un singolo membro (value)
{    
	double value;
};

inline bool operator< (const ClassObj& lhs, const ClassObj& rhs) { return lhs.value < rhs.value; }		//definisce una funzione globale che sovraccarica l'operatore < per gli oggetti di tipo ClassObj
		
		
		
int main(int argc, char *argv[])		//()	sono i parametri di main
										//argc 		sta per argument count, È un intero che contiene il numero di argomenti passati al programma dalla riga di comando quando viene eseguito. Il nome del programma stesso è sempre contato come il primo argomento.
										//*argv[]	sta per argument vector, È un array di puntatori a caratteri, Ogni elemento di questo array (argv[0], argv[1], ecc.) contiene uno degli argomenti passati dalla riga di comando. argv[0] di solito contiene il percorso o il nome del programma eseguito.
{
    cout << "argc: " << argc << endl;
    for(int a = 0; a < argc; a++)			//finchè a< argc(=numero totale di argomenti)
        cout << argv[a] << " ";
    cout << endl;

    size_t m = 10;				//dimensione predefinita per qualche contenitore
    if(argc > 1)				//se numerod i argomenti passati al programma è > 1. il nome del programma stesso è argv[0], quindi se argc è maggiore di 1, significa che l'utente ha fornito almeno un argomento aggiuntivo sulla riga di comando.
    {
        istringstream convert(argv[1]);		//tratta la stringa argv[1] come se fosse un flusso di input da cui è possibile leggere i dati
        convert >> m;						//estrae un valore intero da convert e lo inserisce in m
        cout << "use value: "  << m << endl;
    }
    else
        cerr << "use default value: "  << m << endl;

    vector<int> v1(m);						//vettore v1 di m elm, inizialmente inizializzati a 0
    std::iota(v1.begin(), v1.end(), -4); 	//iota riempe un intervallo di elm con valori sequenziali
											//v1.begin() 	restituisce iteratore che punta al primo elm di v1, è l'inizio dell'intervallo da riempire
											//v1.end()		restituisce iteratore che punta a posizione successiva di ultimo elm di v1, è la fine dell'intervallo da riempire
											//-4			è il valore di partenza della sequenza, il secondo elm è impostato a -3, il terzo a -2, ... fino a riempire tutti gli m elm del vettore
	

    srand(3);						//imposta il seme per il generatore di numeri pseudo-casuali utilizzato da rand()
	vector<int> v2(m);
    for(size_t i = 0; i < m; i++)			//i è l'indice dell'elm di v2 che sto per popolare
        v2[i] = rand();			

    vector<int> v3(m, 0);							//v3 è un vettore di m elm inizializzati a 0
    for(size_t i = floor(m * 0.5) + 2; i < m; i++)	//floor arrotonda il risultato all'intero inferiore
        v3[i] = rand() % 1000;						//il risultato è un numero compreso tra 0 e 999 inclusi

    copy(v1.begin(), v1.begin() + floor(m * 0.5) + 2, v3.begin());		//copia intervallo di elm da una sorgente a una destinazione


	cout << "v1: " << ArrayToString(v1) << endl;		//stampo i vettori passati ad ArrayToString
	cout << "v2: " << ArrayToString(v2) << endl;
	cout << "v3: " << ArrayToString(v3) << endl;

	//calcolo dei tempi:
    // https://www.epochconverter.com/			utilizzato per capire o convertire i timestamp Unix (il numero di secondi trascorsi dal 1 gennaio 1970)
    const auto today_time = std::chrono::system_clock::now();					//std::chrono::system_clock		rappresenta l'orologio di sistema in tempo reale
												//now()	 	è una funzione statica di std::chrono::system_clock che restituisce un oggetto di tipo std::chrono::time_point che rappresenta l'ora corrente
    std::cout << "Tempo trascorso dal 1 gennaio 1970: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(			//calcola la durata in millisecondi tra l'epoca (1 gennaio 1970) e l'ora corrente.
                     today_time.time_since_epoch()).count() << endl;			//today_time.time_since_epoch(): Restituisce un oggetto di tipo std::chrono::duration che rappresenta l'intervallo di tempo tra l'epoca del system_clock e il today_time.


    unsigned int numero_esperimenti = 100;			//numero di volte che ogni esperimento di ordinamento verrà eseguito per calcolare una media del tempo di esecuzione. Eseguire il test più volte e calcolare la media aiuta a ottenere risultati più stabili e meno influenzati da fluttuazioni temporanee del sistema.

    double tempomedio_bubble_v1 = 0.0;				// Questa variabile verrà utilizzata per accumulare il tempo totale impiegato dall'algoritmo per ordinare il vettore v1 in tutte le esecuzioni dell'esperimento. L'uso di double permette di memorizzare valori di tempo con una certa precisione.
    for(unsigned int t = 0; t < numero_esperimenti; t++)
    {
        vector<int> v(v1);		
        std::chrono::steady_clock::time_point tempo_inizio = std::chrono::steady_clock::now();		//registra il momento di inizio dell'esecuzione dell'algoritmo di ordinamento.
																									//std::chrono::steady_clock: Rappresenta un orologio monotono, il che significa che il suo valore aumenta a un ritmo costante e non viene influenzato da cambiamenti nell'ora di sistema. È ideale per misurare intervalli di tempo.
																									//now()			 Restituisce l'ora corrente come un punto nel tempo (std::chrono::time_point). Questo punto nel tempo viene memorizzato nella variabile tempo_inizio.
        SortLibrary::BubbleSort<int>(v1);
        std::chrono::steady_clock::time_point tempo_fine = std::chrono::steady_clock::now();			//registra il momento di fine dell'esecuzione, memorizzandolo nella variabile tempo_fine.
        tempomedio_bubble_v1 += std::chrono::duration_cast<std::chrono::microseconds>(tempo_fine - tempo_inizio).count();			//calcola il tempo impiegato per l'esecuzione dell'algoritmo di ordinamento in questa singola iterazione e lo aggiunge al tempo totale accumulato.
										//tempo_fine - tempo_inizio: Sottrae il punto di tempo iniziale dal punto di tempo finale, ottenendo un oggetto di tipo std::chrono::duration che rappresenta l'intervallo di tempo trascorso.
										//std::chrono::duration_cast<std::chrono::microseconds>(...): Converte la durata ottenuta al tipo std::chrono::microseconds. Questo specifica che vogliamo la durata espressa in microsecondi.
	}
    tempomedio_bubble_v1 /= numero_esperimenti;			//tempomedio_bubble_v1 /= numero_esperimenti;: Questa linea calcola il tempo di esecuzione medio dividendo il tempo totale accumulato per il numero di esperimenti. Il risultato è il tempo medio impiegato dall'algoritmo Bubble Sort per ordinare il vettore v1

    cout << "Bubble Sort - v1 (microseconds): " << tempomedio_bubble_v1 << endl;

    double tempomedio_bubble_v2 = 0.0;
    for(unsigned int t = 0; t < numero_esperimenti; t++)
    {
        vector<int> v(v2);

        std::chrono::steady_clock::time_point tempo_inizio = std::chrono::steady_clock::now();
        SortLibrary::BubbleSort<int>(v2);
        std::chrono::steady_clock::time_point tempo_fine = std::chrono::steady_clock::now();
        tempomedio_bubble_v2 += std::chrono::duration_cast<std::chrono::microseconds>(tempo_fine - tempo_inizio).count();
    }
    tempomedio_bubble_v2 /= numero_esperimenti;

    cout << "Bubble Sort - v2 (microseconds): " << tempomedio_bubble_v2 << endl;


    double tempomedio_bubble_v3 = 0.0;
    for(unsigned int t = 0; t < numero_esperimenti; t++)
    {
        vector<int> v(v3);

        std::chrono::steady_clock::time_point tempo_inizio = std::chrono::steady_clock::now();
        SortLibrary::BubbleSort<int>(v3);
        std::chrono::steady_clock::time_point tempo_fine = std::chrono::steady_clock::now();
        tempomedio_bubble_v3 += std::chrono::duration_cast<std::chrono::microseconds>(tempo_fine - tempo_inizio).count();
    }
    tempomedio_bubble_v3 /= numero_esperimenti;

    cout << "Bubble Sort - v3 (microseconds): " << tempomedio_bubble_v3 << endl;

    double timemedio_heap_v1 = 0.0;
    for(unsigned int t = 0; t < numero_esperimenti; t++)
    {
        vector<int> v(v1);

        std::chrono::steady_clock::time_point tempo_inizio = std::chrono::steady_clock::now();
        SortLibrary::HeapSort<int>(v1);
        std::chrono::steady_clock::time_point tempo_fine = std::chrono::steady_clock::now();
        timemedio_heap_v1 += std::chrono::duration_cast<std::chrono::microseconds>(tempo_fine - tempo_inizio).count();
    }
    timemedio_heap_v1 /= numero_esperimenti;

    cout << "Heap Sort - v1 (microseconds): " << timemedio_heap_v1 << endl;

    double timemedio_heap_v2 = 0.0;
    for(unsigned int t = 0; t < numero_esperimenti; t++)
    {
        vector<int> v(v2);

        std::chrono::steady_clock::time_point tempo_inizio = std::chrono::steady_clock::now();
        SortLibrary::HeapSort<int>(v2);
        std::chrono::steady_clock::time_point tempo_fine = std::chrono::steady_clock::now();
        timemedio_heap_v2 += std::chrono::duration_cast<std::chrono::microseconds>(tempo_fine - tempo_inizio).count();
    }
    timemedio_heap_v2 /= numero_esperimenti;

    cout << "Heap Sort - v2 (microseconds): " << timemedio_heap_v2 << endl;


    double timemedio_heap_v3 = 0.0;
    for(unsigned int t = 0; t < numero_esperimenti; t++)
    {
        vector<int> v(v3);

        std::chrono::steady_clock::time_point tempo_inizio = std::chrono::steady_clock::now();
        SortLibrary::HeapSort<int>(v3);
        std::chrono::steady_clock::time_point tempo_fine = std::chrono::steady_clock::now();
        timemedio_heap_v3 += std::chrono::duration_cast<std::chrono::microseconds>(tempo_fine - tempo_inizio).count();
    }
    timemedio_heap_v3 /= numero_esperimenti;

    cout << "Heap Sort - v3 (microseconds): " << timemedio_heap_v3 << endl;


    return 0;
}

