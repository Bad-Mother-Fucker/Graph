//
// Created by Michele De Sena on 26/03/21.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <stdexcept>	// contiene std::runtime_error
#include <algorithm>	// contiene std::swap
#include <new>			// contiene std::bad_alloc
#include <iterator>		// contiene std::forward_iterator_tag
#include <cstddef>		// contiene std::ptrdiff_t
#include <algorithm>
#include <iostream>
#include "Node.h"
#include "Exceptions.h"

template <class T>

class Graph {

private:
    typedef unsigned int size_type; ///< Tipo che definisce il numero dei nodi e degli archi

    // DATI MEMBRO DEL GRAFO
    Node<T>* _headN; ///< testa della lista dei nodi
    bool** matrix; ///< Matrice di adiacenza del grafo
    size_type num_nodes; ///< numero di nodi
    size_type num_edges; ///< numero di archi

    /**
    METODO AUSILIARIO
    Dato un elemento, ritorna il relativo puntatore al nodo se esistente, altrimenti nullptr.
    @param value dato elementare T di cui cerco il nodo
    @return puntatore al relativo nodo, se esistente
    */
    Node<T>* find_N_helper(const T &value) const{

        Node<T> *tmp = _headN;

        while(tmp!=0) {

            if(tmp -> _data == value)
                return tmp;

            tmp = tmp -> _next;
        }

        return nullptr;
    }

    /**
    METODO AUSILIARIO
    Dato due elementi, ritorna il relativo puntatore all'arco se esistente, altrimenti nullptr.
    @param value1 dato elementare T del nodo sorgente dell'arco che cerco
    @param value2 dato elementare T del nodo sorgente dell'arco che cerco
    @return puntatore al relativo arco, se esistente
    */
    int find_E_helper(const T &value1, const T &value2) const {
        return matrix[getNodeIndex(value1)][getNodeIndex(value2)];
    }

    /**
    METODO AUSILIARIO
    Dato un elemento, effettua un controllo sull'eventuale nodo relativo.
    @param value dato elementare T del nodo che cerco
    @return true se il puntatore cercato è nullo, false altrimenti
    */
    bool check_N(const T &value) const{
        return find_N_helper(value)==nullptr;
    }

    /**
    METODO AUSILIARIO
    Dati due elementi, effettua dei controlli sull'eventuale arco relativo.
    @param value1 dato elementare T del nodo sorgente dell'arco che cerco
    @param value2 dato elementare T del nodo destinazione dell'arco che cerco
    @return 1 se i due valori sono entrambi nodi e l'arco esiste; 0 se i due valori sono entrambi nodi e l'arco non esiste; -1 se almeno uno dei due valori non corrisponde a nessun nodo
    */
    int check_E(const T &value1, const T &value2) const{

        if(!check_N(value1)&&!check_N(value2)){
            return find_E_helper(value1,value2);
        }
        else
            return -1;
    }

    /**
    METODO AUSILIARIO
    Pulisce la memoria allocata da nodi e archi.
    */
    void clear() {

        // Cancello i nodi
        Node<T> *tmpN = _headN;
        Node<T> *tmpN2 = nullptr; ///TODO: CORREGGI

        while(tmpN!=nullptr) {

            tmpN2 = tmpN -> _next;
            delete tmpN;
            tmpN = tmpN2;
        }

        // Cancella la matrice
        for(int i=0;i<num_nodes;i++)
            delete [] matrix[i];

        delete [] matrix;

    }


    /**
    METODO AUSILIARIO
    Rimuove fisicamente l'arco, una volta che sono sicuro sia esistente.
    @param value1 dato elementare T del nodo sorgente dell'arco
    @param value2 dato elementare T del nodo destinazione dell'arco
    */
    void safe_remove_edge(const T &value1, const T &value2){

        matrix[getNodeIndex(value1)][getNodeIndex(value2)] = false;

    }

