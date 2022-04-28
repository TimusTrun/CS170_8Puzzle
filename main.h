// class Problem{
//     public:
//         Problem(); //default constructor

//         //funcs:
//         void performSeach(); //performs the search algorithm based on which one is choosen (parameters: )
//         int uniformSearch(Problem); //returns h(n) = 0
//         int misplacedTileHeur(Problem); //returns ...
//         int euclideanDistanceHeur(Problem); //returns...
// };

struct puzzleNode{ //represents a board sequence
    public:
        puzzleNode();
        puzzleNode(state);
        vector<vector<int>> currState = NULL; //represents the current state
        puzzleNode* parent = NULL; //represents the previous move 
        puzzleNode* child1 = NULL; //represents the possible moves: move blank up,left,right,down
        puzzleNode* child2 = NULL;
        puzzleNode* child3 = NULL;
        puzzleNode* child4 = NULL;
        int depth = 0;
        int cost = 0;
}

void performSearch(puzzleNode rootPuzzle, int h); //Best-first search
int uniformSearch(vector<vector<int>> board); //returns h(n) = 0 
int misplacedTileHeur(vector<vector<int>> board); //returns h(n) which counts the number of misplaced tiles
int euclideanDistanceHeur(vector<vector<int>> board); //returns h(n) which is the Euclidean distance
