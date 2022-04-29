#include "main.h"
//TO DO: double check my Euclidean function and run it
int expandedNodes = 0; //keeps track of the amount of puzzleNodes expanded
int maxQSize = 0; //refers to maximum size of the frontier

void printGoalState(puzzleNode* node){
    cout<< "\nWe found the goal state!\nThe depth is " << node->cost << "!\n";
    cout<< "We also expanded " << expandedNodes << " nodes!\n";
    cout<< "The max queue size was " << maxQSize << "!\n";
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << node->currState[i][j];
        }
        cout <<"\n";
    }
}

void printCurrent(puzzleNode* node){
    cout<< "\nThis is the current state we are at.\n";
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << node->currState[i][j];
        }
        cout <<"\n";
    }
    cout<< "This state's current depth is " << node->cost << " with a heuristic cost of " << node->heurVal << endl;
}

bool solvedPuzzle(vector<vector<int>> board){
    vector<vector<int>> goalBoard;
    vector<int> temp;
    temp = {1, 2, 3};
    goalBoard.push_back(temp);
    temp = {4, 5, 6};
    goalBoard.push_back(temp);
    temp = {7, 8, 0};
    goalBoard.push_back(temp);

    if (board == goalBoard){
        return true;
    } else {
        return false;
    }
}

int uniformSearch(vector<vector<int>> board){  //returning h(n) = 0
    return 0; 
}

