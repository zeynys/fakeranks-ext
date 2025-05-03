#include "ranksclass.h"
#include "entrypoint.h"

extern std::map<int, int> points;
extern std::map<int, int> rank;

void SetupScripting(EContext* ctx)
{
    ADD_CLASS("RanksClass");

    ADD_CLASS_FUNCTION("RanksClass", "GetRankPoints", [](FunctionContext* context, ClassData* data) -> void {
        int playerid = context->GetArgumentOr<int>(0, 0);
        int player_points = context->GetArgumentOr<int>(1, 0);
        points[playerid] = player_points;
    });

    ADD_CLASS_FUNCTION("RanksClass", "GetRankSkillID", [](FunctionContext* context, ClassData* data) -> void {
        int playerid = context->GetArgumentOr<int>(0, 0);
        int player_rank = context->GetArgumentOr<int>(1, 0);
        rank[playerid] = player_rank;
    });

    ADD_VARIABLE("_G", "ranks", MAKE_CLASS_INSTANCE_CTX(ctx, "RanksClass", {}));
}