    /**
    METODO AUSILIARIO
    Ridimensiona la matrice di adiacenze.
    @param new_num_nodes la nuova dimensione

    */
    void reallocMatrix(size_type new_num_nodes) {

        if (matrix == nullptr) {
            matrix = new bool* [new_num_nodes];
            for(int i=0;i<new_num_nodes;i++)
                matrix[i] = new bool[new_num_nodes];
        } else {

            bool **newMatrix = new bool* [new_num_nodes]();

            for(int i=0;i<new_num_nodes;i++)
                newMatrix[i] = new bool[new_num_nodes]();

           int num = std::min(num_nodes,new_num_nodes);

           //Copio la vecchia matrice nella nuova

           for(int i = 0; i< num; i++) {
               for(int j = 0; j< num; j++) {
                   newMatrix[i][j] = matrix[i][j];
               }
           }

            //Elimino la matrice inutilizzata prima di riassegnarla al nuovo puntatore

            for(int i = 0; i<num; i++){
                delete[] matrix [i];

            }

            delete [] matrix;


            matrix = newMatrix;

        }

        if(new_num_nodes > num_nodes) matrix[new_num_nodes-1][new_num_nodes-1] = false;


    }

    /**
   METODO AUSILIARIO
   Restituisce l'indice della riga della matrice indicante il nodo
   @param T valore del nodo da cercare
   @returns l'indice della matrice indicante il nodo in questione
   */
   int getNodeIndex(const T &val) const {
        int index=0;

        Node<T> *tmp = _headN;

        while(tmp!=0){

            if(tmp -> _data == val)
                return index;
            index++;

            tmp = tmp -> _next;
        }

        return -1;
   }

    /**
    METODO AUSILIARIO
    Rimuove i dati sulle adiacenze di un nodo dalla matrice.
    @param node: posizione del nodo da rimuovere
    */

    void update_matrix(const int &node) {

        for(int i = 0; i <num_nodes; i++){
            for (int j = node; j<num_nodes; j++){
                matrix[i][j] = matrix[i][j+1];
            }
        }

        for (int i = node; i < num_nodes; i++) {
            matrix[i] = matrix[i+1];
        }

        reallocMatrix(num_nodes-1);
        num_nodes--;

    }

    /**
    Metodo utile allo swap dei dati membro di un grafo
    @param other grafo con cui scambiare i dati membro con this
    */
    void swap(Graph &other){

        std::swap(this ->_headN, other._headN);
        std::swap(this ->_headN, other._headE);
        std::swap(this -> num_nodes, other.num_nodes);
        std::swap(this -> num_edges, other.num_edges);
    }

public:



    friend ostream& operator<<(ostream& os, Graph<T>g ) {
        return g.print_matrix(os);
    }

    /**
    COSTRUTTORE DI DEFAULT di un grafo
    */
    Graph(): _headN(nullptr), num_nodes(0), num_edges(0), matrix(nullptr){
    }



    /**
    DISTRUTTORE di un grafo
    */
    ~Graph() {
        clear();
    }

    /**
    COPY CONSTRUCTOR di un grafo
    @param other grafo da cui copiare this
    @throw ... nel caso in cui qualche new fallisca
    */
    Graph(const Graph &other):_headN(nullptr), matrix(nullptr), num_nodes(0), num_edges(0){

        Node<T> *tmpN = other._headN;

        try
        {
            while(tmpN!=0)
            {
                add_node(tmpN -> _data);
                tmpN = tmpN -> _next;
            }

            for(int i = 0; i< num_nodes; i++){
                for(int j = 0; j<num_nodes; j++) {
                    this -> matrix[i][j] = other.matrix[i][j];
                }
            }

        }
        catch(...)
        {
            clear(); // Riporto l'oggetto in uno stato coerente
            throw;
        }
    }

    /**
    OPERATOR= di un grafo
    @param other grafo di cui copio lo stato in this
    @return grafo risultante dalla copia
    */
    Graph& operator=(const Graph &other) {

        if(this!=&other) {
            Graph temp(other);
            temp.swap(*this);
        }

        return *this;
    }