int misplacedTileHeur(vector<vector<int>> board){ //returning h(n) based on wrong tile placement not including 0 (blank tile)
    int misplaced = 0;
    vector<vector<int>> goalBoard;
    vector<int> temp;
    temp = {1, 2, 3};
    goalBoard.push_back(temp);
    temp = {4, 5, 6};
    goalBoard.push_back(temp);
    temp = {7, 8, 0};
    goalBoard.push_back(temp);

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

double euclideanDistanceHeur(vector<vector<int>> board){ //returning h(n) based on euclidean distance
    int xVal = 0;
    int yVal = 0;
    double euclDist = 0;
    for (int i = 0; i < 3; i++){ //row
        for (int j = 0; j < 3; j++){ //column
            if (board[i][j] == 0){ //dont count blank spot
                xVal = 0;
                yVal = 0;
                euclDist += 0; 
            } else if (board[i][j] == 1){
                if (i == 0){yVal = 0;} //calculating how many moves in x-dir
                else if (i == 1){yVal = 1;}
                else if (i == 2){yVal = 2;}
                if (j == 0){xVal = 0;}
                else if (j == 1){xVal = 1;}
                else if (j == 2){xVal = 2;}
            } else if (board[i][j] == 2){
                if (i == 0){yVal = 0;}
                else if (i == 1){yVal = 1;}
                else if (i == 2){yVal = 2;}
                if (j == 0){xVal = 1;}
                else if (j == 1){xVal = 0;}
                else if (j == 2){xVal = 1;}
            } else if (board[i][j] == 3){
                if (i == 0){yVal = 0;}
                else if (i == 1){yVal = 1;}
                else if (i == 2){yVal = 2;}
                if (j == 0){xVal = 2;}
                else if (j == 1){xVal = 1;}
                else if (j == 2){xVal = 0;}
            } else if (board[i][j] == 4){
                if (i == 0){yVal = 1;}
                else if (i == 1){yVal = 0;}
                else if (i == 2){yVal = 1;}
                if (j == 0){xVal = 0;}
                else if (j == 1){xVal = 1;}
                else if (j == 2){xVal = 2;}
            } else if (board[i][j] == 5){
                if (i == 0){yVal = 1;}
                else if (i == 1){yVal = 0;}
                else if (i == 2){yVal = 1;}
                if (j == 0){xVal = 1;}
                else if (j == 1){xVal = 0;}
                else if (j == 2){xVal = 1;}
            } else if (board[i][j] == 6){
                if (i == 0){yVal = 1;}
                else if (i == 1){yVal = 0;}
                else if (i == 2){yVal = 1;}
                if (j == 0){xVal = 2;}
                else if (j == 1){xVal = 1;}
                else if (j == 2){xVal = 0;}
            } else if (board[i][j] == 7){
                if (i == 0){yVal = 2;}
                else if (i == 1){yVal = 1;}
                else if (i == 2){yVal = 0;}
                if (j == 0){xVal = 0;}
                else if (j == 1){xVal = 1;}
                else if (j == 2){xVal = 2;}
            } else if (board[i][j] == 8){
                if (i == 0){yVal = 2;}
                else if (i == 1){yVal = 1;}
                else if (i == 2){yVal = 0;}
                if (j == 0){xVal = 1;}
                else if (j == 1){xVal = 0;}
                else if (j == 2){xVal = 1;}
            }
            euclDist += sqrt((xVal*xVal) + (yVal*yVal)); //sqrt(x^2 + y^2)
        }
    }
    return euclDist;
}

void topLeftMoves(puzzleNode* node){
    //at top left, the blank can move in 2 directions, make 2 children
    // 0 1 2
    // 3 4 5
    // 6 7 8
    puzzleNode* child1 = new puzzleNode(node->currState); //move blank down
    child1->currState[0][0] = node->currState[1][0];
    child1->currState[1][0] = node->currState[0][0];
    child1->cost = node->cost + 1;

    puzzleNode* child2 = new puzzleNode(node->currState); //move blank right
    child2->currState[0][0] = node->currState[0][1];
    child2->currState[0][1] = node->currState[0][0];
    child2->cost = node->cost + 1;

    //assign children to node's children pointers 1,2
    node->child1 = child1;
    node->child2 = child2;
    node->child3 = NULL;
    node->child4 = NULL;
} 
void topMiddleMoves(puzzleNode* node){
    //at top middle, the blank can move in 3 directions, make 3 children
    // 1 0 2
    // 3 4 5
    // 6 7 8
    puzzleNode* child1 = new puzzleNode(node->currState); //move blank left
    child1->currState[0][0] = node->currState[0][1];
    child1->currState[0][1] = node->currState[0][0];
    child1->cost = node->cost + 1;

    puzzleNode* child2 = new puzzleNode(node->currState); //move down
    child2->currState[1][1] = node->currState[0][1];
    child2->currState[0][1] = node->currState[1][1];
    child2->cost = node->cost + 1;

    puzzleNode* child3 = new puzzleNode(node->currState); //move right
    child3->currState[0][1] = node->currState[0][2];
    child3->currState[0][2] = node->currState[0][1];
    child3->cost = node->cost + 1;

    //assign children to node's children pointers 1,2,3
    node->child1 = child1;
    node->child2 = child2;
    node->child3 = child3;
    node->child4 = NULL;

}
void topRightMoves(puzzleNode* node){
    //at top right, the blank can move in 2 directions, make 2 children
    // 1 2 0
    // 3 4 5
    // 6 7 8
    puzzleNode* child1 = new puzzleNode(node->currState); //move blank left
    child1->currState[0][1] = node->currState[0][2];
    child1->currState[0][2] = node->currState[0][1];
    child1->cost += 1;
    child1->cost = node->cost + 1;

    puzzleNode* child2 = new puzzleNode(node->currState); //move blank down
    child2->currState[0][2] = node->currState[1][2];
    child2->currState[1][2] = node->currState[0][2];
    child2->cost += 1;
    child2->cost = node->cost + 1;

    //assign children to node's children pointers 1,2
    node->child1 = child1;
    node->child2 = child2;
    node->child3 = NULL;
    node->child4 = NULL;
}
void middleLeftMoves(puzzleNode* node){
    //at middle left, the blank can move in 3 directions, make 3 children
    // 3 1 2
    // 0 4 5
    // 6 7 8
    puzzleNode* child1 = new puzzleNode(node->currState); //move blank up
    child1->currState[0][0] = node->currState[1][0];
    child1->currState[1][0] = node->currState[0][0];
    child1->cost = node->cost + 1;

    puzzleNode* child2 = new puzzleNode(node->currState); //move right
    child2->currState[1][1] = node->currState[0][1];
    child2->currState[0][1] = node->currState[1][1];
    child2->cost = node->cost + 1;

    puzzleNode* child3 = new puzzleNode(node->currState); //move down
    child3->currState[0][1] = node->currState[0][2];
    child3->currState[0][2] = node->currState[0][1];
    child3->cost = node->cost + 1;

    //assign children 1 2 3
    node->child1 = child1;
    node->child2 = child2;
    node->child3 = child3;
    node->child4 = NULL;

}
void middleMiddleMoves(puzzleNode* node){
    //at top left, the blank can move in 4 directions, make 4 children
    // 4 1 2
    // 3 0 5
    // 6 7 8
    puzzleNode* child1 = new puzzleNode(node->currState); //move blank left
    child1->currState[1][0] = node->currState[1][1];
    child1->currState[1][1] = node->currState[1][0];
    child1->cost = node->cost + 1;

    puzzleNode* child2 = new puzzleNode(node->currState); //move up
    child2->currState[1][1] = node->currState[0][1];
    child2->currState[0][1] = node->currState[1][1];
    child2->cost = node->cost + 1;

    puzzleNode* child3 = new puzzleNode(node->currState); //move right
    child3->currState[1][1] = node->currState[1][2];
    child3->currState[1][2] = node->currState[1][1];
    child3->cost = node->cost + 1;

    puzzleNode* child4 = new puzzleNode(node->currState); //move down
    child4->currState[2][1] = node->currState[1][1];
    child4->currState[1][1] = node->currState[2][1];
    child4->cost = node->cost + 1;

    //assign children 1,2,3,4
    node->child1 = child1;
    node->child2 = child2;
    node->child3 = child3;
    node->child4 = child4;

}
void middleRightMoves(puzzleNode* node){
    //at middle right, the blank can move in 3 directions, make 3 children
    // 5 1 2
    // 3 4 0
    // 6 7 8

    puzzleNode* child1 = new puzzleNode(node->currState); //move blank left
    child1->currState[1][1] = node->currState[1][2];
    child1->currState[1][2] = node->currState[1][1];
    child1->cost = node->cost + 1;

    puzzleNode* child2 = new puzzleNode(node->currState); //move up
    child2->currState[1][2] = node->currState[0][2];
    child2->currState[0][2] = node->currState[1][2];
    child2->cost = node->cost + 1;

    puzzleNode* child3 = new puzzleNode(node->currState); //move down
    child3->currState[2][2] = node->currState[1][2];
    child3->currState[1][2] = node->currState[2][2];
    child3->cost = node->cost + 1;

    //assign children 1 2 3
    node->child1 = child1;
    node->child2 = child2;
    node->child3 = child3;
    node->child4 = NULL; 

}
void botLeftMoves(puzzleNode* node){
    //at bot left, the blank can move in 2 directions, make 2 children
    // 6 1 2
    // 3 4 5
    // 0 7 8
    puzzleNode* child1 = new puzzleNode(node->currState); //move blank up
    child1->currState[1][0] = node->currState[2][0];
    child1->currState[2][0] = node->currState[1][0];
    child1->cost = node->cost + 1;

    puzzleNode* child2 = new puzzleNode(node->currState); //move right
    child2->currState[2][0] = node->currState[2][1];
    child2->currState[2][1] = node->currState[2][0];
    child2->cost = node->cost + 1;

    //assign children 1 2
    node->child1 = child1;
    node->child2 = child2;
    node->child3 = NULL;
    node->child4 = NULL;

}
void botMiddleMoves(puzzleNode* node){
    //at bot middle, the blank can move in 3 directions, make 3 children
    // 6 1 2
    // 3 4 5
    // 7 0 8
    puzzleNode* child1 = new puzzleNode(node->currState); //move blank left
    child1->currState[2][0] = node->currState[2][1];
    child1->currState[2][1] = node->currState[2][0];
    child1->cost = node->cost + 1;

    puzzleNode* child2 = new puzzleNode(node->currState); //move up
    child2->currState[1][1] = node->currState[2][1];
    child2->currState[2][1] = node->currState[1][1];
    child2->cost = node->cost + 1;

    puzzleNode* child3 = new puzzleNode(node->currState); //move right
    child3->currState[2][2] = node->currState[2][1];
    child3->currState[2][1] = node->currState[2][2];
    child3->cost = node->cost + 1;

    //assign children 1 2 3
    node->child1 = child1;
    node->child2 = child2;
    node->child3 = child3;
    node->child4 = NULL;

}
void botRightMoves(puzzleNode* node){
    //at bot right, the blank can move in 2 directions, make 2 children
    // 6 1 2
    // 3 4 5
    // 8 7 0
    puzzleNode* child1 = new puzzleNode(node->currState); //move blank left
    child1->currState[2][1] = node->currState[2][2];
    child1->currState[2][2] = node->currState[2][1];
    child1->cost = node->cost + 1;

    puzzleNode* child2 = new puzzleNode(node->currState); //move up
    child2->currState[2][2] = node->currState[1][2];
    child2->currState[1][2] = node->currState[2][2];
    child2->cost = node->cost + 1;

    //assign children 1 2
    node->child1 = child1;
    node->child2 = child2;
    node->child3 = NULL;
    node->child4 = NULL;
}

void performSearch(puzzleNode* rootPuzzle, int hAlgo){ //1 = uni, 2 = misplaced, 3 = euclidean, h = heuristic val
    puzzleNode* currNode = rootPuzzle; //node <- Node(state = problem.initial)
    if (hAlgo == 1){ currNode->heurVal = 0;}//calculating initial h(n) based off of the chosen algorithm
    else if (hAlgo == 2){ currNode->heurVal = misplacedTileHeur(currNode->currState); }
    else if (hAlgo == 3){ currNode->heurVal = euclideanDistanceHeur(currNode->currState); }
    priority_queue<puzzleNode*, vector<puzzleNode*>, reverseQueue> frontier; //nodelist????
    vector<vector<vector<int>>> boardList; //list of boards that have been expanded to already to makes sure we dont push boards that already occurred 
    frontier.push(currNode); //priority queue pushes back the root
    maxQSize = frontier.size();
    boardList.push_back(currNode->currState); //starting node in the explored list
    int zeroLoc;
    int tempLoc;
    expandedNodes = 0;

    while (!frontier.empty()){
        zeroLoc = -1; //reset so we can look for the location of the blank slot (012345678)
        tempLoc = 0;
        currNode = frontier.top();
        frontier.pop();
        printCurrent(currNode);
        expandedNodes++;
        if (solvedPuzzle(currNode->currState)){printGoalState(currNode); break;}
        //expand nodes (find where the 0 {blank} is)
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (currNode->currState[i][j] == 0){ zeroLoc = tempLoc; } 
                else { tempLoc++; }
            }
        } //expand nodes (find where the 0 {blank} is)
        //now expand based on 0 location and give children heuristic values
        if (zeroLoc == 0){
            topLeftMoves(currNode);
        } else if (zeroLoc == 1){
            topMiddleMoves(currNode);
        } else if (zeroLoc == 2){
            topRightMoves(currNode);
        } else if (zeroLoc == 3){
            middleLeftMoves(currNode);
        } else if (zeroLoc == 4){
            middleMiddleMoves(currNode);
        } else if (zeroLoc == 5){
            middleRightMoves(currNode);
        } else if (zeroLoc == 6){
            botLeftMoves(currNode);
        } else if (zeroLoc == 7){
            botMiddleMoves(currNode);
        } else if (zeroLoc == 8){
            botRightMoves(currNode);
        } else if (zeroLoc >= 9 || zeroLoc ==-1){
            cout << "The board is not valid!";
            break;
        } //now expand based on 0 location and give children heuristic values
        if(currNode->child1 != NULL){ //check which childrens exist and assign a heur value to them
            if(hAlgo == 1){currNode->child1->heurVal = uniformSearch(currNode->child1->currState);}
            else if (hAlgo == 2){currNode->child1->heurVal = misplacedTileHeur(currNode->child1->currState);}
            else if (hAlgo == 3){currNode->child1->heurVal = euclideanDistanceHeur(currNode->child1->currState);}
        }
        if(currNode->child2 != NULL){
            if(hAlgo == 1){currNode->child2->heurVal = uniformSearch(currNode->child2->currState);}
            else if (hAlgo == 2){currNode->child2->heurVal = misplacedTileHeur(currNode->child2->currState);}
            else if (hAlgo == 3){currNode->child2->heurVal = euclideanDistanceHeur(currNode->child2->currState);}  
        }
        if(currNode->child3 != NULL){
            if(hAlgo == 1){currNode->child3->heurVal = uniformSearch(currNode->child3->currState);}
            else if (hAlgo == 2){currNode->child3->heurVal = misplacedTileHeur(currNode->child3->currState);}
            else if (hAlgo == 3){currNode->child3->heurVal = euclideanDistanceHeur(currNode->child3->currState);}
        }
        if(currNode->child4 != NULL){
            if(hAlgo == 1){currNode->child4->heurVal = uniformSearch(currNode->child4->currState);}
            else if (hAlgo == 2){currNode->child4->heurVal = misplacedTileHeur(currNode->child4->currState);}
            else if (hAlgo == 3){currNode->child4->heurVal = euclideanDistanceHeur(currNode->child4->currState);}
        }  //check which childrens exist and assign a heur value to them

        //Check children to see if they are already discovered, if already discovered: dont do anything
        //                                                      if not already discovered: add to frontier, and discovered list
        if (currNode->child1 != NULL){ //child 1 check if exists
            bool exist1 = false; //doesnt exists yet
            for (vector<vector<int>> board : boardList){
                if (board == currNode->child1->currState) { exist1 = true; break;} //already discovered, just ignore this node
            }
            if (!exist1){ //board not discovered yet, add to frontier and list of discovered nodes
                frontier.push(currNode->child1);
                if(frontier.size() > maxQSize){
                    maxQSize = frontier.size();
                }
                boardList.push_back(currNode->child1->currState);
            }
        }

        if (currNode->child2 != NULL){ //child 2 check if exists
            bool exist2 = false; //doesnt exists yet
            for (vector<vector<int>> board : boardList){
                if (board == currNode->child2->currState) { exist2 = true; break;} //already discovered, just ignore this node
            }
            if (!exist2){ //board not discovered yet, add to frontier and list of discovered nodes
                frontier.push(currNode->child2);
                if(frontier.size() > maxQSize){
                    maxQSize = frontier.size();
                }
                boardList.push_back(currNode->child2->currState);
            }
        }

        if (currNode->child3 != NULL){ //child 3 check if exists
            bool exist3 = false; //doesnt exists yet
            for (vector<vector<int>> board : boardList){
                if (board == currNode->child3->currState) { exist3 = true; break;} //already discovered, just ignore this node
            }
            if (!exist3){ //board not discovered yet, add to frontier and list of discovered nodes
                frontier.push(currNode->child3);
                if(frontier.size() > maxQSize){
                    maxQSize = frontier.size();
                }
                boardList.push_back(currNode->child3->currState);
            }
        }

        if (currNode->child4 != NULL){ //child 4 check if exists
            bool exist4 = false; //doesnt exists yet
            for (vector<vector<int>> board : boardList){
                if (board == currNode->child4->currState) { exist4 = true; break;} //already discovered, just ignore this node
            }
            if (!exist4){ //board not discovered yet, add to frontier and list of discovered nodes
                frontier.push(currNode->child4);
                if(frontier.size() > maxQSize){
                    maxQSize = frontier.size();
                }
                boardList.push_back(currNode->child4->currState);
            }
        }
        //Check children to see if they are already discovered, DONE
    }
}

