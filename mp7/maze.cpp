#include "maze.h"
#include <vector>
#include <queue>
using namespace cs225;
using namespace std;
SquareMaze::SquareMaze(	): m(NULL){
	
}	

SquareMaze::~SquareMaze() {
	if (m == NULL) return;
	for (int x = 0; x < h; x++) delete[] m[x];
	delete[] m;
	m = NULL;
}
void SquareMaze::DFS(int x, int y, DisjointSets & sets, int tx) {
	int t = rand() % 2;
	if (tx > 10) return;
	if (t) {
		if (x + 1 <= h && sets.find((x + 1) * w + y) != sets.find(x * w + y)) {
			sets.setunion((x + 1) * w + y, x * w + y);
			setWall(x, y, t, 0);
			DFS(x + 1, y, sets, tx + 1);
			
		}
	} else {
		if (y + 1 <= w && sets.find(x * w + y + 1) != sets.find(x * w + y)) {
			sets.setunion((x) * w + y + 1, x * w + y);
			setWall(x, y, t, 0);
			DFS(x, y + 1, sets, tx + 1);
			
		}
	}
}
void SquareMaze::makeMaze(int width,
int height)	{
	/*
	if (m != NULL) { 
	for (int x = 0; x < h; x++) delete[] m[x];
	delete[] m;		
	}
	m = new point * [height];
	for (int x = 0; x < height; x++) m[x] = new point[width];
	w = width;
	h = height;
	DisjointSets sets;
	sets.addelements(width * height);
	while(sets.size(0) != width * height) {
		 DFS(0, 0, sets, 0);
		for (int x = 0; x < h; x++) {
			for (int y = 0; y < w; y++) {
				if (y + 1 <= w && sets.find(x * w + y + 1) != sets.find(x * w + y)) {
			    sets.setunion((x) * w + y + 1, x * w + y);
			    setWall(x, y, 0, 0);				
				}
				if (x + 1 <= h && sets.find((x + 1) * w + y) != sets.find(x * w + y)) {
			     sets.setunion((x + 1) * w + y, x * w + y);
			     setWall(x, y, 1, 0);				
				}
			}
		}
	}*/
	if (m != NULL) { 
	for (int x = 0; x < h; x++) delete[] m[x];
	delete[] m;	
	m = NULL;	
	}
	m = new point * [height];
	for (int x = 0; x < height; x++) m[x] = new point[width];
	w = width;
	h = height;
}

bool SquareMaze::canTravel(int x,
int y,
int dir 
)const {
	if (m == NULL) return 0;
	switch(dir) {
		case(0): return x + 1 < w && !m[y][x].right;
		case(1): return y + 1 < h && !m[y][x].down; 
		case(2): return x - 1 >= 0 && !m[y][x - 1].right;
		case(3): return y - 1 >= 0 && !m[y - 1][x].down; 
	}
	return false;
}

void SquareMaze::setWall(int x, int y, int dir,bool exists ) {
	if (dir) m[x][y].down = exists;
	else m[x][y].right = exists;
}

PNG * SquareMaze::drawMaze () const{
	PNG * result = new PNG(w * 10 + 1, h * 10 + 1);
	int hi = h * 10 + 1, wi = w * 10 + 1;
	for (int x = 0; x < hi; x++) {
		HSLAPixel & p = result->getPixel(0, x);
		p.l = 0;
		HSLAPixel & p1 = result->getPixel(w * 10, x);
		p1.l = 0;
	}
	for (int x = 0; x < wi; x++) {
		if (x >= 10) {
		HSLAPixel & p = result->getPixel(x, 0);
		p.l = 0;
		}
		HSLAPixel & p1 = result->getPixel(x, h * 10);
		p1.l = 0;		
	}
	for (int x = 0; x < h; x++) {
		for (int y = 0; y < w; y++) {
			if (m[x][y].right) {
				for (int j = 0; j <= 10; j++) {
				HSLAPixel & p = result->getPixel((x + 1) * 10, y * 10 + j);
		        p.l = 0;
				}
			}
			if (m[x][y].down) {
				for (int j = 0; j <= 10; j++) {
				HSLAPixel & p = result->getPixel(x * 10 + j, (y + 1) * 10);
		        p.l = 0;
				}
			}
		}
	}
	for (int x = 0; x <= 10; x++) {
	HSLAPixel & p = result->getPixel(x, 0);
	p.l = 1;		
	}
	return result;
}

