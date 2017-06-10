#include <iostream>
#include <vector>
#include "RushHour.hh"
#include "AStarSearch.hh"

int main(){
    RushHour::Position pos;
    AStar::Search<RushHour::Position, RushHour::Move> search(pos);
    std::vector<RushHour::Move> solution;
    search.solve(solution);
    return 0;
}
