#include "bot.h"
namespace Econ{

Bot::Bot(IndustrialNode* home)
{
  m_home = home;
  m_id = s_newId();
  (*s_idTable())[m_id] = this;
}


}
