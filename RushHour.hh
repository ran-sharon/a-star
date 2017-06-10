#pragma once

#include<vector>

namespace RushHour{

constexpr int boardSize = 6;

class Vehicle{
public:
    int upperMost;
    int leftMost;
    bool isHorizontal;
    int length; 
    Vehicle(int _upperMost, int _leftMost, bool _isHorizontal, int _length) :
        upperMost(_upperMost), leftMost(_leftMost), isHorizontal(_isHorizontal),
        length(_length){}
};

class Move{
public:
    int vehicleIndex;
    int size;
    Move(int _vehicleIndex, int _size) :
        vehicleIndex(_vehicleIndex), size(_size) {}
    double cost() const {return 1;}
};

class Position{
public:
    Position();
    Position(const Position& prevPosition, const Move& move);
    bool isSolved() const;
    void generateMoves(std::vector<Move>& output) const;
    void print() const;
    double permissibleDistanceToSolution() const;
    const std::vector<Vehicle>& getVehicles() const {return vehicles;};
private:    
    std::vector<Vehicle> vehicles;
    bool isLegal() const;
    void createOccupancyGrid(int board[boardSize][boardSize]) const;
    void generateAllVehicleMoves(std::vector<Move>& output, std::vector<Vehicle>::const_iterator it) const;
};

bool operator< (const Position& lhs, const Position& rhs);
}
