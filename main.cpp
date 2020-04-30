/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 19:01:31 by jjosephi          #+#    #+#             */
/*   Updated: 2020/04/30 12:26:30 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include "list.hpp"
#include <assert.h>
#include <string>

int main()
{
	ft::vector<int> vec(5,10);
	ft::vector<int> vec2(5,20);
	

	printf("Vector tests'''''''''''''''''''''''''''''''''''''''''''''''''''\n\n");
	printf("Size should be 5;\nSize is: %zu\nArray : ", vec.size());
	
	for (size_t i = 0; i < vec2.size(); i++)
	{
		printf("%d ", vec2[i]);
	}
	printf("\n");
	
	vec2[1] = 42;
	printf("Change 2nd elem to 42\n");
	
	for (size_t i = 0; i < vec2.size(); i++)
	{
		printf("%d ", vec2[i]);
	}
	printf("\n");
	
	printf("Second vector is\n");
	for (size_t i = 0; i < vec.size(); i++)
	{
		printf("%d ", vec[i]);
	}
	printf("\n");
	
	printf("Operator= \nVect1: ");
	vec.operator=(vec2);

	for (size_t i = 0; i < vec2.size(); i++)
	{
		printf("%d ", vec2[i]);
	}
	printf("\nVect2: ");
	
	for (size_t i = 0; i < vec2.size(); i++)
	{
		printf("%d ", vec2[i]);
	}
	printf("\n");
	
	printf("Is vec2 empty? %d\n", vec2.empty());
	vec2.clear();
	printf("Cleared vec2. Is empty? %d\n", vec2.empty());
	printf("Size is: %zu\n", vec2.size());
	vec2.reserve(20);
	printf("Reserved 20; Size of vector : %zu\n", vec2.capacity());

	vec2.assign(20,42);
	
	printf("Filled vec2 with 42. Size = %zu\n", vec2.size());

	printf("\nVec2:");
	for (size_t i = 0; i < vec2.size(); i++)
	{
		printf("%d ", vec2[i]);
	}
	printf("\n");
	
	vec2.insert(18, 69);
	printf("Inserted 69 at pos 17 %d\n",vec2[18]);
	
	for (size_t i = 0; i < vec2.size(); i++)
	{
		printf("%d ", vec2[i]);
	}
	printf("\n");
	
	vec2.push_back(3);
	printf("Pushed 3 at back\n");

	printf("\nVec2:");
	for (size_t i = 0; i < vec2.size(); i++)
	{
		printf("%d ", vec2[i]);
	}
	printf("\n");
	
	vec2.pop_back();
	printf("Removed elem at back\n");
	
	printf("\nVec2:");
	for (size_t i = 0; i < vec2.size(); i++)
	{
		printf("%d ", vec2[i]);
	}
	printf("\n");
	
	vec2.erase(18);
	
	printf("Removed element 17\n");


	printf("\nVec2:");
	for (size_t i = 0; i < vec2.size(); i++)
	{
		printf("%d ", vec2[i]);
	}
	printf("\n");

	for (size_t i = 0; i < vec.size(); i++)
	{
		vec[i] = i;
	}
	
	printf("Swapping vec1 and vec2\n\nBefore :\nVec1: ");
	for (size_t i = 0; i < vec.size(); i++)
	{
		printf("%d ", vec[i]);
	}
	printf("\nVec2:");
	for (size_t i = 0; i < vec2.size(); i++)
	{
		printf("%d ", vec2[i]);
	}
	printf("\n");
	vec2.swap(vec);
	printf("After :\nVec1: ");
	for (size_t i = 0; i < vec.size(); i++)
	{
		printf("%d ", vec[i]);
	}
	printf("\nVec2:");
	for (size_t i = 0; i < vec2.size(); i++)
	{
		printf("%d ", vec2[i]);
	}
	printf("\n");
	
	printf("printing first elem %d\n", vec2.front());
	printf("printing elem at back %d\n", vec2.back());
//```````````````````````````````````````````````````````````````````````````
	printf("\n\nList tests---------------------------------------\n\n");
	ft::list<int> lst(3,42);

	ft::list<int>::Iterator it1;
	ft::list<int>::Iterator end;

	
	it1 = lst.begin();
	printf("First elem in list %d\n", *it1.operator->());
	lst.push_back(69);
	end = lst.end();
	printf("List size: %zu\n", lst.size());

	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d ", *it1.operator->());

	lst.assign(1, 420);
	it1 = lst.begin();
	end = lst.end();
	printf("\nAssigning 420 to element 2\n");
	for (; it1.operator!=(end) ; it1.operator++())
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d ", *it1.operator->());

	lst.resize(2);


	it1 = lst.begin();
	end = lst.end();
	printf("\n Resized list to 2 elements %zu\n", lst.size());
	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d ", *it1.operator->());

	
	lst.erase(lst.begin());

	it1 = lst.begin();
	end = lst.end();
	printf("\nRemoved first element; size: %zu\n", lst.size());
	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d ", *it1.operator->());
	lst.push_back(35);
	lst.push_front(53);

	it1 = lst.begin();
	end = lst.end();
	printf("\nPushed 53 front, 35 back; size: %zu\n", lst.size());
	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d ", *it1.operator->());
	lst.pop_back();
	lst.pop_front();

	it1 = lst.begin();
	end = lst.end();
	printf("\nPoped front and back; size: %zu\n", lst.size());
	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d ", *it1.operator->());
	
	ft::list<int> lst2(5,42);
	lst2.assign(1, 430);
	lst2.assign(2, 69);
	lst2.assign(4, 1);

	it1 = lst2.begin();
	end = lst2.end();
	printf("\n;New list: size: %zu\n", lst2.size());
	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d ", *it1.operator->());

	lst2.unique();


	it1 = lst2.begin();
	end = lst2.end();
	printf("\nRemoved duplicates: size: %zu\n", lst2.size());
	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d ", *it1.operator->());

	lst2.sort();

	
	it1 = lst2.begin();
	end = lst2.end();
	printf("\nSorted list; size: %zu\n", lst2.size());
	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d ", *it1.operator->());
	lst2.reverse();

it1 = lst2.begin();
	end = lst2.end();
	printf("\nReverse list; size: %zu\n", lst2.size());
	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d ", *it1.operator->());
	

	it1 = lst.begin();
	end = lst.end();
	printf("\nSwap list; size: %zu\n Before\n lst1 :", lst2.size());
	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d\n list2:", *it1.operator->());

	it1 = lst2.begin();
	end = lst2.end();
	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d ", *it1.operator->());
	lst2.swap(lst);


it1 = lst.begin();
	end = lst.end();
	printf("After\n lst1 :");
	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d\n list2:", *it1.operator->());

	it1 = lst2.begin();
	end = lst2.end();
	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d ", *it1.operator->());
	
	//lst2.merge(lst);
	
	it1 = lst2.begin();
	end = lst2.end();
	for (; it1.operator!=(end) ; it1.operator++() )
	{
		printf("%d ", *it1.operator->());
	}
	printf("%d ", *it1.operator->());

	
	printf("\n\nMap tests---------------------------------------\n\n");

	//ft::map<int, int> mp();

	
	
	printf("\n\nStack tests---------------------------------------\n\n");

	// ft::Stack<int> tea();

	// printf("Is the queue empty? %d",tea.empty());
	// tea.push(42);
	// tea.push(69);
	// printf("Pushed 42 and 69. Size = %d",tea.size());
	// printf("Front value %d", tea.front());
	// printf("back Value %d", tea.back());
	// tea.pop();
	// printf("Pop() teat. First : %d, last: %d , size : %d", tea.front(), tea.back(), tea.size());
	
	// printf("\n\nQueue tests---------------------------------------\n\n");

	// ft::queue<int> tes();

	// printf("Is the queue empty? %d",tes.empty());
	// tes.push(42);
	// tes.push(69);
	// printf("Pushed 42 and 69. Size = %d",tes.size());
	// printf("Front value %d", tes.front());
	// printf("back Value %d", tes.back());
	// tes.pop();
	// printf("Pop() test. First : %d, last: %d , size : %d", tes.front(), tes.back(), tes.size());
}