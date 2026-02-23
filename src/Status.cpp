#include "Status.h"

Status::Status() : iteration(0), money(STARTING_MONEY) 
{
  date.tm_mon = 0;
  date.tm_year = 0;

  paused = false;
  speed_label = ">";
}

void Status::update_date()
{
  ++(date.tm_mon);
  if (date.tm_mon == 12)
  {
    date.tm_mon = 0;
    ++(date.tm_year);
  }
}

char* Status::get_date()
{
  char* date_string = new char[100];
  strftime(date_string, 100, "%b %Y\0", &date);
  return date_string;
}

#include <fstream>

void Status::save(std::ofstream& out) {
    // Save in a specific order, one per line for the V3 Vertical style
    out << money << "\n";
    out << iteration << "\n";
    // Add any others from your Status.h (year, month, etc.)
    out << date.tm_mon << "\n";
    out << date.tm_year << "\n";
}

void Status::load(std::ifstream& in) {
    std::string line;
    // Load money
    if (std::getline(in, line)) money = std::stoi(line);
    // Load iteration
    if (std::getline(in, line)) iteration = std::stoi(line);
    if (std::getline(in, line)) date.tm_mon = std::stoi(line);
    if (std::getline(in, line)) date.tm_year = std::stoi(line);
}

