/* Your code here! */
#ifndef _DSET_H
#define _DSET_H
#include <iostream>
#include <vector>
using namespace std;
class DisjointSets{
	public:
/**
* @param num shit
* Returns shit
*/
	void addelements(int num);
/**
* @param elem shit
* Returns shit
*/
	int find(int elem);	

/**
* @param a shit
* @param b shit
* Returns shit
*/	
	void setunion	(int a, int b);
/**
* @param elem shit
* Returns shit
*/
	int size(int elem);

	private:
		vector<int> vec;
};
#endif
