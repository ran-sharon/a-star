#pragma once

#include <vector>
#include <queue>
#include <map>

namespace AStar{

template <class Position, class Move>
class Node{
public:
    Node(const Position& initialPos);
    Node(const Node& prevNode, const Move& move);
    Position pos;
    std::vector<Move> movesToHere;
    double costToHere;
    double permissibleDistanceToSolution;
};

template<class Position, class Move>
bool operator<(const Node<Position,Move>& lhs, const Node<Position,Move>& rhs){
    // The reversal of the sign in the comparison causes the priority_queue to be min first instead of
    // max first.
    return (lhs.costToHere + lhs.permissibleDistanceToSolution) > 
              (rhs.costToHere + rhs.permissibleDistanceToSolution);
}

template <class Position, class Move>
class Search{
public:
    Search(const Position& initialPosition);
    void solve(std::vector<Move>& solution);
private:
    std::priority_queue<Node<Position,Move>> queue;
    std::map<Position, double> positionDiscoveryHistory;
    void exploreNewNode(const Node<Position, Move>& node);
    void printSolution(const std::vector<Move>& solution) const;
    const Position m_initialPos;
};
}

#include "AStarSearch.cc"

