#ifndef __FREQTABLE_H__
#define __FREQTABLE_H__

#include <stdbool.h>
#include <string>

#ifndef NULL
#define NULL nullptr  // adopts C++11 notation
#endif

class BSTNode {
private:
    // word should always be stored in lowercase
    std::string word;
    // count how many occurrences of this word we have
    unsigned int count;

    BSTNode *left;
    BSTNode *right;

public:
    BSTNode(const char *str) {
        count = 1;
        word = str;
        left = right = NULL;
    }
    ~BSTNode() {
    }

    friend class FreqTable;
};

class FreqTable {
private:
    BSTNode *root;
    unsigned int n_elem;
    void destroy(BSTNode *p);
    void insert(BSTNode **p,const char *str);
    void erase(BSTNode **p,const char *str);
    BSTNode *successor(BSTNode *p);
    void deleteRoot(BSTNode **p);
    void print_all(BSTNode *p);

public:
    FreqTable(){
        n_elem = 0;
        root = NULL;
    }
    ~FreqTable(){
        clear();
    }
    void insert(const char *str);
    bool contains(const char *str);
    void erase(const char *str);
    bool empty();
    unsigned int size();
    void clear();
    void print_all();
};

#endif
