#include "ranksclass.h"
#include "entrypoint.h"

extern std::map<int, int> points;
extern std::map<int, int> rank;

RanksClass::RanksClass(std::string m_plugin_name)
{
    this->plugin_name = m_plugin_name;
}

void RanksClass::GetRankPoints(int playerid, int player_points)
{
    points[playerid] = player_points;
}

void RanksClass::GetRankSkillID(int playerid, int player_rank)
{
    rank[playerid] = player_rank;
}