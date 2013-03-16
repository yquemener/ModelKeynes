#include <sstream>
#include <string>
#include "bot.h"

#include <iostream>

using std::stringstream;
using std::string;

namespace Econ{

Bot::Bot(IndustrialNode* home)
{
  m_home = home;
  m_id = s_newId();
  (*s_idTable())[m_id] = this;
}

string Bot::displayStock()
{
  stringstream ss;
  ss << cash << " ";
  for(auto it=stock.begin(); it!=stock.end(); it++)
  {
    ss << "/" << it->second;
  }
  return ss.str();
}

}
