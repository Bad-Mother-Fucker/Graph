/*
NOME........Riccardo
COGNOME.....Frigerio
MATRICOLA...781315
E-MAIL..... r.frigerio5@campus.unimib.it
*/

#include <iostream>
#include "Graph.h"

/**
METODO DI TEST
Data un grafo templato di interi, effettua delle chiamate alle funzioni pubbliche per testarle.
*/
void test_int(){

    std::cout << "---------------------TEST INT-------------------------" << std::endl;

    Graph<int> g;

    try{
        std::cout << "Aggiunta dei nodi 0,5,7,6..." << std::endl;
        g.add_node(0);
        g.add_node(5);
        g.add_node(7);
        g.add_node(6);
        std::cout << "Aggiunta di un ulteriore nodo 0..." << std::endl;
        g.add_node(0); // Genera eccezione
    }
    catch(duplicated_node &e){
        std::cout << e.what() << std::endl;
    }

    try{
        std::cout << "Aggiunta degli archi <5,7>,<0,0>,<0,6>..." << std::endl;
        g.add_edge(5,7);
        g.add_edge(0,0);
        g.add_edge(0,6);
        std::cout << "Aggiunta di un ulteriore arco <7,5>..." << std::endl;
        g.add_edge(7,5); // Genera eccezione
    }
    catch(duplicated_edge &e){
        std::cout << e.what() << std::endl;
    }

    std::cout << "Test di esistenza di 5 e 90..." << std::endl;
    g.exists(5);
    g.exists(90);



    try{
        std::cout << "Test di esistenza di <0,0>,<5,7>,<7,5>,<6,5>..." << std::endl;
        g.has_edge(0,0);
        g.has_edge(5,7);
        g.has_edge(7,5);
        g.has_edge(6,5);
        std::cout << "Test di esistenza di <0,90>..." << std::endl;
        g.has_edge(0,90); // Genera eccezione
    }
    catch(key_not_found &e){
        std::cout << e.what() << std::endl;
    }

    try{
        std::cout << "Test rimozione di 5..." << std::endl;
        g.remove_node(5);
        std::cout << "Test esistenza di 5 e di <5,7>..." << std::endl;
        g.exists(5);
        g.has_edge(5,7); // Genera eccezione

    }
    catch(key_not_found &e){
        std::cout << e.what() << std::endl;
    }

    try{
        std::cout << "Test rimozione di 90..." << std::endl;
        g.remove_node(90); // Genera eccezione
    }
    catch(key_not_found &e){
        std::cout << e.what() << std::endl;
    }


    try{
        std::cout << "Test rimozione di <0,6> e di esistenza successiva..." << std::endl;
        g.remove_edge(0, 6);
        g.has_edge(0,6);
        std::cout << "Test rimozione di <90,70>..." << std::endl;
        g.remove_edge(90, 70); // Genera eccezione
    }
    catch(key_not_found &e){
        std::cout << e.what() << std::endl;
    }

    std::cout << "Test dei metodi per il ritorno di numero di nodi ed archi..." << std::endl;
    std::cout << "Il numero di nodi del grafo e' " << g.get_size_nodes() << "." << std::endl;
    std::cout << "Il numero di archi del grafo e' " << g.get_size_edges() << "." << std::endl;

    std::cout <<  "Test dell'operatore di stream, copy constructor e operatore=..." << std::endl;
    // std::cout << "g: " << g << " " << std::endl;

    //g.print_matrix();

    Graph<int> g2 = g;
   // std::cout << "copia di g (o=): " << g2 << " " << std::endl;

    Graph<int> g3(g);
   // std::cout << "copia di g (cc) : " << g2 << " " << std::endl;
}



/**
ENTRY POINT
Crea un grafo templato e chiama le funzioni per testarlo
@param argc numero parametri passati da linea di comando
@param argv parametri passati da linea di comando
*/
int main(int argc, char* argv[]){

    /* Test sugli interi */
    test_int();
    std::cout << std::endl;



    std::cout << "Esecuzione terminata!" << std::endl;
    return 0;
}
