#ifndef _SMART_FIXED_ARRAY_HPP
#define _SMART_FIXED_ARRAY_HPP

// C++ Library includes
#include <iostream>
#include <stdexcept>

template <typename T>
//! A data structure that wraps a fixed array
class SmartFixedArray
{
public:
    /* Public member methods */
    //! Sets up the SmartFixedArray.
    SmartFixedArray();
    //! Cleans up the SmartFixedArray.
    ~SmartFixedArray();

    //! Insert an item to the END of the array.
    void PushBack( T newItem );

    //! Remove the LAST item in the array.
    void PopBack();

    //! Get an item in the array at some index.
    T& GetAt( int index );

    //! Returns the amount of items currently stored in the array.
    int Size() const;

    //! Check if the array is currently empty.
    bool IsEmpty() const;

    //! Check if the array is currently full.
    bool IsFull() const;

    //! Clear the data.
    void Clear();

private:
    /* Private member variables */
    //! The pointer used for the dynamic array
    T m_array[100];

    //! The current size of the array
    const int ARRAY_SIZE;

    //! The current amount of items inserted into the array
    int m_itemCount;

    friend class SmartFixedArrayTester;
};

/**
Clear out the array to get ready to use it.
*/
template <typename T>
SmartFixedArray<T>::SmartFixedArray()
    : ARRAY_SIZE( 100 )
{
    Clear();
}

/**
Clean up the SmartFixedArray by calling the Clear function.
*/
template <typename T>
SmartFixedArray<T>::~SmartFixedArray()
{
    Clear();
}

/**
This function will:
- Reset the m_itemCount to 0.
*/
template <typename T>
void SmartFixedArray<T>::Clear()
{
    m_itemCount = 0;
}

/**
Return the value of m_itemCount;
*/
template <typename T>
int SmartFixedArray<T>::Size() const
{
    return m_itemCount;
}

/**
The array is full if m_itemCount is the same value as ARRAY_SIZE.

@return     true if the array is full, false otherwise.
*/
template <typename T>
bool SmartFixedArray<T>::IsFull() const
{
    return m_itemCount == ARRAY_SIZE;
}

/**
Check if the array is currently empty.
The array is empty if the m_itemCount is set to 0.

@return     true if empty, false otherwise.
*/
template <typename T>
bool SmartFixedArray<T>::IsEmpty() const
{
    return ( m_itemCount == 0 );
//    throw Exception::NotImplementedException( "SmartFixedArray<T>::IsEmpty" ); // Erase this once you work on this function
}

/**
PREP CHECKS - do these before inserting the data to make sure the array is in a valid state:

* Check if the array is full with the IsFull() function. If it is full, throw a StructureFullException.

READY TO INSERT:
1. Put the newItem into the array at the first empty position available.
2. Increment the m_itemCount by 1.

@param      newItem         The new item to store at the end of the array.
*/
template <typename T>
void SmartFixedArray<T>::PushBack( T newItem )
{
    if (m_itemCount == ARRAY_SIZE){
        throw std::runtime_error("Array is full");
    }

    m_array[m_itemCount] = newItem;
    m_itemCount++;
}

/**
ERROR CHECK:
1. If the array is currently empty, then throw a StructureEmptyException exception - we cannot remove an item from an empty array!

READY TO REMOVE:
When we're just removing the last item of the array, we only need to decrement m_itemCount by 1.
This is known as a "Lazy Deletion"; we're not explicitly removing the item, but it will be replaced later on.
*/
template <typename T>
void SmartFixedArray<T>::PopBack()
{
    if (m_itemCount == 0) {
        throw std::runtime_error("Array is empty");
    }

    m_itemCount--;
}

/**
ERROR CHECK:
1. If the array is empty, then we can't return anything; throw a StructureEmptyException.
2. If the index is out of range, throw a InvalidIndexException.

READY TO GET:
Return the element at this index.

@param      index       The index of the element to return.
*/
template <typename T>
T& SmartFixedArray<T>::GetAt( int index )
{
    if (m_itemCount == 0) {
        throw std::runtime_error("Array is empty");
    }
    if (index < 0 || index >= m_itemCount) {
        throw std::invalid_argument("Index cannot be less than 0 or greater than " + m_itemCount);
    }

    return m_array[index];
}

#endif
