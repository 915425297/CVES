/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>
#include <cstring>
using namespace std;
/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    token = startingTokens;
    string s = to_string(startingTokens);
    startingVertex_ = "p1-" + s;
    g_.insertVertex(startingVertex_);
    Vertex p = "p2-" + s;
    g_.insertVertex(p);
    for (int x = startingTokens - 1; x >= 0; x--) {
    	s = to_string(x);
    	Vertex p1 = "p1-" + s;
    	Vertex p2 = "p2-" + s;
    	g_.insertVertex(p1);
    	g_.insertVertex(p2);
    	if ((unsigned) x + 1 <= startingTokens) {
    	Vertex p3 = "p1-" + to_string(x + 1);
    	g_.insertEdge(p3, p2);
		g_.setEdgeWeight(p3, p2, 0);	
    	p3 = "p2-" + to_string(x + 1);
    	g_.insertEdge(p3, p1);
    	g_.setEdgeWeight(p3, p1, 0);
		}
    	if ((unsigned) x + 2 <= startingTokens) {
    	Vertex p3 = "p1-" + to_string(x + 2);
    	g_.insertEdge(p3, p2);
		g_.setEdgeWeight(p3, p2, 0);	
    	p3 = "p2-" + to_string(x + 2);
    	g_.insertEdge(p3, p1);
    	g_.setEdgeWeight(p3, p1, 0);
		}
	}
	vector<Vertex> p2 = g_.getVertices();
	for (string g: p2) cout<<g<<endl;
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *+
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
  int x = token;
  Vertex p1 = "p1-" + to_string(token);
  int flag = rand() % 2 + 1;
  bool term = 0;
  while(x > 0) {
  	x-= flag;
  	if (x < 0) x = 0;
  	Vertex i;
  	if (!term) i = "p2-";
  	else i = "p1-";
  	term = !term;
	Vertex p2 = i + to_string(x);
  	flag = rand() % 2 + 1;
  	path.push_back(g_.getEdge(p1, p2));
  	p1 = p2;
  }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 	 // p1 won
 		for (unsigned x = 0; x < path.size(); x++) {
		 if (path[path.size() - 1].dest.compare("p2-0") == 0) {
 			if (path[x].source[1] == '1') {
 				g_.setEdgeWeight(path[x].source, path[x].dest, path[x].getWeight() + 1);
			} else {
 				g_.setEdgeWeight(path[x].source, path[x].dest, path[x].getWeight() - 1);
			}
			} else {
 			if (path[x].source[1] == '1') {
 				g_.setEdgeWeight(path[x].source, path[x].dest, path[x].getWeight() - 1);
			} else {
 				g_.setEdgeWeight(path[x].source, path[x].dest, path[x].getWeight() + 1);
			}				
			}
		 }
}


/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
