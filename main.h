#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

struct puzzleNode{ //represents a board sequence
    public:
        puzzleNode();
        puzzleNode(vector<vector<int>> state);
        vector<vector<int>> currState; //represents the current state
        puzzleNode* parent = NULL; //represents the previous move 
        puzzleNode* child1 = NULL; //represents the possible moves: move blank up,left,right,down
        puzzleNode* child2 = NULL;
        puzzleNode* child3 = NULL;
        puzzleNode* child4 = NULL;
        int cost = 0; //cost same as depth
        double heurVal = 0;

};

class reverseQueue { //used to make a priority queue reversed [lowest value prioritized, highest is last out]
    public:
        bool operator()(puzzleNode* node1, puzzleNode* node2){
            if((node1->cost + node1->heurVal) > (node2->cost + node2->heurVal)){
                return true;
            } else {
                return false;
            }
        }
};

void performSearch(puzzleNode* rootPuzzle, int heurAlgo); //Best-first search
int uniformSearch(vector<vector<int>> board); //returns h(n) = 0 
int misplacedTileHeur(vector<vector<int>> board); //returns h(n) which counts the number of misplaced tiles
double euclideanDistanceHeur(vector<vector<int>> board); //returns h(n) which is the Euclidean distance
bool solvedPuzzle(vector<vector<int>> board);
void printGoalState(puzzleNode* node);

void topLeftMoves(puzzleNode* node); //pass in current Board and find possible moves from top row
void topMiddleMoves(puzzleNode* node);
void topRightMoves(puzzleNode* node);
void middleLeftMoves(puzzleNode* node); //pass in current Board and find possible moves from mid row
void middleMiddleMoves(puzzleNode* node);
void middleRightMoves(puzzleNode* node);
void botLeftMoves(puzzleNode* node); //pass in current Board and find possible moves from bottom row
void botMiddleMoves(puzzleNode* node);
void botRightMoves(puzzleNode* node);
void printCurrent(puzzleNode* node);
