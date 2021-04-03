//
// Created by Michele De Sena on 26/03/21.
//

#ifndef GRAPH_EXCEPTIONS_H
#define GRAPH_EXCEPTIONS_H
#include <iostream>

using namespace std;

/**
	Definizione di una classe key_not_found() che estende le eccezioni standard
	Sollevata nel caso in cui cerco un nodo/arco inesistente
	@brief Eccezione custom che rappresenta l'evento di ricerca di un nodo/arco inesistente
*/
class key_not_found : public std::runtime_error{

public:
    explicit key_not_found(const char *message) : std::runtime_error(message){}
};

/**
	Definizione di una classe duplicated_node() che estende le eccezioni standard
	Sollevata nel caso in cui cerco di aggiungere un nodo gia' esistente
	@brief Eccezione custom che rappresenta l'evento di inserimento di un arco già presente
*/
class duplicated_node : public std::runtime_error{

public:
    explicit duplicated_node(const char *message) : std::runtime_error(message){}
};

/**
	Definizione di una classe duplicated_edge() che estende le eccezioni standard
	Sollevata nel caso in cui cerco di aggiungere un arco gia' esistente
	@brief Eccezione custom che rappresenta l'evento di inserimento di un nodo già presente
*/
class duplicated_edge : public std::runtime_error{

public:
    explicit duplicated_edge(const char *message) : std::runtime_error(message){}
};

/**
	Definizione di una classe bad_iterator() che estende le eccezioni standard
	Sollevata nel caso in cui cerco di operare su un iteratore che punta alla coda della lista
	@brief Eccezione custom che rappresenta l'evento di operazione su iteratore "nullo"
*/
class bad_iterator : public std::runtime_error{

public:
    explicit bad_iterator(const char *message) : std::runtime_error(message){}
};


#endif //GRAPH_EXCEPTIONS_H
