#include "Grid.h"

using std::vector;
using std::map;
using std::string;

#include "Constants.h"
#include "Cell.h"
#include "Cell_factory.h"

#include <string>

Grid::Grid()
{
  grid.resize(Y_SIZE);
  for (unsigned int y=0; y<grid.size(); ++y)
  {
    grid[y].resize(X_SIZE);
    for (unsigned int x=0; x<grid[y].size(); ++x)
    {
      grid[y][x] = Cell_factory::create_cell('x', y, x);
    }
  }
}

Grid::~Grid()
{
  for (unsigned int y=0; y<grid.size(); ++y)
  {
    for (unsigned int x=0; x<grid[y].size(); ++x)
    {
      delete(grid[y][x]);
    }
  }
}

std::string Grid::build(int y, int x, Cell* new_cell, Status& status)
{
  if (grid[y][x]->get_type() != LAND)
  {
    delete new_cell;
    return " Land must be clear ";
  }

  if (new_cell->get_price() > status.get_money())
  {
    delete new_cell;
    return " Not enough money ";
  }

  else
  {
    status.sub_money(new_cell->get_price());

    Cell* temp = grid[y][x];
    grid[y][x] = new_cell;
    delete temp;
             
    return "";
  }

}

std::string Grid::replace(int y, int x, Cell* new_cell)
{
  Cell* temp = grid[y][x];
  grid[y][x] = new_cell;
  delete temp;

  return "";
}

void Grid::collect_taxes(Status& status)
{
  for (int y=0; y<Y_SIZE; ++y)
  {
    for (int x=0; x<X_SIZE; ++x)
    {
      grid[y][x]->collect_taxes(status);
    }
  }
}

void Grid::pay_for_services(Status& status)
{
  for (int y=0; y<Y_SIZE; ++y)
  {
    for (int x=0; x<X_SIZE; ++x)
    {
      grid[y][x]->pay_for_services(status);
    }
  }
}

void Grid::calculate_land_values(map<string, Status_grid*>& status_grids)
{
  for (int y=0; y<Y_SIZE; ++y)
  {
    for (int x=0; x<X_SIZE; ++x)
    {
      grid[y][x]->calculate_land_values(status_grids);
    }
  }
}

void Grid::update_state()
{
  for (int y=0; y<Y_SIZE; ++y)
  {
    for (int x=0; x<X_SIZE; ++x)
    {
      grid[y][x]->update_state();
    }
  }
}

// Helper to map "Coal Power Plant" back to 'w', etc.
char map_type_to_cmd(std::string type) {
    if (type == RESIDENTIAL)         return 'r';
    if (type == COMMERCIAL)          return 'c';
    if (type == INDUSTRIAL)          return 'i';
    if (type == ROAD)                return 'o';
    if (type == RAIL)                return 'd';
    if (type == POLICE_STATION)      return 'p';
    if (type == FIRE_STATION)        return 'f';
    if (type == SCHOOL)              return 's';
    if (type == HOSPITAL)            return 'm';
    if (type == PARK)                return 'a';
    if (type == COAL_POWER_PLANT)    return 'w';
    if (type == NUCLEAR_POWER_PLANT) return 'n';
    return 'x'; // Default to Land
}

void Grid::save(std::ofstream& out) {
    for (int y = 0; y < Y_SIZE; ++y) {
        for (int x = 0; x < X_SIZE; ++x) {
            out << grid[y][x]->get_type() << "\n";
            out << grid[y][x]->get_state() << "\n";
        }
    }
}

void Grid::load(std::ifstream& in) {
    std::string type_name, state_str;
    for (int y = 0; y < Y_SIZE; ++y) {
        for (int x = 0; x < X_SIZE; ++x) {
            if (!std::getline(in, type_name)) break;
            if (!std::getline(in, state_str)) break;
            
            char cmd = map_type_to_cmd(type_name);
            Cell* new_cell = Cell_factory::create_cell(cmd, y, x);
            if (new_cell) {
                new_cell->set_state(std::stoi(state_str));
                delete grid[y][x]; // Clean up old memory
                grid[y][x] = new_cell;
            }
        }
    }
}
