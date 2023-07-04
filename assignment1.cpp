//#include "common.h"

#ifndef _common_h_
#include "common.h"
#define _common_h_
#endif

//////////////////////////////////////////////////////////////
//
//			Some common functions
//
//////////////////////////////////////////////////////////////
digitList *digitize(char str[80])
{
	digitList*	L = 0;
	digitList*	node;

	int i;
	
	for(i = 0; i< strlen(str); i++)
	{
		if(str[i] < '0' || str[i] > '9')	break;

		node = new digitList(str[i] - '0', L);
		L = node;
	}

	return L;

}

digitList *trimDigitList(digitList* L)
{
	digitList* head = L;
	digitList* p = L;
	digitList* lastNotZero = p;

	while (p != nullptr) {
		if (p->digit != 0) {
			lastNotZero = p;
			p = p->nextDigit;
		}
	}

	if (lastNotZero == nullptr) {
		p = head;
		while (p != nullptr) {
			digitList* curr = p;
			p = p->nextDigit;
			delete curr;
			curr = nullptr;
		}
		L = nullptr;
	} else {
		p = lastNotZero->nextDigit;
		lastNotZero->nextDigit = nullptr;
		while (p != nullptr) {
			digitList* curr = p;
			p = p->nextDigit;
			delete curr;
			curr = nullptr;
		}
	}

	return L;
}

digitList *subDigitLists(int b, digitList* L1, digitList* L2)
{
	if (L1 == nullptr && L2 == nullptr) return digitize(b);
	else if (L1 == nullptr) return subDigitLists(b, L2, nullptr);
	else if (L2 == nullptr) {
		if (L1->getDigit() >= b) {
			int carry = L1->getDigit() - b;
			return new digitList(carry, subDigitLists(0, L1->getNextDigit(), nullptr));
		} else {
			int carry = L1->getDigit() + 10 - b;
			return new digitList(carry, subDigitLists(1, L1->getNextDigit(), nullptr));
		}
	} else {
		if (L1->getDigit() > L2->getDigit()) {
			int carry = L1->getDigit() - L2->getDigit() - b;
			return new digitList(carry, subDigitLists(0, L1->getNextDigit(), L2->getNextDigit()));
		} else if (L1->getDigit() == L2->getDigit()) {
			if (b == 1) {
				int carry = L1->getDigit() + 10 - L2->getDigit() - b;
				return new digitList(carry, subDigitLists(1, L1->getNextDigit(), L2->getNextDigit()));
			} else {
				int carry = L1->getDigit() - L2->getDigit() - b;
				return new digitList(carry, subDigitLists(0, L1->getNextDigit(), L2->getNextDigit()));
			}
		} else {
			int carry = L1->getDigit() + 10 - L2->getDigit() - b;
			return new digitList(carry, subDigitLists(1, L1->getNextDigit(), L2->getNextDigit()));
		}
	}
}


Integer computeValue(int operatorNum)
{
	Integer		L1, L2;

	L1 = operandArr[0];

	for(int i = 0; i<operatorNum; i++)
	{
		L2 = operandArr[i+1];
		switch(operatorArr[i])
		{
		case '+':
			L1 = L1 + L2;
			break;
		case '-':
			L1 = 0;
			break;
		}
		// L1 = L1.trimDigit();
	}
	
	return L1;
}
///////////////////////////////////////////////////////////////////////////
//
//		Some methods of Integer class
//
////////////////////////////////////////////////////////////////////
Integer Integer::operator +(Integer L)
{
	if(sign == L.sign) {
		return Integer(sign, addDigitLists(0, digits, L.digits));
	} else if (sign == 1 && L.sign == -1) {
		if (compareDigitLists(digits, L.digits) == 1) {
			return Integer(sign, subDigitLists(0, digits, L.digits));
		} else if (compareDigitLists(digits, L.digits) == 0) {
			return Integer(sign, subDigitLists(0, digits, L.digits));
		} else if (compareDigitLists(digits, L.digits) == -1) {
			return Integer(L.sign, subDigitLists(0, L.digits, digits));
		}
	}
}

Integer Integer::operator -(Integer L)
{
	return Integer();
}

Integer Integer::leftDigits(int n)
{
	return Integer();
}

Integer Integer::rightDigits(int n)
{
	return Integer();
}

Integer	Integer::shift(int n)
{
	return Integer();
}

Integer Integer::operator *(Integer Y)
{
	return Integer();
}
