#include "Status.h"

Status::Status() : iteration(0), money(STARTING_MONEY), current_message("")
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
  strftime(date_string, 100, "%b %Y", &date);
  return date_string;
}

#include <fstream>

void Status::save(std::ofstream& out) {
    out << money << "\n";
    out << iteration << "\n";
    out << date.tm_mon << "\n";
    out << date.tm_year << "\n";
}

void Status::load(std::ifstream& in) {
    std::string line;
    if (std::getline(in, line)) money = std::stoi(line);
    if (std::getline(in, line)) iteration = std::stoi(line);
    if (std::getline(in, line)) date.tm_mon = std::stoi(line);
    if (std::getline(in, line)) date.tm_year = std::stoi(line);
}

