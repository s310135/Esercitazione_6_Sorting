#pragma once

#include <iostream>
#include <vector>
#include <algorithm>		//swap

using namespace std;

namespace SortLibrary 
{
	
template<typename T>						//generico tipo T
concept Sortable = requires(T& t) 			//un tipo T soddisfa il concetto Sortable se il codice dentro requires è valido
{											//requires dichiara una variabile t di tipo T passata per riferimento
    {t < t} -> convertible_to<bool>;	//requisito: T è Sortable se t < t e il risultato seve essere convertibile in bool, cioè assicura che T supporti l'operatore <
};

template<Sortable T>						//le funzioni accettano solo tipi T che soddisfano il concetto Sortable
vector<int> BubbleSort(std::vector<T>& v)			//riferimento mofificabile ad un elm di tipo T
													//v è il vettore che verrà ordinato
													//poichè ho passato per riferimento, le modifiche che apporto a v nella funzione si riflettono sul vettore originale passato per argomento
{
    const unsigned int n = v.size();			//è la dimensione del vettore
    for (unsigned int i = 0; i < n - 1; i++)		//uso n-1 perchè dopo n-1 iterazioni l'elemento più grande sarà sicuramente l'ultimo nel vettore e non dovrò più confrontarlo
    {
        for (unsigned int j = 0; j < n - i - 1; j++)		//i = numero elm che sono già stati spostati nella posizione corretta
															//n-i-1 è l'indice dell'ultimo elemento nella parte non ancora ordinata
        {
            if (v[j] > v[j + 1])				//confronto dell'elemento corrente con l'elemento successivo
            {
                std::swap(v[j], v[j + 1]);		//scambia posizione dei due elementi in v
            }
        }
    }
	return v;
}


template<Sortable T>
void heapify(std::vector<T>& v, int n, int i) 		//n è la dimensione dell'heapcheck
													//i è l'indice del nodo nell'heap da cui iniziare l'operazione
{
    int nodo_maggiore = i;					//è l'indice dell'elemento più grande tra il nodo corrente e i suoi figli
    int figlio_sinistro = 2 * i + 1;
    int figlio_destro = 2 * i + 2;

    if (figlio_sinistro < n && v[figlio_sinistro] > v[nodo_maggiore]) 	//la prima parte verifica se l'indice del figlio sinistro è minore della dimensione dell'heap
														//la seconda se il valore del figlio sinistro è maggiore del valore dell'elemento che attualmente è il maggiore
	{
        nodo_maggiore = figlio_sinistro;
    }

    if (figlio_destro < n && v[figlio_destro] > v[nodo_maggiore]) 
	{
        nodo_maggiore = figlio_destro;
    }

    if (nodo_maggiore != i) 			//se è diverso significa che uno dei due figli è maggiore del nodo corrente
	{
        std::swap(v[i], v[nodo_maggiore]);
        heapify(v, n, nodo_maggiore);		//verifica che anche il sottoalbero verifichi la proprietà dell'heap
    }
}

template<Sortable T>
vector<int> HeapSort(std::vector<T>& v) 
{
    int n = v.size();

    for (int i = n / 2 - 1; i >= 0; i--) 	//i è inizializzato all'indice dell'ultimo nodo non foglia nell'albero binario rappresentato dall'array, dove i nodi da n/2 a n-1 sono foglie in un heap di dimensione n
								//0 è la radice dell'heap
	{
        heapify(v, n, i);					//verifica che anche il sottoalbero verifichi la proprietà dell'heap
    }

    for (int i = n - 1; i > 0; i--) //inizializza l'indice all'indice dell'ultimo elemento del vettore
	{
        std::swap(v[0], v[i]);
        heapify(v, i, 0);
    }
	return v;
}

}
