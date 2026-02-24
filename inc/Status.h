#ifndef STATUS_H
#define STATUS_H

#include "Constants.h"
#include <ctime>
#include <string>
using std::string;

#include <fstream>

class Status
{
  public:
    //~Status() {}
    Status();
    void set_message(std::string msg) { current_message = msg; }
    std::string get_message() const { return current_message; }

    void add_money(int amount) {money += amount;}
    void sub_money(int amount) {money -= amount;}
    int get_money() {return money;}

    void update_iteration() {++iteration;}
    int get_iteration() {return iteration;}

    void update_date();
    char* get_date();

    bool get_paused() const { return paused; }
    void set_paused(bool p) { paused = p; }
    string get_speed_label() const { return speed_label; }
    void set_speed_label(string s) { speed_label = s; }

    void save(std::ofstream& out);
    void load(std::ifstream& in);
  protected:

  private:
    std::tm date;
    int iteration;
    int money;

    bool paused;
    string speed_label;
    std::string current_message;
};

#endif
