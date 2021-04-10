//
// Created by Michele De Sena on 26/03/21.
//

#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H
#include <iostream>

using namespace std;

/**
    Definizione di una class Node(T, Node*) che implementa un nodo del grafo
    @brief Struct che rappresenta un nodo del grafo
*/
template<class T>
class Node {

private:

    /**
    Metodo utile allo swap dei dati membro di un nodo
    @param other nodo con cui scambiare i dati membro con this
    */
    void swap(Node &other){
        std::swap(this -> _data, other._data);

    }

public:

    // DATI MEMBRO del nodo
    T _data; 		///< dato elementare di tipo T

    /**
    COSTRUTTORE DI DEFAULT di un nodo
    */
    Node () : _data(0){
    }

    /**
    Costruttore del nodo dato un elemento
    @param other dato elementare di tipo T che identifica il nodo
    */
    explicit Node(const T &other) : _data(other){
    }

    /**
    DISTRUTTORE di un nodo
    */
    ~Node() {
    }

    /**
    COPY CONSTRUCTOR di un nodo
    @param other nodo da cui copiare this
    */
    Node(const Node &other) : _data(other._data){
    }

    /**
    OPERATOR= di un nodo
    @param other nodo di cui copio lo stato in this
    @return nodo risultato dalla copia
    */
    Node& operator=(const Node &other) {

        if(this!=&other) {

            Node tmp(other);
            tmp.swap(*this);
        }

        return *this;
    }



};


// end class Node



#endif //GRAPH_NODE_H
