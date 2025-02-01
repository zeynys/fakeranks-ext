#ifndef _ranksclass_h
#define _ranksclass_h

#include <string>

class RanksClass
{
private:
    std::string plugin_name;

public:
    RanksClass(std::string m_plugin_name);

    void GetRankPoints(int playerid, int points);
    void GetRankSkillID(int playerid, int rank);
};

#endif