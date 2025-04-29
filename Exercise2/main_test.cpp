#include <gtest/gtest.h>				//include l'header file principale di Google Test

#include "test_sorting_algorithm.hpp"

int main(int argc, char *argv[])		//int argc		intero, è il num di argomenti  passati dalla riga di comando quando il programma viene eseguito
										//char *argv[]		array di puntatori di caratteri, contiene argomenti passati a riga di comando, il primo elm argv[0] è di solito il noem del programma
{
    ::testing::InitGoogleTest(&argc, argv);		//funzione di GT, la chiamo una volta sola a inizio programma, analizza argomenti di riga di comanfo e inizializza lìambiente GT
    return RUN_ALL_TESTS();						//GT esegue tutti i test case definiti nel progetto (quelli definiti in test_sorting_algorithm.hpp)
												//ritorna 0		se tutti i test hanno avuto successo
												//ritorna valroe diverso da 0		se uno o più test sono falliti
												//il valore viene restituito alla main
}
