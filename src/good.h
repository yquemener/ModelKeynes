#ifndef GOOD_H
#define GOOD_H

#include <map>
#include <string>

using std::map;
using std::string;

namespace Econ
{

/// This describes an industrial good type
typedef int good_t;

/// Attributes a human readable name to (hopefully) every kind of goods
static map<good_t, string>& s_goodName()
{
  static map<good_t, string> gn;
  return gn;
}

}
#endif // GOOD_H