    /**
    METODO PUBBLICO
    Getter del numero dei nodi di this
    @return numero dei nodi del grafo
    */
    size_type get_size_nodes() const{
        return this -> num_nodes;
    }

    /**
    METODO PUBBLICO
    Getter del numero degli archi di this
    @return numero degli archi del grafo
    */
    size_type get_size_edges() const{
        return this -> num_edges;
    }

    /**
    METODO PUBBLICO RICHIESTO DA PROGETTO
    Aggiunge un nodo, dato il relativo valore, se non ancora esistente
    @param value dato elementare T da cui aggiungere il nodo
    @throw duplicated_node nel caso in cui si cerchi di aggiungere un nodo già esistente
    @throw std::bad_alloc nel caso in cui l'allocazione di memoria non vada a buon fine
    */
    void add_node(const T &value){

        if(check_N(value)){ /// Controllo se il nodo è già presente

            try{

                if(_headN==nullptr) {
                    _headN = new Node<T>(value); /// Lo aggiungo all'insieme dei nodi
                    reallocMatrix(num_nodes+1);
                }else{

                    Node<T> *tmp = _headN;
                    _headN = new Node<T>(value);
                    _headN -> _next = tmp;
                    reallocMatrix(num_nodes+1);
                }

                num_nodes++;
            }
            catch(std::bad_alloc &e){
                std::cout << e.what() << std::endl;
                throw;
            }
        }
        else throw duplicated_node("EXCEPTION: Impossibile aggiungere un nodo gia' esistente!");
    }

    /**
    METODO PUBBLICO RICHIESTO DA PROGETTO
    Rimuove un nodo, dato il relativo valore, se esistente
    @param value dato elementare T da cui rimuovere il nodo
    @throw key_not_found nel caso si cerchi di rimuovere un nodo inesistente
    */
    void remove_node(const T &value){
        if(!check_N(value)){

            int id=0;
            ///Rimuovo dall'insieme dei nodi
            Node<T>* tmp = _headN;
            if(tmp -> _data == value){
                _headN = tmp -> _next;
                delete tmp;
            }
            else{
                while(tmp -> _next -> _data != value){
                    Node<T>* tmp2 = tmp -> _next;
                    tmp = tmp2;
                    id++;
                }
                Node<T>* tmp2 = tmp -> _next;
                std::swap(tmp -> _next, tmp2 -> _next);
                delete tmp2;
            }
            update_matrix(id);
        }
        else throw key_not_found("EXCEPTION: Impossibile rimuovere un nodo inesistente!");
    }

    /** METODO PUBBLICO RICHIESTO DA PROGETTO
    Aggiunge un arco, dati i relativi valori, se non ancora esistente e i valori sono nodi esistenti
    @param value1 dato elementare T che identifica il nodo sorgente da cui aggiungere l'arco
    @param value2 dato elementare T che identifica il nodo destinazione da cui aggiungere l'arco
    @throw duplicated_edge nel caso in cui si cerchi di aggiungere un arco già esistente
    @throw key_not_found nel caso in cui si cerchi di aggiungere un arco su nodi inesistenti
    */
    void add_edge(const T &value1, const T &value2){

        if(check_E(value1, value2)==0 && check_E(value2, value1)==0){
            matrix[getNodeIndex(value1)][getNodeIndex(value2)] = true;
            num_edges++;
        }
        else {
            if (check_E(value1, value2)>0 || check_E(value2, value1)>0)
                throw duplicated_edge("EXCEPTION: Impossibile aggiungere un arco gia' esistente!");
            else throw key_not_found("EXCEPTION: Impossibile aggiungere un arco su un nodo inesistente!");
        }
    }

