//
// Created by Michele De Sena on 09/04/21.
//

#ifndef GRAPH_TESTCLASS_H
#define GRAPH_TESTCLASS_H
class test {
public:
    char val;
    explicit test(char c){
        this->val = c;
    }
    friend ostream& operator<<(ostream& os, test t){
        os<<t.val;
        return os;
    }

};

bool operator == (const test& l, const test& r){
    return l.val == r.val;
}

bool operator != (const test& l, const test& r){
    return l.val != r.val;
}



#endif //GRAPH_TESTCLASS_H