puzzleNode::puzzleNode(){
    this->currState;
    this->parent = NULL;
    this->child1 = NULL;
    this->child2 = NULL;
    this->child3 = NULL;
    this->child4 = NULL;
    this->cost = 0;
    this->heurVal = 0;
}

puzzleNode::puzzleNode(vector<vector<int>> currState){
    this->currState = currState;
    this->parent = NULL;
    this->child1 = NULL;
    this->child2 = NULL;
    this->child3 = NULL;
    this->child4 = NULL;
    this->cost = 0;
    this->heurVal = 0;
}

int main(){
    int puzzleType; //default or custom
    vector<vector<int>> board;
    vector<int> temp;
    cout<< "Which puzzle would you like? (1 = default and 2 = custom)\n"; //Setting up puzzle board and choosing an algorithm [doesn't error check boards though]
    cin >> puzzleType;
    if (puzzleType == 1){
        temp = {1, 0, 3};
        board.push_back(temp);
        temp = {4, 2, 6};
        board.push_back(temp);
        temp = {7, 5, 8};
        board.push_back(temp);
        // board[0][0] = 1; 
        // board[0][1] = 0; 
        // board[0][2] = 3;
        // board[1][0] = 4; 
        // board[1][1] = 2; 
        // board[1][2] = 6;
        // board[2][0] = 7; 
        // board[2][1] = 5; 
        // board[2][2] = 8;

        cout << "Your resulting board is: \n 1 0 3 \n 4 2 6 \n 7 5 8\n";

        int algo;
        int hVal;
        cout << "Which algorithm would you like to run on the puzzle?\n 1 = Uniform Search\n 2 = A* Misplaced Tiles Search\n 3 = A* Euclidean Distance Search\n";
        cin >> algo;


        puzzleNode* initialBoard = new puzzleNode(board); //does it have to be a pointer?
        performSearch(initialBoard, algo); //passes in the board with the chosen algorithm
        return 0;

    } else if (puzzleType == 2){
        int slot1, slot2, slot3;
        cout << "Input your values for the first row. 0 represents the blank tile. Use values 1-8 only once each\n";
        cout << "Use a space to separate the three first tiles (ex. 1 2 3)\n";
        cin >> slot1;
        cin >> slot2;
        cin >> slot3;
        //board[0][0] = slot1; board[0][1] = slot2; board[0][2] = slot3;
        temp = {slot1, slot2, slot3};
        board.push_back(temp);
        cout << "Your current board is: \n" << slot1 << " " << slot2 << " " << slot3 << "\n"
                                            << "x x x \n"
                                            << "x x x\n";
        int slot4, slot5, slot6;
        cout << "Input your values for the second row.\n";
        cin >> slot4;
        cin >> slot5;
        cin >> slot6;
        // board[1][0] = slot4; board[1][1] = slot5; board[1][2] = slot6;
        temp = {slot4, slot5, slot6};
        board.push_back(temp);
        cout << "Your current board is: \n" << slot1 << " " << slot2 << " " << slot3 << "\n"
                                            << slot4 << " " << slot5 << " " << slot6 << "\n"
                                            << "x x x\n";
        int slot7, slot8, slot9;
        cout << "Input your values for the third row. \n";
        cin >> slot7;
        cin >> slot8;
        cin >> slot9;
        // board[2][0] = slot7; board[2][1] = slot8; board[2][2] = slot9;
        temp = {slot7, slot8, slot9};
        board.push_back(temp);
        cout << "Your resulting board is: \n" << slot1 << " " << slot2 << " " << slot3 << "\n"
                                            << slot4 << " " << slot5 << " " << slot6 << "\n"
                                            << slot7 << " " << slot8 << " " << slot9 << "\n";
    
        int algo;
        int hVal;
        cout << "Which algorithm would you like to run on the puzzle?\n 1 = Uniform Search\n 2 = A* Misplaced Tiles Search\n 3 = A* Euclidean Distance Search\n";
        cin >> algo;


        puzzleNode* initialBoard = new puzzleNode(board);
        performSearch(initialBoard, algo); //passes in the board with its hVal
        return 0;

    }
    return 0;
}