#ifndef ITERATOR_H
#define ITERATOR_H

#include "exception.h"

template <class T, class F>
class iterator{
    T** cur;
    unsigned nb;
    unsigned nbItems;
    iterator(T** c, unsigned int nbItems): cur(c),nb(0),nbMax(nbItems){}
    friend class F;
public:
    iterator(): cur(0), nb(0),nbItems(0){}
    bool operator!=(const iterator& it) const { return cur!=it.cur; }
    iterator& operator++() {
        if(nb<nbItems) nb++;
        else throw exception("Error: overflow");
        cur++;
        return *this;
    }
    iterator& operator++(int) {
        iterator* old = this;
        if(nb<nbItems) nb++;
        else throw exception("Error: overflow");
        cur++;
        return *old;
    }
    iterator& operator--() {
        if(nb>0) nb--;
        else throw exception("Error: reach head of array");
        cur--;
        return *this;
    }
    iterator& operator--(int) {
        iterator* old = this;
        if(nb>0) nb--;
        else throw exception("Error: reach head of array");
        cur--;
        return *old;
    }
    T& operator*() const { return **cur; }
};


template <class T, class F>
class const_iterator{
    T** cur;
    unsigned nb;
    unsigned nbItems;
    const_iterator(T** c, unsigned int nbItems): cur(c),nb(0),nbMax(nbItems){}
    friend class F;
public:
    const_iterator(): cur(0), nb(0),nbItems(0){}
    bool operator!=(const const_iterator& it) const { return cur!=it.cur; }
    const_iterator& operator++() {
        if(nb<nbItems) nb++;
        else throw exception("Error: overflow");
        cur++;
        return *this;
    }
    const_iterator& operator++(int) {
        const_iterator* old = this;
        if(nb<nbItems) nb++;
        else throw exception("Error: overflow");
        cur++;
        return *old;
    }
    const_iterator& operator--() {
        if(nb>0) nb--;
        else throw exception("Error: reach head of array");
        cur--;
        return *this;
    }
    const_iterator& operator--(int) {
        iterator* old = this;
        if(nb>0) nb--;
        else throw exception("Error: reach head of array");
        cur--;
        return *old;
    }
    const T& operator*() const { return **cur; }
};

#endif // ITERATOR_H
