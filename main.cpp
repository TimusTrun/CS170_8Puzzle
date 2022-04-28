using namespace std;
#include "main.h"
#include <iostream>
#include <vector>
#include <cmath>

int uniformSearch(vector<vector<int>> board){  //returning h(n) = 0
    return 0; 
}

int misplacedTileHeur(vector<vector<int>> board){ //returning h(n) based on wrong tile placement not including 0 (blank tile)
    int misplaced = 0;
    vector<vector<int>> goalBoard;
    goalBoard[0][0] = 1;
    goalBoard[0][1] = 2;
    goalBoard[0][2] = 3;
    goalBoard[1][0] = 4; // 1 2 3
    goalBoard[1][1] = 5; // 4 5 6
    goalBoard[1][2] = 6; // 7 8 0
    goalBoard[2][0] = 7;
    goalBoard[2][1] = 8;
    goalBoard[2][2] = 0;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (board[i][j] == 0){ //doesnt count for blank tile
                misplaced += 0;
            } else {
                if (board[i][j] != goalBoard[i][j]){ //checks if the current tile matches the goal tile, if doesnt match, mismatch++
                    misplaced++;
                }
            }
        }
    }
    return misplaced; //h(n) for misplaced tiles
}

int euclideanDistanceHeur(vector<vector<int>> board){ //returning h(n) based on euclidean distance
    int xVal;
    int yVal;
    double euclDist;
    for (int i = 0; i < 3; i++){ //row
        for (int j = 0; j < 3; j++){ //column
            if (board[i][j] == 0){ //dont count blank spot
                euclDist += 0; 
            } else if (board[i][j] == 1){
                if (i == 0){xVal = 0;} //calculating how many moves in x-dir
                else if (i == 1){xVal = 1;}
                else if (i == 2){xVal = 2;}
                if (j == 0){yVal = 0;}
                else if (j == 1){yVal = 1;}
                else if (j == 2){yVal = 2;}
            } else if (board[i][j] == 2){
                if (i == 0){xVal = 1;}
                else if (i == 1){xVal = 0;}
                else if (i == 2){xVal = 1;}
                if (j == 0){yVal = 0;}
                else if (j == 1){yVal = 1;}
                else if (j == 2){yval = 2;}
            } else if (board[i][j] == 3){
                if (i == 0){xVal = 2;}
                else if (i == 1){xVal = 1;}
                else if (i == 2){xVal = 0;}
                if (j == 0){yVal = 0;}
                else if (j == 1){yVal = 1;}
                else if (j == 2){yval = 2;}
            } else if (board[i][j] == 4){
                if (i == 0){xVal = 0;}
                else if (i == 1){xVal = 1;}
                else if (i == 2){xVal = 2;}
                if (j == 0){yVal = 1;}
                else if (j == 1){yVal = 0;}
                else if (j == 2){yval = 1;}
            } else if (board[i][j] == 5){
                if (i == 0){xVal = 1;}
                else if (i == 1){xVal = 0;}
                else if (i == 2){xVal = 1;}
                if (j == 0){yVal = 1;}
                else if (j == 1){yVal = 0;}
                else if (j == 2){yval = 1;}
            } else if (board[i][j] == 6){
                if (i == 0){xVal = 2;}
                else if (i == 1){xVal = 1;}
                else if (i == 2){xVal = 0;}
                if (j == 0){yVal = 1;}
                else if (j == 1){yVal = 0;}
                else if (j == 2){yval = 1;}
            } else if (board[i][j] == 7){
                if (i == 0){xVal = 0;}
                else if (i == 1){xVal = 1;}
                else if (i == 2){xVal = 2;}
                if (j == 0){yVal = 2;}
                else if (j == 1){yVal = 1;}
                else if (j == 2){yval = 0;}
            } else if (board[i][j] == 8){
                if (i == 0){xVal = 1;}
                else if (i == 1){xVal = 0;}
                else if (i == 2){xVal = 1;}
                if (j == 0){yVal = 2;}
                else if (j == 1){yVal = 1;}
                else if (j == 2){yval = 0;}
            }
            euclDist += sqrt((xVal*xVal) + (yVal*yVal)); //sqrt(x^2 + y^2)
        }
    }
    return euclDist;
}

