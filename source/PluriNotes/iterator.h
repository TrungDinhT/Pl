#ifndef ITERATOR_H
#define ITERATOR_H

#include "exception.h"

template <class T>
class _Iterator{
    T** cur;
    unsigned nb;
    unsigned nbItems;
protected:
    _Iterator(T** c, unsigned int nbItems);
public:
    _Iterator();
    bool operator!=(const _Iterator& it) const { return cur!=it.cur; }
    _Iterator& operator++() {
        if(nb<nbItems) nb++;
        else throw _Exception("Error: overflow");
        cur++;
        return *this;
    }
    _Iterator& operator++(int) {
        _Iterator* old = this;
        if(nb<nbItems) nb++;
        else throw _Exception("Error: overflow");
        cur++;
        return *old;
    }
    _Iterator& operator--() {
        if(nb>0) nb--;
        else throw _Exception("Error: reach head of array");
        cur--;
        return *this;
    }
    _Iterator& operator--(int) {
        _Iterator* old = this;
        if(nb>0) nb--;
        else throw _Exception("Error: reach head of array");
        cur--;
        return *old;
    }
    T* operator*() const { return *cur; }
};

template <class T>
_Iterator<T>::_Iterator(T **c, unsigned int nbItems):cur(c),nb(0),nbItems(nbItems){}

template <class T>
_Iterator<T>::_Iterator(): cur(0), nb(0),nbItems(0){}




template <class T>
class _const_iterator: public _Iterator<T>{
protected:
    _const_iterator(T** c, unsigned int nbItems);
public:
    _const_iterator();
    const T* operator*() const { return _Iterator<T>::operator*(); }
};

template <class T>
_const_iterator<T>::_const_iterator(T **c, unsigned int nbItems): _Iterator<T>(c,nbItems){}

template <class T>
_const_iterator<T>::_const_iterator(): _Iterator<T>(){}

#endif // ITERATOR_H
