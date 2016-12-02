// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize() { return Size; };  // размер вектора
  int GetStartIndex() { return StartIndex; }; // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if ((s >= 0)&&( s <= MAX_VECTOR_SIZE)&&(si >= 0))
	{
		pVector = new ValType[s-si]; // Храним только значимые числа
		Size = s; // Сохраняем характеристику вектора (размерность)
		StartIndex = si; //Все, что левее si = 0; Поэтому (1 2 3) + (1 2) = (1 2 3) + (0 1 2) = (1 3 5)
	}
	else
		throw "VCrF";
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования TVector<ValType>::TVector(const TVector<ValType> &v)
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	pVector = new ValType[v.Size];
	Size = v.Size;
	StartIndex = v.StartIndex;
	for (int i = 0; i < Size - StartIndex; i++) //Заполняем только значимые -> 0 1 2 3 4 (5 элементов, пусть стартовый индекс = 1 -> значимые индексы: 5-1=4: 0 1 2 3. Цикл до 4-х)
		pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{ 
	
	if (pos >= 0)
	{
		if ((pos <= MAX_MATRIX_SIZE) || (pos < Size))
			if (pos >= StartIndex)
				return pVector[pos - StartIndex]; // [0 0 0 2 3 1 5 6]
			else
				throw "Azero";
		else
			throw "Amax";
	}
	else
		throw "Aneg";
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector<ValType> &v) const
{
	if ((Size == v.Size) && (StartIndex == v.StartIndex))
	{
		for (int i = 0; Size - StartIndex; i++)
			if (pVector[i] != v.pVector[i])
				return false;
		return true;
	}
	else
	{
		return false;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector<ValType> &v) const
{
	if ((Size != v.Size)||(StartIndex!=v.StartIndex))
	{
		return true;
	}
	else
	{
		for (int i = 0; Size - StartIndex; i++)
			if (pVector[i] == v.pVector[i])
				return false;
		return true;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this != &v)
	{
		if (Size != v.Size)
		{
			delete[] pVector;
			pVector = new ValType[v.Size];
		}
	}
	Size = v.Size;
	StartIndex = v.StartIndex;
	for (int i = 0; i < Size-StartIndex; i++)
	{
		pVector[i] = v.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> temp(Size, StartIndex);
	for (int i = 0; i < Size - StartIndex; i++)
	{
		temp.pVector[i] = pVector[i] + val;
	}
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> temp(Size, StartIndex);
	for (int i = 0; i < Size-StartIndex; i++)
	{
		temp.pVector[i] = pVector[i] - val;
	}
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> temp(Size, StartIndex);
	for (int i = 0; i < Size-StartIndex; i++)
	{
		temp.pVector[i] = pVector[i] * val;
	}
	return temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (Size == v.Size)
	{
		if (StartIndex <= v.StartIndex)
		{
			//Тут у нас this + v, потому что this имеет больше значимых чисел
			TVector<ValType> temp(Size, StartIndex);
			for (int i = 0; i < v.StartIndex; i++)
			{
				temp.pVector[i] = pVector[i];
			}
			for (int i = v.StartIndex; i < Size; i++)
			{
				temp.pVector[i] = pVector[i] + v.pVector[i];
			}
			return temp;
		}
		else //this имеет меньше значимых чисел, просто меняем местами порядок сложения;
		{
			TVector<ValType> temp(Size, StartIndex);
			for (int i = 0; i < StartIndex; i++)
			{
				temp.pVector[i] = v.pVector[i];
			}
			for (int i = StartIndex; i < Size; i++)
			{
				temp.pVector[i] = pVector[i] + v.pVector[i];
			}
			return temp;
		}
	}
	else
		throw "VAdd";
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (Size == v.Size)
	{
		if (StartIndex <= v.StartIndex)
		{
			//Тут у нас this + v, потому что this имеет больше значимых чисел
			TVector<ValType> temp(Size, StartIndex);
			for (int i = 0; i < v.StartIndex; i++)
			{
				temp.pVector[i] = pVector[i];
			}
			for (int i = v.StartIndex; i < Size; i++)
			{
				temp.pVector[i] = pVector[i] - v.pVector[i];
			}
			return temp;
		}
		else //this имеет меньше значимых чисел, просто меняем местами порядок сложения;
		{
			TVector<ValType> temp(Size, StartIndex);
			for (int i = 0; i < StartIndex; i++)
			{
				temp.pVector[i] = -v.pVector[i];
			}
			for (int i = StartIndex; i < Size; i++)
			{
				temp.pVector[i] = pVector[i] - v.pVector[i];
			}
			return temp;
		}
	}
	else
		throw "VSub";
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (Size == v.Size)
	{
			//Тут у нас this + v, потому что this имеет больше значимых чисел
		ValType Sum = 0;
			for (int i = 0; i < Size; i++)
			{
				Sum = pVector[i] * v.pVector[i];
			}
			return Sum;
	}
	else
		throw "VMul";
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	return 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	throw "eads";
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	return 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	return 0;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
