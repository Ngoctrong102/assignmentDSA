/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked list
    size_t       _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
	~L1List() {
		this->clean();
		delete[] _pHead;
	}
    L1Item<T>* getHead(){ return this->_pHead; }
    void    clean();
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    T&      at(int i);// give the reference to the element i-th in the list
    T&      operator[](int i);// give the reference to the element i-th in the list

	L1Item<T>* find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
    int     insert(int i, T& a);// insert an element into the list at location i. Return 0 if success, -1 otherwise
    int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.

	L1Item<T>& push_back(T& a);// insert to the end of the list
    int     insertHead(T& a);// insert to the beginning of the list

    int     removeHead();// remove the beginning element of the list
    int     removeLast();// remove the last element of the list

    void    reverse();

    void    traverse(void (*op)(T&)) {
        // TODO: Your code goes here
        if (!this->isEmpty()) {
            L1Item<T>* p = this->_pHead;
            while (p->pNext!=NULL) {
                op(p->data);
                p=p->pNext;
            }
            op(p->data);
            p=NULL;
            delete[] p;
        }
    }
    // void    traverse(void (*op)(T&, int num)) {
    //     // TODO: Your code goes here
    //     p->data->num = 0;
    //     if (!this->isEmpty()) {
    //         L1Item<T>* p = this->_pHead;
    //         while (p->pNext!=NULL) {
    //             op(p->data, p->data->num);
    //             p=p->pNext;
    //         }
    //         op(p->data,  p->data->num);
    //         p=NULL;
    //         delete[] p;
    //     }
    // }
    void    traverse(void (*op)(T&, void*), void* pParam) {
        // TODO: Your code goes here
    }
};
// template <typename T>
// void L1List<T>::traverse(void (*op)(T&, void*), void* pParam){
//     if (!this->isEmpty()) {
//         L1Item<T>* p = this->_pHead;
//         while (p->pNext!=NULL) {
//             op(p->data);
//             p=p->pNext;
//         }
//         op(p->data);
//         p=NULL;
//         delete[] p;
//     }
// }
template <typename T>
T& L1List<T>::at(int i){
    if (i>this->_size-1 || i<0) throw DSAException(1,"Out range of the size");
    else {
        L1Item<T>* p=this->_pHead;
        for (int k=0;k<i;k++){
            p=p->pNext;
        }
        return p->data;
    }
}
template <typename T>
T& L1List<T>::operator[](int i){
    return this->at(i);
}
template <typename T>
L1Item<T>* L1List<T>::find(T& a, int& idx){
    if (!this->isEmpty()){
        L1Item<T>* p = this->_pHead;
        idx = 0;
        while (p!=NULL) {
			if (p->data == a) return p;
			p = p->pNext;
            idx++;
        }
    }
	idx = -1;
	return NULL;
}
template <typename T>
void L1List<T>::clean(){
	this->_pHead = NULL;
    this->_size = 0;
}
/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
L1Item<T>& L1List<T>::push_back(T &a) {
    // TODO: Your code goes here
    this->_size++;
    if (this->isEmpty()) {
        this->_pHead = new L1Item<T>(a);
		return *this->_pHead;
    }
    else{
        L1Item<T>* p = this->_pHead;
        while (p->pNext!=NULL)
        {
            p=p->pNext;
        }
        p->pNext= new L1Item<T>(a);
		return *p->pNext;
    }
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T &a) {
    // TODO: Your code goes here
    this->insert(0,a);
    return 0;
}

template <typename T>
int L1List<T>::remove(int i){
    if (i<0 || i>this->_size) return -1;
    if (i==0){
        L1Item<T>* p = this->_pHead;
        this->_pHead = p->pNext;
        delete p;
		p = NULL;
    }
    else {
        L1Item<T>* p = this->_pHead;
        for (int k=0;k<i-1;k++){
            p = p->pNext;
        }
        L1Item<T>* temp = p->pNext;
        p->pNext = p->pNext->pNext;
		delete temp;
		temp = NULL;
    }
    this->_size--;
    return 0;
}
/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
    this->remove(0);
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
    // TODO: Your code goes here
    this->remove(this->_size-1);
    return -1;
}
template <typename T>
int L1List<T>::insert(int i, T& a){
    if (i>this->_size || i<0) return -1;
    if (i==0) {
        L1Item<T>* p= new L1Item<T>(a);
        p->pNext = this->_pHead;
        this->_pHead= p;
    }
    else{
    L1Item<T>* p=this->_pHead;
    for (int k=0;k<i-1;k++){
        p=p->pNext;
    }
    L1Item<T>* temp = new L1Item<T>(a);
    temp->pNext = p->pNext;
    p->pNext = temp;
    }
    this->_size++;
    return 0;
}
template <typename T>
void L1List<T>::reverse(){
    if (this->_size>1){
        L1Item<T>* t=NULL;
        L1Item<T>* p = this->_pHead;
        L1Item<T>* s = p;
        while (p!=NULL){
            s=p->pNext;
            p->pNext = t;
            t = p;
            p = s;
        }
        this->_pHead = t;
        t=NULL;
        p=NULL;
        s=NULL;
        delete t,p,s;
    }
}

#endif //DSA191_A1_DSALIB_H