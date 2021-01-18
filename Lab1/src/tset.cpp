// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
#include<algorithm>

TSet::TSet(int mp) : BitField(0){
    MaxPower = mp;
    TBitField tmp(mp);
    BitField = tmp;
	if (MaxPower < 0) throw - 1;
	
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(0){
    *(this) = s;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(0) {
	MaxPower = bf.GetLength();
	BitField = bf;
	if (MaxPower < 0) {
		throw 0;
	}
}

TSet::operator TBitField(){
    return BitField;
}

int TSet::GetMaxPower(void) const { // получить макс. к-во эл-тов
    return BitField.GetLength();
}

int TSet::IsMember(const int Elem) const {// элемент множества?
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem){ // включение элемента множества
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem){// исключение элемента множества
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s){ // присваивание
    MaxPower = s.GetMaxPower();
    BitField = s.BitField;
    return *(this);
}

int TSet::operator==(const TSet &s) const { // сравнение
    return MaxPower==s.GetMaxPower() && BitField==s.BitField;
}

int TSet::operator!=(const TSet &s) const {// сравнение
    return !(*(this) == s);
}

TSet TSet::operator+(const TSet &s) { // объединение
    
    TSet tmp(max(s.MaxPower, MaxPower));
    tmp.BitField = BitField | s.BitField;
    return tmp;
}

TSet TSet::operator+(const int Elem){ // объединение с элементом
    TSet tmp(*(this));
    tmp.InsElem(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem){// разность с элементом
    TSet tmp(*(this));
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet &s){ // пересечение
    TSet tmp(max(s.MaxPower, MaxPower));
    tmp.BitField = BitField & s.BitField;
    return tmp;
}

TSet TSet::operator~(void) { // дополнение
    TSet* tmp = new TSet(*this);
    tmp->BitField = ~(tmp)->BitField;
    return *tmp;

}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) {// ввод
    istr >> s.MaxPower;
    TBitField tmp(s.MaxPower);
    s=tmp;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) { // вывод
    ostr<<s.BitField<<"\n";
    return ostr;
}
