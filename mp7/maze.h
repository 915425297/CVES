/* Your code here! */
/* Your code here! */
/* Your code here! */
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <vector>
#ifndef _MAZE_H
#define _MAZE_H
#include <algorithm>
using namespace cs225;
using namespace std;
class SquareMaze {
	public:
	struct point {
		bool down = 1;
		bool right = 1;
	};
	int h;
	int w;
	point ** m;
	SquareMaze();
	~SquareMaze();
	void DFS(int x, int y, DisjointSets & sets, int t);
	void makeMaze(int width,int height );		
	vector< int > solveMaze ();
	bool canTravel(int x, int y, int dir) const;
	void setWall (int x, int y, int dir, bool exists);
	PNG * drawMaze () const;
	PNG * drawMazeWithSolution ();
};
#endif
