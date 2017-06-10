#include <iterator>
#include <stdexcept>
#include <iostream>
#include "RushHour.hh"

namespace RushHour{

void verifySquareIsEmpty(int board[boardSize][boardSize], int x, int y);
void printLetter(int letter);

Position::Position(){
    vehicles.clear();
    vehicles.push_back(Vehicle(2,0,true,2));
    vehicles.push_back(Vehicle(0,0,false,2));
    vehicles.push_back(Vehicle(1,1,true,3));
    vehicles.push_back(Vehicle(0,2,true,2));
    vehicles.push_back(Vehicle(0,4,false,3));
    vehicles.push_back(Vehicle(3,1,false,2));
    vehicles.push_back(Vehicle(3,2,true,2));
    vehicles.push_back(Vehicle(4,2,false,2));
    vehicles.push_back(Vehicle(4,3,true,2));
    vehicles.push_back(Vehicle(2,5,false,3));
}

Position::Position(const Position& prevPosition, const Move& move){
    *this = prevPosition;
    Vehicle& v = vehicles[move.vehicleIndex];
    if (v.isHorizontal)
        v.leftMost += move.size;
    else
        v.upperMost += move.size;
}

double Position::permissibleDistanceToSolution() const{
    int board[boardSize][boardSize];
    createOccupancyGrid(board);
    double nBlockingVehicles = 0;
    int placeAfterFirstCar = vehicles[0].leftMost + vehicles[0].length;
    for (int i = placeAfterFirstCar; i < boardSize; i++)
        if (board[vehicles[0].upperMost][i] != -1)
            nBlockingVehicles++;
    return nBlockingVehicles;
}

bool Position::isSolved() const{
    return permissibleDistanceToSolution() == 0;
}

bool Position::isLegal() const{
    int board[boardSize][boardSize];
    try {
        createOccupancyGrid(board);
    }
    catch (const std::logic_error& e) {
        return false;
    }
    return true;
}

void Position::generateMoves(std::vector<Move>& output) const{
    output.clear();
    for (auto it = vehicles.cbegin(); it != vehicles.cend(); ++it){
        generateAllVehicleMoves(output, it);
    }
}

void Position::generateAllVehicleMoves(std::vector<Move>& output, std::vector<Vehicle>::const_iterator it) const{
    int iVehicle = std::distance(vehicles.cbegin(), it);
    for (int direction : {-1, 1}){
        int size = 1;
        while (true){
            Move move(iVehicle, size * direction);
            Position newPos(*this, move);
            if (newPos.isLegal()){
                output.push_back(move);
            }
            else{
                break;
            }
            size++;
        }
    }
}

void Position::createOccupancyGrid(int board[boardSize][boardSize]) const{
    for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
            board[i][j] = -1;
    for (auto it = vehicles.cbegin(); it != vehicles.cend(); ++it){
        int iVehicle = std::distance(vehicles.cbegin(), it);
        for(int iLength = 0; iLength < it->length; iLength++){
            int y = it->upperMost + (!(it->isHorizontal)) * iLength;
            int x = it->leftMost + (it->isHorizontal) * iLength;
            verifySquareIsEmpty(board, x, y);
            board[y][x] = iVehicle;
        }
         
    }
}

void verifySquareIsEmpty(int board[boardSize][boardSize], int x, int y){
    bool xInRange = (x >= 0) && (x < boardSize);
    if (!xInRange)
        throw std::logic_error("x out of range");
    bool yInRange = (y >= 0) && (y < boardSize);
    if (!yInRange)
        throw std::logic_error("y out of range");
    if (board[y][x] != -1)
        throw std::logic_error("Illegal Position");
}

void Position::print() const{
    int board[boardSize][boardSize];
    createOccupancyGrid(board);
    for (int i = 0; i < boardSize + 2; i++)
        std::cout << '-';
    std::cout << std::endl;
    for (int y = 0; y < boardSize; y++){
        std::cout << '|';
        for (int x = 0; x < boardSize; x++){
            printLetter(board[y][x]);
        }
        std::cout << '|' << std::endl;
    }
    for (int i = 0; i < boardSize + 2; i++)
        std::cout << '-';
    std::cout << std::endl;
    std::cout << std::endl;
    
}
    
void printLetter(int letter){
    char c;
    if (letter == -1){
        c = ' ';
    }
    else {
        if (letter == 0){
            c = 'X';
        } else {
            c = letter - 1 + 'A';
        }
    }
    std::cout << c;
}

bool operator< (const Position& lhs, const Position& rhs){
    const std::vector<Vehicle>& lVehicles = lhs.getVehicles();
    const std::vector<Vehicle>& rVehicles = rhs.getVehicles();
    if (lVehicles.size() != rVehicles.size()){
        throw std::logic_error("Trying to compare positions with different number of vehicles");
    }
    auto lIt = lVehicles.cbegin();
    auto rIt = rVehicles.cbegin();
    while((lIt != lVehicles.cend()) && (rIt != rVehicles.cend())){
        if (lIt->upperMost < rIt->upperMost){
            return true;
        }
        else{
            if (lIt->upperMost > rIt->upperMost){
                return false;
            }
        }
        if (lIt->leftMost < rIt->leftMost){
            return true;
        }
        else{
            if (lIt->leftMost > rIt->leftMost){
                return false;
            }
        }

        ++lIt;
        ++rIt;
    }
    return false;
}

}
