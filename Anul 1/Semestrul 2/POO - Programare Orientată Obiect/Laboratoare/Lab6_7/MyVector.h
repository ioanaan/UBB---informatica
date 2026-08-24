#pragma once

template <typename T>
class MyVector
{
private:
    int dimensiune;
    int capacitate;
    T* elems;

public:
    MyVector() noexcept
        : dimensiune{ 0 }, capacitate{ 10 }, elems{ new T[10] } {
    }

    ~MyVector() {
        delete[] elems;
    }

    MyVector(const MyVector& other)
        : dimensiune{ other.dimensiune }, capacitate{ other.capacitate }, elems{ new T[capacitate] }
    {
        for (int i = 0; i < dimensiune; i++)
            elems[i] = other.elems[i];
    }

    MyVector& operator=(const MyVector& other) {
        if (this == &other) {
            return *this;
        }

        delete[] elems;

        dimensiune = other.dimensiune;
        capacitate = other.capacitate;
        elems = new T[capacitate];

        for (int i = 0; i < dimensiune; i++)
        {
            elems[i] = other.elems[i];
        }

        return *this;
    }

    void add(const T& element) {
        if (dimensiune == capacitate)
        {
            capacitate *= 2;
            T* aux = new T[capacitate];
            for (int i = 0; i < dimensiune; i++)
            {
                aux[i] = elems[i];
            }

            delete[] elems;
            elems = aux;
        }

        elems[dimensiune] = element;
        dimensiune += 1;
    }

    void remove(int index) noexcept {
        for (int i = index; i < dimensiune-1; i++) {
            elems[i] = elems[i + 1];
        }
        dimensiune -= 1;
    }

    T& get(int index) const noexcept {
        return elems[index];
    }

    int size() const noexcept {
        return dimensiune;
    }

    T& operator[](int index) noexcept {
        return elems[index];
    }
    const T& operator[](int index) const noexcept {
        return elems[index];
    }

    MyVector(MyVector&& other) noexcept
        : dimensiune{ other.dimensiune }, capacitate{ other.capacitate }, elems{ other.elems }
    {
        other.elems = nullptr;
        other.dimensiune = 0;
        other.capacitate = 0;
    }

    MyVector& operator=(MyVector&& other) noexcept {
        if (this == &other)
            return *this;
        delete[] elems;
        elems = other.elems;
        dimensiune = other.dimensiune;
        capacitate = other.capacitate;
        other.elems = nullptr;
        other.dimensiune = 0;
        other.capacitate = 0;
        return *this;
    }

    // Iterator
    class Iterator {
    private:
        T* current;
    public:
        Iterator(T* ptr) : current{ ptr } {}

        T& operator*() noexcept {
            return *current;
        }

        Iterator& operator++() noexcept {
            current++;
            return *this;
        }

        bool operator!=(const Iterator& other) const noexcept {
            return current != other.current;
        }
    };

    Iterator begin() noexcept {
        return Iterator(elems);
    }

    Iterator end() noexcept {
        return Iterator(elems + dimensiune);
    }

    Iterator begin() const noexcept {
        return Iterator(elems);
    }

    Iterator end() const noexcept {
        return Iterator(elems + dimensiune);
    }
};