void performSearch(vector<vector<int>> board, double h){ //1 = uni, 2 = misplaced, 3 = euclidean, h = heuristic val

}

puzzleNode::puzzleNode(){
    this.state = NULL;
    this.parent = NULL;
    this.child1 = NULL;
    this.child2 = NULL;
    this.child3 = NULL;
    this.child4 = NULL;
    this.depth = 0;
    this.cost = 0;
}

puzzleNode::puzzleNode(vector<vector<int>> currState){
    this.currState = currState;
    this.parent = NULL;
    this.child1 = NULL;
    this.child2 = NULL;
    this.child3 = NULL;
    this.child4 = NULL;
    this.depth = 0;
    this.cost = 0;
}

int main(){
    int puzzleType; //default or custom
    vector<vector<int>> board;
    cout<< "Which puzzle would you like? (1 = default and 2 = custom)"; //Setting up puzzle board and choosing an algorithm [doesn't error check boards though]
    cin>> puzzleType;
    if (puzzleType == 1){
        board[0][0] = 1; board[0][1] = 0; board[0][2] = 3;
        board[1][0] = 4; board[1][1] = 2; board[1][2] = 6;
        board[2][0] = 7; board[2][1] = 5; board[2][2] = 8;

        cout << "Your resulting board is: \n 1 0 3 \n 4 2 6 \n 7 5 8";

        int algo;
        int hVal;
        cout << "Which algorithm would you like to run on the puzzle? 1 = Uniform Search\n 2 = A* Misplaced Tiles Search\n 3 = A* Euclidean Distance Search";
        cin >> algo;
        if (algo == 1){
            hVal = uniformSearch(board);
        } else if (algo == 2){
            hVal = misplacedTileHeur(board);
        } else if (algo == 3){
            hVal = euclideanDistanceHeur(board);
        }

        puzzleNode* initialBoard = new puzzleNode(board);
        performSearch(initialBoard, hVal); //passes in the board with its hVal
        return 0;

    } else if (puzzleType == 2){
        int slot1, slot2, slot3;
        cout << "Input your values for the first row. 0 represents the blank tile. Use values 1-8 only once each";
        cout << "Use a space to separate the three first tiles (ex. 1 2 3)";
        cin >> slot1;
        cin >> slot2;
        cin >> slot3;
        board[0][0] = slot1; board[0][1] = slot2; board[0][2] = slot3;
        
        cout << "Your current board is: \n" << slot1 << " " << slot2 << " " << slot3 << "\n"
                                            << "x x x \n"
                                            << "x x x";
        int slot4, slot5, slot6;
        cout << "Input your values for the second row. "
        cin >> slot4;
        cin >> slot5;
        cin >> slot6;
        board[1][0] = slot4; board[1][1] = slot5; board[1][2] = slot6;

        cout << "Your current board is: \n" << slot1 << " " << slot2 << " " << slot3 << "\n"
                                            << slot4 << " " << slot5 << " " << slot6 << "\n"
                                            << "x x x";
        int slot7, slot8, slot9;
        cout << "Input your values for the third row. "
        cin >> slot7;
        cin >> slot8;
        cin >> slot9;
        board[2][0] = slot7; board[2][1] = slot8; board[2][2] = slot9;

        cout << "Your resulting board is: \n" << slot1 << " " << slot2 << " " << slot3 << "\n"
                                            << slot4 << " " << slot5 << " " << slot6 << "\n"
                                            << slot7 << " " << slot8 << " " << slot9;
    
        int algo;
        int hVal;
        cout << "Which algorithm would you like to run on the puzzle? 1 = Uniform Search\n 2 = A* Misplaced Tiles Search\n 3 = A* Euclidean Distance Search";
        cin >> algo;
        if (algo == 1){
            hVal = uniformSearch(board);
        } else if (algo == 2){
            hVal = misplacedTileHeur(board);
        } else if (algo == 3){
            hVal = euclideanDistanceHeur(board);
        }

        puzzleNode initialBoard = new puzzleNode(board);
        performSearch(initialBoard, hVal); //passes in the board with its hVal
        return 0;

    }
    return 0;
}