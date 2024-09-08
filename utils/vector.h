#pragma once

template<typename Element>
class IteratorVector;

template<typename Element>
class vector {
public:
    //constructor
    vector();

    //constructor de copiere
    vector(const vector &obiect);

    //destructor
    ~vector();


    vector &operator=(const vector &obiect);

    //move constructor
    vector(vector &&obiect) noexcept;
    vector &operator=(vector &&obiect) noexcept;

    //add element
    void push_back(const Element &element);

    //get element from position
    Element &get(int pozitie) const noexcept;

    int size() const noexcept;

    void erase(int poz);

    //iterator
    friend class IteratorVector<Element>;

    IteratorVector<Element> begin() const;

    IteratorVector<Element> end() const;

private:
    int dimensiune{0};
    int capacitate{2};
    Element *elemente;

    void redimensionare();
};

template<typename Element>
vector<Element>::vector() :elemente{new Element[2]}{

}

template<typename Element>
vector<Element>::vector(const vector &obiect) {
    elemente = new Element[obiect.capacitate];
    for (int i = 0; i < obiect.dimensiune; i++) {
        elemente[i] = obiect.elemente[i];
    }
    dimensiune = obiect.dimensiune;
    capacitate = obiect.capacitate;
}

template<typename Element>
vector<Element> &vector<Element>::operator=(const vector &obiect) {
    delete[] elemente;
    elemente = new Element[obiect.capacitate];
    for (int i = 0; i < obiect.dimensiune; i++) {
        elemente[i] = obiect.elemente[i];
    }
    dimensiune = obiect.dimensiune;
    capacitate = obiect.capacitate;
    return *this;
}

template<typename Element>
vector<Element>::vector(vector &&obiect) noexcept {
    elemente = obiect.elemente;
    dimensiune = obiect.dimensiune;
    capacitate = obiect.capacitate;

    obiect.elemente = nullptr;
    obiect.dimensiune = 0;
    obiect.capacitate = 0;
}

template<typename Element>
vector<Element> &vector<Element>::operator=(vector &&obiect) noexcept {
    delete[] elemente;

    elemente = obiect.elemente;
    dimensiune = obiect.dimensiune;
    capacitate = obiect.capacitate;

    obiect.elemente = nullptr;
    obiect.dimensiune = 0;
    obiect.capacitate = 0;
    return *this;

}

template<typename Element>
void vector<Element>::push_back(const Element &element) {
    redimensionare();
    elemente[dimensiune++] = element;
}

template<typename Element>
void vector<Element>::erase(int pozitie) {
    if (pozitie < 0 || pozitie >= dimensiune) return;
    for (int i = pozitie; i < dimensiune - 1; i++) {
        elemente[i] = elemente[i + 1];
    }
    dimensiune--;
}

template<typename Element>
Element &vector<Element>::get(int pozitie) const noexcept {
    return elemente[pozitie];
}

template<typename Element>
int vector<Element>::size() const noexcept {
    return dimensiune;
}

template<typename Element>
void vector<Element>::redimensionare() {
    if (dimensiune < capacitate)
        return;
    capacitate *= 2;
    auto *auxiliar = new Element[capacitate];
    for (int i = 0; i < dimensiune; i++) {
        auxiliar[i] = elemente[i];
    }
    delete[] elemente;
    elemente = auxiliar;
}

template<typename Element>
vector<Element>::~vector() {
    delete[] elemente;
}


template<typename Element>
IteratorVector<Element> vector<Element>::begin() const {
    return IteratorVector<Element>(*this);
}

template<typename Element>
IteratorVector<Element> vector<Element>::end() const {
    return IteratorVector<Element>(*this, dimensiune);
}

template<typename Element>
class IteratorVector {
private:
     vector<Element> vector;
    int pozitie = 0;
public:
    explicit IteratorVector(const vector<Element> &vector) noexcept;

    IteratorVector(const vector<Element> &vector, int pozitie) noexcept;

    Element &element() const;

    void urmator();

    Element &operator*();

    IteratorVector &operator++();

    bool operator==(const IteratorVector &obiect) noexcept;

    bool operator!=(const IteratorVector &obiect) noexcept;

};


template<typename Element>
IteratorVector<Element>::IteratorVector(const vector<Element> &vector) noexcept : vector{vector} {}

template<typename Element>
IteratorVector<Element>::IteratorVector(const vector<Element> &vector, int pozitie) noexcept : vector{vector},
                                                                                               pozitie{pozitie} {}


template<typename Element>
Element &IteratorVector<Element>::element() const {
    return vector.elemente[pozitie];
}

template<typename Element>
void IteratorVector<Element>::urmator() {
    pozitie++;
}

template<typename Element>
Element &IteratorVector<Element>::operator*() {
    return element();
}

template<typename Element>
IteratorVector<Element> &IteratorVector<Element>::operator++() {
    urmator();
    return *this;
}

template<typename Element>
bool IteratorVector<Element>::operator==(const IteratorVector &obiect) noexcept {
    return pozitie == obiect.pozitie;
}

template<typename Element>
bool IteratorVector<Element>::operator!=(const IteratorVector &obiect) noexcept {
    return !(*this == obiect);
}