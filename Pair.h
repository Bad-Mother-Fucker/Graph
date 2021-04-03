#ifndef GRAPH_PAIR_H
#define GRAPH_PAIR_H
#include <iostream>

/**
Definizione di una class Pair(T, T) che implementa una coppia di elementi di un arco del grafo
@brief Struct che rappresenta una coppia di elementi base
*/
template<typename T>
class Pair {

private:

    // DATI MEMBRO della coppia
    T _src; ///< dato elementare T del nodo sorgente
    T _dst;	///< dato elementare T del nodo destinazione

    void swap(Pair &other){
        std::swap(this -> _src, other._src);
        std::swap(this -> _dst, other._dst);
    }

public:

    /**
    COSTRUTTORE DI DEFAULT di una coppia
    */
    Pair() : _src(nullptr), _dst(nullptr) {
    }

    /**
    Costruttore di una coppia dati due elementi
    @param value1 dato elementare di tipo T che identifica il nodo sorgente
    @param value2 dato elementare di tipo T che identifica il nodo destinazione
    */
    Pair(const T& value1, const T& value2) : _src(value1), _dst(value2) {
    }

    /**
    DISTRUTTORE della coppia
    */
    ~Pair() {
    }

    /**
    COPY CONSTRUCTOR di una coppia
    @param other Pair da copiare
    */
    Pair(const Pair& other) : _src(other._src), _dst(other._dst) {
    }

    /**
    OPERATOR= di una coppia
    @param other Pair da cui effettuare la copia
    */
    Pair& operator=(const Pair &other) {

        if(this!=&other) {

            Pair tmp(other);
            tmp.swap(*this);
        }

        return *this;
    }

    /**
    GETTER DELLA SORGENTE
    @return reference all'elemento che identifica la sorgente
    */
    T& src() {
        return _src;
    }

    /**
    GETTER COSTANTE DELLA SORGENTE
    @return reference costante all'elemento che identifica la sorgente
    */
    const T& src() const {
        return _src;
    }

    /**
    GETTER DELLA DESTINAZIONE
    @return reference all'elemento che identifica la destinazione
    */
    T& dst(){
        return _dst;
    }

    /**
    GETTER COSTANTE DELLA DESTINAZIONE
    @return reference costante all'elemento che identifica la destinazione
    */
    const T& dst() const {
        return _dst;
    }


};



//fine class Pair

#endif