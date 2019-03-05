#include "freqtable.h"

#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <string.h>

using namespace std;

void FreqTable::insert(const char *str){
    // convert string to lowercase
    std::string str_lower = string(str);
    std::transform(str_lower.begin(), str_lower.end(), str_lower.begin(), ::tolower);
    // insert the word into the frequency table
    insert(&root,str_lower.c_str());
}

bool FreqTable::contains(const char *str){
    BSTNode *p = root;
    // convert string to lowercase
    std::string str_lower = string(str);
    std::transform(str_lower.begin(), str_lower.end(), str_lower.begin(), ::tolower);
    // search for the word in the tree
    while (p) {
        if (p->word == str_lower) return true;
        else if (p->word < str_lower) p = p->right;
        else p = p->left;
    }
    return false;
}

void FreqTable::erase(const char *str){
    // convert string to lowercase
    std::string str_lower = string(str);
    std::transform(str_lower.begin(), str_lower.end(), str_lower.begin(), ::tolower);
    // erase the word in the frequency table
    erase(&root, str_lower.c_str());
}

bool FreqTable::empty(){
    return (n_elem == 0);
}

unsigned int FreqTable::size(){
    // return number of unique elements
    return n_elem;
}

void FreqTable::clear(){
    destroy(root);
    n_elem = 0;
    root= NULL;
}

void FreqTable::print_all(){
    print_all(root);
}


//* * * * * * * * * * * * * * H E L P E R S * * * * * * * * * * * * *//
void FreqTable::insert(BSTNode **p,const char *str){
    if(!*p){
        // create a node for the word
        (*p) = new BSTNode(str);
        // increase the number of unique elements if the word was not found
        n_elem++;
    }
    else{
        // if the word is found, increase the word counter
        if((*p)->word == str){
            (*p)->count++;
            return;
        }
        // if the word is lexigraphically the lesser word, traverse left
        else if((*p)->word > str) insert(&((*p)->left), str);
        // otherwise traverse right
        else if((*p)->word < str) insert(&((*p)->right), str);
    }
}

void FreqTable::erase(BSTNode **p,const char *str){
    bool found = false;
    // search for the word in the tree
    while(*p){
        // if found, break out of loop
        if ((*p)->word == str) {
            found = true;
            break;
        }
        else if ((*p)->word < str) p = &((*p)->right);
        else if ((*p)->word > str) p = &((*p)->left);
    }
    // if the word count is greater than one, decrement count
    if (found == true && (*p)->count > 1) (*p)->count--;
    // otherwise delete the node
    else if (found == true && (*p)->count == 1){
        deleteRoot(p);
    }// end count and found check
}

BSTNode *FreqTable::successor(BSTNode *p){
    BSTNode *current = p;
    // find the leftmost leaf or the max value in the subtree
    // of root p
    while (current->left != NULL)
        current = current->left;
    return current;
}
void FreqTable::deleteRoot(BSTNode **p){
    // case 1: no chirren
    if ((*p)->left == NULL && (*p)->right == NULL){
        (*p) = NULL;
        delete (*p);
        n_elem--;
    }
    // case 2: left child
    else if ((*p)->right == NULL){
        BSTNode *temp = (*p);
        (*p) = (*p)->left;
        delete temp;
        n_elem--;
    }
    // case 3: right child
    else if ((*p)->left == NULL){
        BSTNode *temp = (*p);
        (*p) = (*p)->right;
        delete temp;
        n_elem--;
    }
    // case 2: two children
    else{
        BSTNode *temp = (*p);
        // the parent will point to the successor
        (*p) = successor((*p)->right);
        // the parent will point to the left of of the node being deleted
        (*p)->left = temp->left;
        delete temp;
        n_elem--;
    }
}
// post order traversal
// destroy the node starting from the lowest level
// and traversing to the top
void FreqTable::destroy(BSTNode *p){
    if(p){
        destroy(p->left);
        destroy(p->right);
    }
    delete p;
}

void FreqTable::print_all(BSTNode *p){
    if (p){
        // travserse to the left most elemnt
        print_all(p->left);
        // print words in order
        cout << p->word << " " << p->count << endl;
        print_all(p->right);
    }
}