    /** METODO PUBBLICO RICHIESTO DA PROGETTO
    Rimuove un arco, dati i relativi valori, se esistente e i valori sono nodi esistenti
    @param value1 dato elementare T che identifica il nodo sorgente da cui rimuovere l'arco
    @param value2 dato elementare T che identifica il nodo destinazione da cui rimuovere l'arco
    @throw duplicated_edge nel caso in cui si cerchi di rimuovere un arco inesistente
    @throw key_not_found nel caso in cui si cerchi di rimuovere un arco su nodi inesistenti
    */
    void remove_edge(const T &value1, const T &value2){

        if(check_E(value1, value2)>0 || check_E(value2,value1)>0){
            safe_remove_edge(value1, value2);
        }
        else {
            if (check_E(value1,value2)==0 || check_E(value2,value1)==0)
                throw key_not_found("EXCEPTION: Impossibile rimuovere un arco inesistente!");
            else throw key_not_found("EXCEPTION: Impossibile rimuovere un arco su un nodo inesistente!");
        }
    }

    /** METODO PUBBLICO RICHIESTO DA PROGETTO
    Stampa true se il valore corrisponde ad un nodo, false altrimenti
    @param value dato elementare T del nodo che cerco
    */
    void exists(const T &value) const{
        if(!check_N(value))
            std::cout <<  "exists(" << value << ") = true" << std::endl;
        else
            std::cout <<  "exists(" << value << ") = false" << std::endl;
    }

    /** METODO PUBBLICO RICHIESTO DA PROGETTO
    Stampa true se il valore corrisponde ad un arco di nodi esistenti, false altrimenti
    @param value1 dato elementare T che rappresenta il nodo sorgente dell'arco che cerco
    @param value2 dato elementare T che rappresenta il nodo destinazione dell'arco che cerco
    @throw key_not_found nel caso in cui si cerchi un arco su nodi inesistenti
    */
    void has_edge(const T &value1, const T &value2) const{

        if(!check_N(value1)&&!check_N(value2)){

            if(check_E(value1, value2)>0 || check_E(value2, value1)>0)
                std::cout <<  "has_edge(" << value1 << "," << value2 << ") = true" << std::endl;
            else
                std::cout <<  "has_edge(" << value1 << "," << value2 << ") = false" << std::endl;
        }
        else throw key_not_found("EXCEPTION: Impossibile ricercare un arco su un nodo inesistente!");
    }

    /** METODO AGGIUNTIVO NON RICHIESTO
   Stampa la matrice di adiacenza per semplificare i controlli

   */
    ostream& print_matrix(ostream& os) {

        if (matrix == nullptr) return os;

        for(int k = 0; k < num_nodes; k++){
            for (int j = 0; j<num_nodes; j++ ){
                os<<matrix[k][j]<<"\t";
            }
            os<<endl;
        }
        return os;
    }

    /**
         Definizione di una classe const_iterator che implementa gli ITERATORI FORWARD sui nodi

         @brief Classe che rappresenta un iteratore forward sui nodi
         */
    class const_iterator {

    private:

        const Node<T>* n;			///< puntatore al nodo contenente il dato "puntato" dall'iteratore
        friend class Graph;		///< classe padre

        /**
        Costruttore secondario di un iteratore forward sui nodi, dato un puntatore al nodo
        @param p puntatore al nodo
        */
        explicit const_iterator(const Node<T>* p): n(p) {
        }

    public:

        //Traits degli iteratori
        typedef std::forward_iterator_tag	iterator_category;	///< tag corrispondente all'iteratore forward
        typedef Node<T>			             	value_type;			///< definizionde del tipo di dato "puntato" dall'iteratore
        typedef ptrdiff_t                	difference_type;	///< tipo (di default) usato per differenziare due puntatori
        typedef const Node<T>*			     	pointer;			///< definizione del puntatore al tipo di dato "puntato" dall'iteratore
        typedef const Node<T>&					reference; 			///< definizione del puntatore al tipo di dato "puntato" dall'iteratore

        /**
        COSTRUTTORE DEFAULT di un iteratore forward sui nodi
        */
        const_iterator() : n(nullptr){
        }

