// TinyArray.h
#pragma once

#ifndef _TINYARRAY_h
#define _TINYARRAY_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// A tiny array that maximizes at 256 items. It can be used as a standard array or stack. Not both at the same time.
template <typename T>
class TinyArray
{
protected:
	uint8_t m_length{ 0 };
	uint8_t m_topIndex{ 0 };
	bool m_memConstraintMode{ false };
	T* m_elements{ nullptr };

	static T Nil()
	{
		static T nil;
		return nil;
	}

public:
	explicit TinyArray<T>(const uint8_t size, const bool memConstrain = false);
	~TinyArray<T>();

	// Returns the size of the array
	uint8_t Length() const;

	// (Stack) Push a value onto the top of the stack
	T Push(const T& value, const bool dropIfOverLimit = true);
	// (Stack) Pop the top value from the stack and return value
	T Pop();
	// (Stack) Return the value from the top of the stack
	T Top();
	// (Stack) Return the value from the bottom of the stack
	T Bottom();
	// (Stack) [Slow Operation] Pop the bottom value from the stack and return value (shifts entire array left)
	T PopBottom();
	// (Stack) Returns the number of entries
	uint8_t EntryCount() const { return m_topIndex; }

	// Shift all contents in the array left by a given value (values can be lost)
	void ShiftLeft(uint8_t shiftBy = 0);
	// Shift all contents in the array right by a given value (values can be lost)
	void ShiftRight(uint8_t shiftBy = 0);

	// (Stack) Removes value at given index and shifts remaining items down
	void RemoveAt(const uint8_t index, bool deleteItem = false);

	T Get(const uint8_t index);
	void Set(const uint8_t index, T value);

	// (Array) Getter
	T operator[] (const uint32_t index) const;

	// (Array) Setter
	T& operator[] (const uint32_t index);
};

template <typename T>
TinyArray<T>::TinyArray(const uint8_t size, const bool memConstrain)
{
	this->m_elements = new T[size];
	this->m_length = size;
	this->m_memConstraintMode = memConstrain;
}

template <typename T>
TinyArray<T>::~TinyArray()
{
	//for (uint8_t i; i < this->m_length; ++i)
	//	delete this->m_elements[i];

	delete[] this->m_elements;
	this->m_length = 0;
	this->m_topIndex = 0;
}

template <typename T>
uint8_t TinyArray<T>::Length() const
{
	return this->m_length;
}

template <typename T>
T TinyArray<T>::Push(const T& value, const bool dropIfOverLimit)
{
	if (dropIfOverLimit && this->m_topIndex == this->m_length)
		return value;

	this->m_elements[this->m_topIndex++] = value;
	return value;
}

template <typename T>
T TinyArray<T>::Pop()
{
	if (this->m_memConstraintMode)
	{
		auto value = this->Top();
		this->m_elements[this->m_topIndex - 1] = this->Nil();
		return value;
	}

	return this->m_elements[--this->m_topIndex];
}

template <typename T>
T TinyArray<T>::Top()
{
	return this->m_elements[this->m_topIndex - 1];
}

template <typename T>
T TinyArray<T>::Bottom()
{
	return this->m_elements[0];
}

template <typename T>
T TinyArray<T>::PopBottom()
{
	auto value = this->m_elements[0];
	uint8_t totalLength = this->m_length > 0 ? this->m_length - 1 : 0;

	for (uint8_t i = 0; i < totalLength; ++i)
		this->m_elements[i] = this->m_elements[i + 1];

	return value;
}

template <typename T>
void TinyArray<T>::ShiftLeft(uint8_t shiftBy)
{
	//TODO: Implement this function
}

template <typename T>
void TinyArray<T>::ShiftRight(uint8_t shiftBy)
{
	//TODO: Implement this function
}

template <typename T>
void TinyArray<T>::RemoveAt(const uint8_t index, bool deleteItem)
{
	auto item = this->m_elements[index];

	if (deleteItem)
		delete item;

	for (int8_t i = index + 1; i < this->m_topIndex; ++i)
		this->m_elements[i - 1] = this->m_elements[i];

	this->m_elements[this->m_topIndex - 1] = this->Nil();

	--this->m_topIndex;
}

template <typename T>
T TinyArray<T>::Get(const uint8_t index)
{
	if (index >= this->m_length)
		return this->Nil();

	return this->m_elements[index];
}

template <typename T>
void TinyArray<T>::Set(const uint8_t index, T value)
{
	this->m_elements[index] = value;
}

template <typename T>
T TinyArray<T>::operator[](const uint32_t index) const
{
	if (index >= this->m_length)
		return this->Nil();

	return this->m_elements[index];
}

template <typename T>
T& TinyArray<T>::operator[](const uint32_t index)
{
	return this->m_elements[index];
}

#endif