PNG *SquareMaze::drawMazeWithSolution () {
	PNG * result = drawMaze();
	vector<int> so = solveMaze();
	int curx = 0, cury = 0;
	for (unsigned x = 0; x < so.size(); x++) {
	for (int y = 0; y <= 10; y++) {
		switch(so[x]) {
			case(0): {
				HSLAPixel & p = result->getPixel(curx * 10 + 5 + y, cury * 10 + 5);
				p.l = 0.5;
				p.s = 1;
				p.h = 0;
				p.a = 1;
				if(y == 0) curx++;
				break;
			}
			case(1): {
				HSLAPixel & p = result->getPixel(curx * 10 + 5, cury * 10 + 5 + y);
				p.l = 0.5;
				p.s = 1;
				p.h = 0;
				p.a = 1;
				if(y == 0) cury++;			
				break;
			}
			case(2): {
				HSLAPixel & p = result->getPixel(curx * 10 + 5 - y, cury * 10 + 5);
				p.l = 0.5;
				p.s = 1;
				p.h = 0;
				p.a = 1;
				if(y == 0) curx--;				
				break;
			}
			case(3): {
				HSLAPixel & p = result->getPixel(curx * 10 + 5, cury * 10 + 5 - y);
				p.l = 0.5;
				p.s = 1;
				p.h = 0;
				p.a = 1;
				if(y == 0) cury--;				
				break;
			}
		}
	}			
	}
	for (int j = 0; j <= 10; j++) {
		HSLAPixel & p = result->getPixel(curx * 10 + j, (cury + 1) * 10);
		p.l = 1;
		p.s = 0;
	}	
	return result;
}
struct sq{
	int x;
	int y;
	sq(int p, int q) {
		x = p;
		y = q;
	}
};
vector<int> SquareMaze::solveMaze() {
	vector<int> result1, result;
	int * dis = new int[w * h];
	int * dir = new int[w * h];
	queue<pair<sq, sq>> q;
	for (int x = 0; x < w * h; x++) {
		dis[x] = -1;
		dir[x] = -1;
	}
	q.push(pair<sq, sq>(sq(0, 0), sq(0, 0)));
	while (!q.empty()) {
		pair<sq, sq> t = q.front();
		q.pop();
		int x = t.second.x, y = t.second.y;
		if (dis[x + y * w] != -1) continue;
		dis[x + y * w] = dis[t.first.x + t.second.y * w] + 1;
		if (x == t.first.x) {
			if (y - t.first.y == 1) {
				dir[x + y * w] = 1;
			} else {
				dir[x + y * w] = 3;
			}
		} else {
			if (x - t.first.x == 1) {
				dir[x + y * w] = 0;
			} else {
				dir[x + y * w] = 2;
			}
		}
		if (canTravel(x, y, 0) && dis[x + 1 + y * w] == -1) q.push(pair<sq, sq>(t.second, sq(x + 1, y)));
		if (canTravel(x, y, 1) && dis[x + w + y * w] == -1) q.push(pair<sq, sq>(t.second, sq(x, y + 1)));
		if (canTravel(x, y, 2) && dis[x - 1 + y * w] == -1) q.push(pair<sq, sq>(t.second, sq(x - 1, y)));
		if (canTravel(x, y, 3) && dis[x - w + y * w] == -1) q.push(pair<sq, sq>(t.second, sq(x, y - 1)));
	}
	int mo = -1, l = (h - 1) * w;
	for (int x = 0; x < w; x++) {
		if (dis[x + (h - 1) * w] > mo) {
			mo = dis[x + (h - 1) * w];
			l = x + (h - 1) * w;
		}
	}
	while(l != 0) {
		result1.push_back(dir[l]);
		switch(dir[l]) {
			case(0): {
				l -= 1;
				break;
			}
			case(1): {
				l -= w;
				break;
			}
			case(2): {
				l += 1;
				break;
		    }
			case(4): {
				l += w;
				break;
			} 
		}
	}
	for (unsigned x = 0; x < result1.size(); x++) result.push_back(result1[result1.size() - 1 - x]);
	delete[] dir;
	delete[] dis;
	return result;
}

