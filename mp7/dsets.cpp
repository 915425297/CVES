/* Your code here! */
#include "dsets.h"
#include<vector>
#include <iostream>
using namespace std;
/**
* @param num shit
* Returns shit
*/
	void DisjointSets::addelements(int num) {
		if (num < 0) return;
		for (int x = 0; x < num; x++) {
			vec.push_back(-1);
		}
	}
/**
* @param elem shit
* Returns shit
*/
	int DisjointSets::find(int elem) {
		if (vec[elem] < 0) return elem;
		int t = find(vec[elem]);
		vec[elem] = t;
		return t;
	}

/**
* @param a shit
* @param b shit
* Returns shit
*/
	void DisjointSets::setunion	(int a, int b) {
		int a1 = find(a), b1 = find(b);
		if (a1 == b1) return;
		if (vec[a1] > vec[b1]) {
		vec[b1] += vec[a1];
		vec[a1] = b1;
		} else {
		vec[a1] += vec[b1];
		vec[b1] = a1;	
		}
		
	}
/**
* @param elem shit
* Returns shit
*/
	int DisjointSets::size(int elem) {
		return -vec[find(elem)];
	}
