This repo contains a generic A* search class which you can use to solve your favorite puzzles.
An example is provided which solves a hard Rush Hour puzzle

A description of the A* algorithm can be found here: 
https://en.wikipedia.org/wiki/A*_search_algorithm

About Rush Hour:
https://en.wikipedia.org/wiki/Rush_Hour_(board_game)

To use the class, include AStarSearch.hh and instantiate the Search class from there.
In order for the instantiation to work, you need to template it on two classes you need to implement, which are Position and Move. Position signifies the current state of the game, and move signifies a possible continuation from that position. The following methods should be implemented (and public):

Position::Position(const Position& prevPosition, const Move& move);
A constructor that advances the previous position by the given move. You might want to implement another constructor to get to the initial position.

bool Position::isSolved() const;
Returns whether the current position is a solution to the puzzle.

void Position::generateMoves(std::vector<Move>& output) const;
Generates a vector of possible moves from the position.

void Position::print() const;
A graphic display of the position, will be used to print the solution

double Position::PermissibleDistanceToSolution() const;
A vital part of the A* algorithm. This is a heuristic distance to solution that always returns a number which is smaller or equal to the true distance of the position from the solution. For example, in the Rush Hour implementation I used the number of blocking cars, in 15-puzzle the manhattan distance of all tiles from their goal location is a natural choice. Setting this function to return a constant will disable the heuristic nature of A* and make the algorithm perform a Dijkstra search.

bool operator< (const Position& lhs, const Position& rhs);
Used for storing information about the history of arrival at a given position. Needs to comply with the standard requirements of an ordering operator. Namely, trasitivity (x<y, y<z then x<z) and reflexivity (!(x<y)&!(y<x) => x==y).

double Move::cost() const;
The cost of move, the search will find the cheapest solution. Namely, a sequence of moves who arrive at a solved position and whose sum of costs is the lowest.



Enjoy.
