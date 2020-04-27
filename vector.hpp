/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 00:03:05 by jjosephi          #+#    #+#             */
/*   Updated: 2020/04/26 20:57:53 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <cstdlib>
#include <memory>

template <typename T, class Allocator = std::allocator<T>>
class vector
{
	class Iterator
{

private:
    vector<T>* v;
    int        i;
public:
    using value_type = T;
    using pointer    = T*;
    using reference  = T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    Iterator():                    v(nullptr), i(0) {}   
    Iterator(vector<T>* v, int i): v(v),       i(i) {}

    reference       operator*()             {return (*v)[i];}
    pointer         operator->()            {return &((*v)[i]);}
    reference       operator[](int m)       {return (*v)[i + m];}


    Iterator& operator++()       {++i;return *this;}
    Iterator& operator--()       {--i;return *this;}
    Iterator  operator++(int)    {Iterator r(*this);++i;return r;}
    Iterator  operator--(int)    {Iterator r(*this);--i;return r;}

    Iterator& operator+=(int n)  {i += n;return *this;}
    Iterator& operator-=(int n)  {i -= n;return *this;}

    Iterator operator+(int n)   const {Iterator r(*this);return r += n;}
    Iterator operator-(int n)   const {Iterator r(*this);return r -= n;}

    difference_type operator-(Iterator const& r) const {return i - r.i;}

    bool operator<(Iterator const& r)  const {return i <  r.i;}
    bool operator<=(Iterator const& r) const {return i <= r.i;}
    bool operator>(Iterator const& r)  const {return i >  r.i;}
    bool operator>=(Iterator const& r) const {return i >= r.i;}
    bool operator!=(const Iterator &r) const {return i != r.i;}
    bool operator==(const Iterator &r) const {return i == r.i;}
	size_t index(){return i;}
};
class Reverse_Iterator
{

private:
    vector<T>* v;
    int        i;
public:
    using value_type = T;
    using pointer    = T*;
    using reference  = T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

   Reverse_Iterator():                    v(nullptr), i(0) {}   
   Reverse_Iterator(vector<T>* v, int i): v(v),       i(i) {}

    reference       operator*()             {return (*v)[i];}
    pointer         operator->()            {return &((*v)[i]);}
    reference       operator[](int m)       {return (*v)[i + m];}


   Reverse_Iterator& operator++()       {--i;return *this;}
   Reverse_Iterator& operator--()       {++i;return *this;}
   Reverse_Iterator  operator++(int)    {Iterator r(*this);--i;return r;}
   Reverse_Iterator  operator--(int)    {Iterator r(*this);++i;return r;}

   Reverse_Iterator& operator+=(int n)  {i -= n;return *this;}
   Reverse_Iterator& operator-=(int n)  {i += n;return *this;}

   Reverse_Iterator operator+(int n)   const {Iterator r(*this);return r -= n;}
   Reverse_Iterator operator-(int n)   const {Iterator r(*this);return r += n;}

    difference_type operator-(Iterator const& r) const {return i - r.i;}

    bool operator<(Iterator const& r)  const {return i <  r.i;}
    bool operator<=(Iterator const& r) const {return i <= r.i;}
    bool operator>(Iterator const& r)  const {return i >  r.i;}
    bool operator>=(Iterator const& r) const {return i >= r.i;}
    bool operator!=(Reverse_Iterator &r) const {return i != r.i;}
    bool operator==(Reverse_Iterator &r) const {return i == r.i;}
	size_t index(){return i;}
};
private:
	size_t size;
	size_t capacity;
	T *ptr;
public:
	using reference  = T&;
	using value_type = T;
	
	vector(Allocator& alloc = T) { ptr = nullptr, size = 0, capacity = 0;} //Constructor
	
	~vector();							//Destructor
	
	vector(const vector& cpy);			//Copy Constructor
	
	vector (size_t n, const T& val); //Fill Constructor
	
	vector::vector()
	{
		size = 0;
		capacity = 0;
		ptr = Allocator.allocate(size);
	}

	vector::~vector()
	{
	//	delete[] ptr;
		ptr = Allocator.deallocate(ptr, size);
		ptr = nullptr;
		size = 0;
		capacity = 0;
	}

	vector::vector(const vector& cpy)
	{
		ptr = new T[cpy.capacity()];
        std::copy(&cpy[0], &cpy[cpy.size()], ptr);
        size = cpy.size();
	}

	vector::vector(size_t n, const T& val)
	{
		size = n;
		capacity = n;
		ptr = Allocator.allocate(n);
		if (n > 0)
			for (size_t i = 0; i < n; i++)
				ptr[n] = val;
	}
	
	Iterator begin(){return new Iterator(vector, 0);}// Returns an iterator pointing to the first element in the vector.
	
	Iterator end(){return new Iterator(vector, size);}//Returns an iterator referring to the past-the-end element in the vector container.
	
	
	size_t size(){return size;}//Returns the number of elements in the vector.
	
	bool empty() {return size == 0;}//is size 0?
	
	void resize(size_t n)//Resizes the container so that it contains n elements.
	{
		if (size > n)
			size = n;
		else if (n <= capacity)
			size = n;
		else
		{
			reserve(n);
			size = n;
		}
	}
	
	size_t capacity() {return capacity;} //Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
	
	void reserve (size_t n)//Requests that the vector capacity be at least enough to contain n elements.
	{
		if (n > capacity)
		{
			T* tmp = new T[n];
			std::copy(ptr, ptr + capacity, tmp);
			delete[] ptr;
			capacity = n;
		}
	}
	
	reference front() {return ptr[0]&;}//Returns a reference to the first element in the vector.
	
	reference back() {return ptr[size];}//back
	
	reference operator[] (size_t n){return ptr[n];}//Returns a reference to the element at position n in the vector container.
	
	vector& operator= (vector& x) //Assigns new contents to the container, replacing its current contents, and modifying its size accordingly
	{
		if (x::size() > this.size)
			resize(x::size());
		for(size_t i = 0; i++; i < x::size())
		{
			ptr[i] = x[i];
		}
		size = x::size();
	}
	
	reference at (size_t n)//Position of an element in the container. OOR exceptions
	{
		if (n >= size)
			std::out_of_range("");
		else
			return ptr[n];
	}
	
	
	//The vector is extended by inserting new elements before the element at the specified position
	void insert (size_t& pos, size_t& n, T& val)
	{
		if (size < n + capacity)
            reserve(size + n);
        size += n;
        for (size_t i = size - 1; i >= pos + n; i--)
        {
            ptr[i] = ptr[i - n];
        }
        for(size_t i = pos; i < pos + n; i++)
        {
            ptr[i] = val;
        }
	}
	
    void insert (size_t pos, const value_type& val)
	{
		if(capacity == size)
            reserve(++size);
        for(size_t i = size - 1; i > pos; i--)
        {
            ptr[i]=ptr[i-1];
        }
        ptr[pos] = val;
	}

	//Removes from the vector either a single element (position) or a range of elements ([first,last)).
	Iterator erase (size_t n)
	{
		if (n > capacity)
			return nullptr;
		delete ptr[n];
        for(size_t i = n; i < size - 1; i++)
        {
            ptr[i] = ptr[i + 1];   //  Shift all the elements one step left, beginning from "pos+1"
        }
        size--;
		return new Iterator(vector, i);
	}
	
	Reverse_Iterator rbegin()//Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
	{
		return new Reverse_Iterator(vector, size)
	}
	
	Reverse_Iterator rend()//Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector
	{
		return new Reverse_Iterator(&vector, -1);
	}
	
	void assign (Iterator first, Iterator last)//Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
	{
		size_t n = first::index() - last::index();
		if (capacity < n)
			reserve(n);
		else if (size < n)
			size = n;
		int i = 0;
		for (first; first != last; first++)
		{
			ptr[i] = first[i];
			i++;
		}
		return first;
	}
	
	void assign (size_t n, const value_type& val)
	{
		if (n > capacity)
			reserve(n);
		for(size_t i = 0; i < n; i++)
		{
			ptr[i] = val;	
		}
		size = n;
	}
	
	void push_back (const value_type& val) //Adds a new element at the end of the vector, after its current last element
	{
		if (size == capacity)
			reserve(size + 1);
		ptr[size + 1] = val;
	}
	
	void pop_back()//Removes the last element in the vector, effectively reducing the container size by one4
	{
		delete ptr[size];
		size--;
	}
	
	void clear()//Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.4
	{
		for (size_t i = size; i > 0; i--)
			delete ptr[i];
		size = 0;
	}
	
	void swap (vector& x) //Exchanges the content of the container by the content of x, which is another vector object of the same type
	{
		vector tmp1 = new vector(vector);
		vector tmp2 = new vector(x);
		x = tmp1;
		vector = tmp2;
	}
	
};



#endif