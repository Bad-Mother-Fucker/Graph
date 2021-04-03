//
// Created by Michele De Sena on 26/03/21.
//

#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H
#include <iostream>
#include "Pair.h"

/**
    Definizione di una class Edge(Pair, Edge*) che implementa un arco del grafo
    @brief Struct che rappresenta un arco del grafo
*/
template<class T>
class Edge {

private:

    /**
    Metodo utile allo swap dei dati membro di un arco
    @param other arco con cui scambiare i dati membro con this
    */
    void swap(Edge<T> &other){

        std::swap(this -> _pair, other._pair);
        std::swap(this -> _next, other._next);
    }

public:

    // DATI MEMBRO dell'arco
    Pair<T> _pair;		///< coppia di dati elementari T che rappresentano il nodo dell'arco
    Edge<T>* _next;	///< puntatore all'arco successivo

    /**
    COSTRUTTORE DI DEFAULT di un arco
    */
    Edge<T>(): _pair(nullptr), _next(nullptr){
    }

    /**
    Costruttore dell'arco dato un elemento
    @param value1 dato elementare di tipo T che identifica il nodo sorgente
    @param value2 dato elementare di tipo T che identifica il nodo destinazione
    */
    Edge(const T &value1, const T &value2) : _pair(value1, value2), _next(nullptr) {
    }

    /**
    DISTRUTTORE di un arco
    */
    ~Edge() {
    }

    /**
    COPY CONSTRUCTOR di un arco
    @param other arco da cui copiare this
    */
    Edge(const Edge &other) : _pair(other._pair), _next(other._next) {
    }

    /**
    OPERATOR= di un arco
    @param other arco di cui copio lo stato in this
    @return arco risultante dalla copia
    */
    Edge& operator=(const Edge &other) {

        if(this!=&other) {

            Edge tmp(other);
            tmp.swap(*this);

        }
        return *this;
    }

};



#endif //GRAPH_EDGE_H
