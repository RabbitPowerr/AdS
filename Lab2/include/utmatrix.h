// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
    ValType* pVector;
    int size;       // размер вектора
    int startIndex; // индекс первого элемента вектора
public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector& v);                // конструктор копирования
    ~TVector();
    int GetSize() { return size; } // размер вектора
    int GetStartIndex() { return startIndex; } // индекс первого элемента
    ValType& operator[](int pos);             // доступ
    bool operator==(const TVector& v) const;  // сравнение
    bool operator!=(const TVector& v) const;  // сравнение
    TVector& operator=(const TVector& v);     // присваивание

    // скалярные операции
    TVector  operator+(const ValType& val);   // прибавить скаляр
    TVector  operator-(const ValType& val);   // вычесть скаляр
    TVector  operator*(const ValType& val);   // умножить на скаляр

    // векторные операции
    TVector  operator+(const TVector& v);     // сложение
    TVector  operator-(const TVector& v);     // вычитание
    ValType  operator*(const TVector& v);     // скалярное произведение

    // ввод-вывод
    friend istream& operator>>(istream& in, TVector& v)
    {
        for (int i = 0; i < v.size; i++)
            in >> v.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TVector& v){
        for (size_t i = 0; i < v.startIndex; i++) cout << 0 << ' ';
        for (size_t i = 0; i < v.size - v.startIndex; i++)
            out << v.pVector[i] << ' ';
        out << endl;
        return out;
    }
};

template <class ValType>
TVector<ValType>::TVector(int s=10, int si=0) {
    if (s > MAX_VECTOR_SIZE || si<0) throw 0;
    if (s != 0) pVector = new ValType[s-si];
    else pVector = nullptr;
    size = s;
    startIndex = si;
    for (size_t i = 0; i < size-startIndex; i++) {
        pVector[i] = (ValType)0;
        
    }
    
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v) {
    pVector = new ValType[v.size-v.startIndex];
    size = v.size;
    startIndex = v.startIndex;
    for (int i = 0; i < size - startIndex; i++) pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector() {
    if(pVector) delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos) {
    if (pos < startIndex || pos >= size)
        throw 0;
   return pVector[pos-startIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector& v) const {
    if (v.startIndex != startIndex || v.size != size) return 0;
    for (size_t i = 0; i < size-startIndex; i++) {
        if (pVector[i] != v.pVector[i]) return 0;
    }
    return 1;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector& v) const {
    return !(*(this) == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector& v) {
    
    if (size != v.size || startIndex!=v.startIndex) {
        if (size != 0) delete[] pVector;
        pVector = new ValType[v.size-v.startIndex];
        startIndex = v.startIndex;
        size = v.size;
    }
    for (size_t i = 0; i < size-startIndex; i++) {
        pVector[i] = v.pVector[i];
        
    }
   
    return *(this);
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType& val) {
    TVector<ValType> tmp(*(this));

    for (size_t i = 0; i < size - startIndex; i++) {
        tmp.pVector[i] += val;
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType& val) {
    TVector<ValType> tmp(*(this));

    for (size_t i = 0; i < size - startIndex; i++) {
        tmp.pVector[i] -= val;
    }
    return tmp;

} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType& val) {
    TVector<ValType> tmp(*(this));

    for (size_t i = 0; i < size - startIndex; i++) {
        tmp.pVector[i] *= val;
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v) {
    if (v.size - v.startIndex != size - startIndex) throw 0;
    TVector<ValType> tmp(*(this));
    for (size_t i = 0; i < size - startIndex; i++) {
        tmp.pVector[i] = pVector[i] + v.pVector[i];
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v) {
    if (v.size - v.startIndex != size - startIndex) throw 0;
    TVector<ValType> tmp(*(this));
    int i = 0;
    for (size_t i = 0; i < size-startIndex; i++) {
        tmp.pVector[i] = pVector[i] - v.pVector[i];
    }
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v) {
    if (v.size - v.startIndex != size - startIndex) throw 0;
    ValType ans=0;
    int j = 0;
    for (size_t i = startIndex; i < size; i++) {
        ans += pVector[i] * v.pVector[j];
        j++;

    }
    return ans;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType>> {
public:
    TMatrix(int s = 10);
    TMatrix(const TMatrix& mt);                    // копирование
    TMatrix(const TVector<TVector<ValType> >& mt); // преобразование типа
    bool operator==(const TMatrix& mt) const;      // сравнение
    bool operator!=(const TMatrix& mt) const;      // сравнение
    TMatrix& operator= (const TMatrix& mt);        // присваивание
    TMatrix  operator+ (const TMatrix& mt);        // сложение
    TMatrix  operator- (const TMatrix& mt);        // вычитание

    // ввод / вывод
    friend istream& operator>>(istream& in, TMatrix& mt)
    {
        for (int i = 0; i < mt.size; i++)
            in >> mt.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TMatrix& mt)
    {
        for (int i = 0; i < mt.size; i++)
            out << mt.pVector[i] << endl;
        return out;
    }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s=10) :TVector<TVector<ValType> >(s) {
    if (s<0 || s > MAX_MATRIX_SIZE) throw 0;
    if (s != 0)pVector = new TVector<ValType>[s];
    
    for (size_t i = 0; i < s; i++) {
        TVector<ValType> tmp(s, i);
        pVector[i] = tmp;
    }
    size = s;
    startIndex = 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
    TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
    TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const{
    if (size != mt.size) return 0;
    for (size_t i = 0; i < size-startIndex; i++) {
        if (pVector[i] != mt.pVector[i]) return 0;
    }
    return 1;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const{
    return !(*(this) == mt); 

} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt){
    if (size != mt.size) {
        if (size != 0)delete[] pVector;
        size = mt.size;
        pVector = new TVector<ValType>[size];
        startIndex = mt.startIndex;
    }
    for (size_t i = 0; i < size; i++) pVector[i] = mt.pVector[i];
    return *(this);
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt){
    return TVector<TVector<ValType> >::operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt){
    return TVector<TVector<ValType> >::operator-(mt);
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
