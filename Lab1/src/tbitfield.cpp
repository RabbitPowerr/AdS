// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include<algorithm>

TBitField::TBitField(int len){
	
	int size_int = sizeof(int)*8;
	MemLen = len / size_int + (bool)(len % size_int);
	BitLen = len;
	if (len < 0) throw 0;
	if (MemLen)pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) pMem[i] = 0;
	
}

TBitField::TBitField(const TBitField &bf){ // конструктор копирования
	pMem = new TELEM[bf.MemLen];
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
}

TBitField::~TBitField(){
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const { // индекс Мем для бита n
	int i = n /(sizeof(int)*8);
	return i;
}

TELEM TBitField::GetMemMask(const int n) const {// битовая маска для бита n
	return pMem[n];
}

TELEM TBitField::GetMask(const int i) const {// Маска с индексом i
	
	return pMem[i];
}

// доступ к битам битового поля

int TBitField::GetMemLength(void) const {
	return MemLen;
}

int TBitField::GetLength(void) const{ // получить длину (к-во битов)
	return BitLen;
}

void TBitField::SetBit(const int n) {// установить бит
	int i = GetMemIndex(n);
	int delta = n % (sizeof(int)*8);
	if (n < 0 || n >= BitLen) throw 0;
	TELEM tmp = (1 << delta);
	pMem[i] = pMem[i] | tmp;
}

void TBitField::ClrBit(const int n) { // очистить бит
	int i = GetMemIndex(n);
	if (n < 0||n>=BitLen) throw 0;
	TELEM delta = n % (sizeof(int) * 8);
	delta = (1 << delta);
	TELEM tmp = ~(delta);
	pMem[i] &= tmp;

}

int TBitField::GetBit(const int n) const { // получить значение бита
	int i = GetMemIndex(n);
	if (n < 0 || n >= BitLen) throw 0;
	int delta = n % (sizeof(int)*8);
	TELEM tmp = (1 << delta);
	return (bool)(tmp & pMem[i]);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) { // присваивание
	int size = bf.GetMemLength();
	if (size != MemLen) {
 		if(MemLen) delete[] pMem;
		MemLen = size;
		pMem = new TELEM[MemLen];
	}
	BitLen = bf.BitLen;
	for (size_t i = 0; i < MemLen; i++) pMem[i] = bf.GetMask(i);
	return *(this);
}

bool TBitField::operator==(const TBitField &bf) const { // сравнение
	if (bf.GetMemLength() != MemLen) return false;
	for (size_t i = 0; i < MemLen; i++)
		if (pMem[i] != bf.GetMemMask(i)) return false;
	return true;
}

bool TBitField::operator!=(const TBitField &bf) const { // сравнение
  return !(*(this)==bf);
}

TBitField TBitField::operator|(const TBitField &bf) { // операция "или"
	TBitField tmp(max(bf.BitLen, BitLen));
	int mi = min(bf.MemLen,MemLen);
	for (int i = 0; i < tmp.MemLen; i++) {
		if (i >= mi) {
			tmp.pMem[i] = 0;
			continue;
		}
		tmp.pMem[i] = bf.pMem[i] | pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) {// операция "и"
	TBitField tmp(max(bf.BitLen,BitLen));
	for (int i = 0; i < MemLen; i++) {
		if (i >= MemLen) {
			tmp.pMem[i] = bf.pMem[i];
			continue;
		}
		if (i >= bf.MemLen) {
			tmp.pMem[i] = pMem[i];
			continue;
		}
		tmp.pMem[i] = bf.pMem[i] & pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator~(void) {// отрицание
	TBitField tmp(*this);
	int num = BitLen / (sizeof(int) * 8);
	int j = 0;

	for (int i = 0; i < num; i++){
		j += (sizeof(int) * 8);
		tmp.pMem[i] = ~pMem[i];
	}
	for (; j<BitLen; j++) {
		if (tmp.GetBit(j)) {
			tmp.ClrBit(j);
		}
		else tmp.SetBit(j);
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) { // ввод
	
	for (int i = 0; i < bf.BitLen; i++) {
		int bit = 0;
		istr>> bit;
		if(bit) bf.SetBit(bit);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) { // вывод
	for (int i = 0; i < bf.BitLen; i++) 
		ostr << bf.GetBit(i)<<' ';
	return ostr;
}