        /**
        DISTRUTTORE di un iteratore forward sui nodi
        */
        ~const_iterator() {
        }

        /**
        COPY CONSTRUCTOR di un iteratore forward sui nodi
        @param other iteratore da cui copiare this
        */
        const_iterator(const const_iterator &other): n(other.n){
        }

        /**
        OPERATOR= di un iteratore forward sui nodi
        @param other iteratore di cui copio lo stato in this
        @return iteratore risultante dalla copia
        */
        const_iterator& operator=(const const_iterator &other){

            if(this!=&other) {
                const_iterator tmp(other);
                tmp.swap(*this);
            }
            return *this;
        }

        /**
        OPERATOR& di deferenziamento di iteratore forward sui nodi
        @return dato riferito dall'iteratore
        @throw bad_iterator nel caso in cui si cerchi di dereferenziare un iteratore "nullo"
        */
        reference operator*() const {

            if(n==nullptr) throw bad_iterator("EXCEPTION: impossibile dereferenziare un iteratore nullo!");
            return *n; //ritorno il valore del nodo
        }

        /**
        OPERATOR -> di deferenziamento di iteratore forward sui nodi
        @return puntatore al dato riferito dall'iteratore
        @throw bad_iterator nel caso in cui si cerchi di dereferenziare un iteratore "nullo"
        */
        pointer operator->()  {

            if(n==nullptr) throw bad_iterator("EXCEPTION: impossibile dereferenziare un iteratore nullo!");
            return &*n ; //ritorno il puntatore al valore del nodo
        }

        /**
        OPERATOR++ di iterazione post-incremento di iteratore forward sui nodi
        @return puntatore allo stato precedente
        @throw bad_iterator nel caso in cui si cerchi di incrementare un iteratore "nullo"
        */
        const_iterator operator++(int) {

            if(n==nullptr) throw bad_iterator("EXCEPTION: impossibile incrementare un iteratore nullo!");
            const_iterator tmp(*this);	//vecchio stato
            n = n -> _next; 			//cambio lo stato corrente
            return tmp;					//ritorno il vecchio stato
        }


        /**
        OPERATOR++ di iterazione pre-incremento di iteratore forward
        @return puntatore allo stato nuovo
        @throw bad_iterator nel caso in cui si cerchi di incrementare un iteratore "nullo"
        */
        const_iterator& operator++() {

            if(n==nullptr) throw bad_iterator("EXCEPTION: impossibile incrementare un iteratore nullo!");
            n = n -> _next; //cambio lo stato corrente
            return *this;	//ritorno il nuovo stato
        }

        /**
        OPERATOR!= di uguaglianza un iteratore forward sui nodi
        @param other iteratore da confrontare
        @return true se other e' uguale al puntatore a nodi, false altrimenti
        */
        bool operator==(const const_iterator &other) const {

            return (n == other.n);
        }

        /**
        OPERATOR!= di diversita' un iteratore forward sui nodi
        @param other iteratore da confrontare
        @return true se other e' diverso dal puntatore a nodi, false altrimenti
        */
        bool operator!=(const const_iterator &other) const {

            return (n != other.n);
        }

        /**
        Metodo utile allo swap dei dati membro di un iteratore forward sui nodi
        @param other iteratore con cui scambiare i dati membro con this
        */
        void swap(const_iterator &other){

            std::swap(this -> n, other.n);
        }

    }; // end class const_iterator

    /**
    METODO PUBBLICO
    Restituisce un const_iterator alla testa della lista dei nodi del grafo
    @return iteratore alla testa
    */
    const_iterator begin() const{
        return const_iterator(_headN);
    }

    /**
    METODO PUBBLICO
    Restituisce un const_iterator alla coda della lista dei nodi del grafo
    @return iteratore alla coda
    */
    const_iterator end() const{
        return const_iterator(nullptr);
    }



};


#endif //GRAPH_GRAPH_H
