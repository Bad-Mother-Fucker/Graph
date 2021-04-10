

#include <iostream>
#include "Graph.h"
#include "TestClass.h"



/**
METODO DI TEST
Data un grafo templato di interi, effettua delle chiamate alle funzioni pubbliche per testarle.
*/
void test_int(){

    std::cout << "---------------------TEST INT-------------------------" << std::endl;


    Graph<int> g;

    try{
        std::cout << "Aggiunta dei nodi 1,2,3,4,5,6..." << std::endl;
        g.add_node(1);
        g.add_node(2);
        g.add_node(3);
        g.add_node(4);
        g.add_node(5);
        g.add_node(6);
        std::cout << "Aggiunta di un ulteriore nodo 1..." << std::endl;
        g.add_node(1); // Genera eccezione
    }
    catch(duplicated_node &e){
        std::cout << e.what() << std::endl;
    }


    try{
        std::cout << "Aggiunta degli archi <1,2>,<1,3>,<3,4>..." << std::endl;
        g.add_edge(1,2);
        g.add_edge(2,4);
        g.add_edge(1,3);
        g.add_edge(3,4);
        g.add_edge(3,5);
        g.add_edge(5,5);
        g.add_edge(5,6);
        g.add_edge(4,6);
        std::cout << "Aggiunta di un ulteriore arco <1,2>..." << std::endl;
        g.add_edge(1,2); // Genera eccezione
    }
    catch(duplicated_edge &e){
        std::cout << e.what() << std::endl;
    }



    std::cout << "Test di esistenza di 5 e 90..." << std::endl;
    g.exists(5);
    g.exists(90);



    try{
        std::cout << "Test di esistenza di <1,2>,<1,3>,<3,4>..." << std::endl;
        g.has_edge(1,2);
        g.has_edge(1,3);
        g.has_edge(3,4);
        std::cout << "Test di esistenza di <0,90>..." << std::endl;
        g.has_edge(0,90); // Genera eccezione
    }
    catch(key_not_found &e){
        std::cout << e.what() << std::endl;
    }

     std::cout <<  "Test dell'operatore di stream, copy constructor e operatore=..." << std::endl;
     std::cout << "g: \n" << g << " " << std::endl;


    Graph<int> g2 = g;
    std::cout << "copia di g (o=): \n"<< g2 << " " << std::endl;

    Graph<int> g3(g);
    std::cout << "copia di g (cc) : \n" << g2 << " " << std::endl;


    try{
        std::cout << "Test rimozione di 5..." << std::endl;
        g.remove_node(5);
        std::cout << "Test esistenza di 5 e di <5,6>..." << std::endl;
        g.exists(5);
        g.has_edge(5,6); // Genera eccezione
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
        std::cout << "Test rimozione di <5,6> e di esistenza successiva..." << std::endl;
        g.remove_edge(5, 6);
        g.has_edge(5,6);
        std::cout << "Test rimozione di <90,70>..." << std::endl;
        g.remove_edge(90, 70); // Genera eccezione
    }
    catch(key_not_found &e){
        std::cout << e.what() << std::endl;
    }

    std::cout << "Test dei metodi per il ritorno di numero di nodi ed archi..." << std::endl;
    std::cout << "Il numero di nodi del grafo e' " << g.get_size_nodes() << "." << std::endl;
    std::cout << "Il numero di archi del grafo e' " << g.get_size_edges() << "." << std::endl;



}

/**
METODO DI TEST
Data un grafo templato di interi, effettua delle chiamate alle funzioni pubbliche per testarle.
*/
void test_custom(){

    std::cout << "---------------------TEST INT-------------------------" << std::endl;


    Graph<test> g;

    test a = test('a');
    test b = test('b');
    test c = test('c');
    test d = test('d');
    test e = test('e');
    test f = test('f');
    test h = test('h');


    try{
        std::cout << "Aggiunta dei nodi a,b,c,d..." << std::endl;
        g.add_node(a);
        g.add_node(b);
        g.add_node(c);
        g.add_node(d);
        g.add_node(e);
        g.add_node(f);
        std::cout << "Aggiunta di un ulteriore nodo a..." << std::endl;
        g.add_node(a); // Genera eccezione
    }
    catch(duplicated_node &e){
        std::cout << e.what() << std::endl;
    }

    try{
        std::cout << "Aggiunta degli archi <a,b>,<e,a>,<c,d>..." << std::endl;
        g.add_edge(a,b);
        g.add_edge(e,a);
        g.add_edge(c,d);
        std::cout << "Aggiunta di un ulteriore arco <e,a>..." << std::endl;
        g.add_edge(e,a); // Genera eccezione
    }
    catch(duplicated_edge &e){
        std::cout << e.what() << std::endl;
    }

    std::cout << "Test di esistenza di 5 e 90..." << std::endl;
    g.exists(a);
    g.exists(c);



    try{
        std::cout << "Test di esistenza di <a,b>,<e,a>,<c,d>..." << std::endl;
        g.has_edge(a,b);
        g.has_edge(e,a);
        g.has_edge(c,d);
        g.has_edge(b,e);
        std::cout << "Test di esistenza di <h,a>..." << std::endl;
        g.has_edge(h,a); // Genera eccezione
    }
    catch(key_not_found &e){
        std::cout << e.what() << std::endl;
    }

    std::cout <<  "Test dell'operatore di stream, copy constructor e operatore=..." << std::endl;
    std::cout << "g: \n" << g << " " << std::endl;


    Graph<test> g2 = g;
    std::cout << "copia di g (o=): \n"<< g2 << " " << std::endl;

    Graph<test> g3(g);
    std::cout << "copia di g (cc) : \n" << g2 << " " << std::endl;


    try{
        std::cout << "Test rimozione di a..." << std::endl;
        g.remove_node(a);
        std::cout << "Test esistenza di a e di <a,b>..." << std::endl;
        g.exists(a);
        g.has_edge(a,b); // Genera eccezione
    }
    catch(key_not_found &e){
        std::cout << e.what() << std::endl;
    }



    try{
        std::cout << "Test rimozione di h..." << std::endl;
        g.remove_node(h); // Genera eccezione
    }
    catch(key_not_found &e){
        std::cout << e.what() << std::endl;
    }


    try{
        std::cout << "Test rimozione di <c,d> e di esistenza successiva..." << std::endl;
        g.remove_edge(c, d);
        g.has_edge(c,d);
        std::cout << "Test rimozione di <90,70>..." << std::endl;
        g.remove_edge(h, f); // Genera eccezione
    }
    catch(key_not_found &e){
        std::cout << e.what() << std::endl;
    }

    std::cout << "Test dei metodi per il ritorno di numero di nodi ed archi..." << std::endl;
    std::cout << "Il numero di nodi del grafo e' " << g.get_size_nodes() << "." << std::endl;
    std::cout << "Il numero di archi del grafo e' " << g.get_size_edges() << "." << std::endl;



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
   //test_custom();

    std::cout << std::endl;



    std::cout << "Esecuzione terminata!" << std::endl;
    return 0;
}
