#pragma once

#include <stdexcept>
#include <iostream>

namespace AStar{

template <class Position, class Move>
Node<Position, Move>::Node(const Position& initialPos) : 
                        pos(initialPos), costToHere(0), 
                        permissibleDistanceToSolution(initialPos.permissibleDistanceToSolution()){
    movesToHere.clear();
}

template <class Position, class Move>
Node<Position, Move>::Node(const Node& prevNode, const Move& move){
    *this = prevNode;
    pos = Position(prevNode.pos, move);
    movesToHere.push_back(move);
    costToHere += move.cost();
    permissibleDistanceToSolution = pos.permissibleDistanceToSolution();
}


template <class Position, class Move>
Search<Position, Move>::Search(const Position& initialPosition) : 
        m_initialPos(initialPosition){
    Node<Position,Move> node(initialPosition);
    queue.push(node);  
}

template <class Position, class Move>
void Search<Position, Move>::solve(std::vector<Move>& solution){
    while (!queue.empty()){
        Node<Position, Move> node = queue.top();
        queue.pop();
        if (node.pos.isSolved()){
            solution = node.movesToHere;
            printSolution(solution);
            return;
        }
        exploreNewNode(node); 
    }
    throw std::logic_error("Puzzle is unsolvable");
}

template <class Position, class Move>
void Search<Position, Move>::printSolution(const std::vector<Move>& solution) const{
    std::cout << "Found Solution:" << std::endl << std::endl;
    m_initialPos.print();
    Position pos = m_initialPos;
    std::cout << std::endl;
    for (auto moveIt = solution.cbegin(); moveIt != solution.cend(); ++moveIt){
        pos = Position(pos, *moveIt);
        pos.print();
        std::cout << std::endl;
    }
    std::cout << "Done" << std::endl;
}

template <class Position, class Move>
void Search<Position, Move>::exploreNewNode(const Node<Position,Move>& node){
    const Position& pos = node.pos;
    auto it = positionDiscoveryHistory.find(pos);
    bool alreadyFound = it != positionDiscoveryHistory.end(); 
    if (alreadyFound && ((*it).second <= node.costToHere)){
        return;
    }
    if (!alreadyFound)
        positionDiscoveryHistory.insert(std::pair<Position, double>(pos, node.costToHere));
    if  (alreadyFound && ((*it).second > node.costToHere)){
        (*it).second = node.costToHere;
    }
    std::vector<Move> availableMoves;
    pos.generateMoves(availableMoves);
    for (auto moveIt = availableMoves.cbegin(); moveIt != availableMoves.cend(); ++moveIt){
        queue.push(Node<Position,Move>(node, *moveIt));
    }

}

}
