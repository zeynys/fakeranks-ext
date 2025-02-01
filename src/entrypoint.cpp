#include "entrypoint.h"
#include "ranksclass.h"
#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>
#include <LuaBridge/LuaBridge.h>
#include <ehandle.h>
#include <swiftly-ext/config.h>

#include <swiftly-ext/sdk.h>

//////////////////////////////////////////////////////////////
/////////////////        Core Variables        //////////////
////////////////////////////////////////////////////////////

FakeRanks g_Ext;
CUtlVector<FuncHookBase*> g_vecHooks;
CREATE_GLOBALVARS();
std::map<int, int> points;
std::map<int, int> rank;

void Hook_CCSPlayerPawnBase_PostThink(void* _this);

FuncHook<decltype(Hook_CCSPlayerPawnBase_PostThink)> TCCSPlayerPawnBase_PostThink(Hook_CCSPlayerPawnBase_PostThink, "CCSPlayerPawnBase_PostThink");

//////////////////////////////////////////////////////////////
/////////////////          Core Class          //////////////
////////////////////////////////////////////////////////////


EXT_EXPOSE(g_Ext);
bool FakeRanks::Load(std::string& error, SourceHook::ISourceHook* SHPtr, ISmmAPI* ismm, bool late)
{
    SAVE_GLOBALVARS();
    if (!InitializeHooks()) {
        error = "Failed to initialize hooks.";
        return false;
    }


    std::string ranking = FetchConfigValue<std::string>("fakeranks.type");
    rankType = (ranking == "wingman") ? 7 : (ranking == "premier") ? 11 : 12;


    return true;
}

void Hook_CCSPlayerPawnBase_PostThink(void* _this)
{
    if (!_this) return TCCSPlayerPawnBase_PostThink(_this);
    CHandle<CEntityInstance> controller = SDKGetProp<CHandle<CEntityInstance>>((void*)_this, "CCSPlayerPawnBase", "m_hOriginalController");
    if (!controller) return TCCSPlayerPawnBase_PostThink(_this);
    int playerid = controller.GetEntryIndex() - 1;


    if (points[playerid] != 0)
    {
        SDKSetProp<int32_t>((void*)controller.Get(), "CCSPlayerController", "m_iCompetitiveWins", 10);
        SDKSetProp<int32_t>((void*)controller.Get(), "CCSPlayerController", "m_iCompetitiveRankType", g_Ext.rankType);
        if (g_Ext.rankType == 11)
        {
            SDKSetProp<int32_t>((void*)controller.Get(), "CCSPlayerController", "m_iCompetitiveRanking", points[playerid]);
        }
        else {
            SDKSetProp<int32_t>((void*)controller.Get(), "CCSPlayerController", "m_iCompetitiveRanking", rank[playerid]);
        }
    }
    return TCCSPlayerPawnBase_PostThink(_this);
}

bool FakeRanks::Unload(std::string& error)
{
    UnloadHooks();
    return true;
}

void FakeRanks::AllExtensionsLoaded()
{

}

void FakeRanks::AllPluginsLoaded()
{

}

bool FakeRanks::OnPluginLoad(std::string pluginName, void* pluginState, PluginKind_t kind, std::string& error)
{

    if (kind == PluginKind_t::Lua) {
        lua_State* state = (lua_State*)pluginState;

        luabridge::getGlobalNamespace(state)
            .beginClass<RanksClass>("RanksClass")
            .addConstructor<void (*)(std::string)>()
            .addFunction("GetRankPoints", &RanksClass::GetRankPoints)
            .addFunction("GetRankSkillID", &RanksClass::GetRankSkillID)
            .endClass();

        luaL_dostring(state, "ranks = RanksClass(GetCurrentPluginName())");
    }

    return true;
}

bool FakeRanks::OnPluginUnload(std::string pluginName, void* pluginState, PluginKind_t kind, std::string& error)
{
    return true;
}

const char* FakeRanks::GetAuthor()
{
    return "Swiftly Development Team";
}

const char* FakeRanks::GetName()
{
    return "Fake Ranks Extension";
}

const char* FakeRanks::GetVersion()
{
#ifndef VERSION
    return "Local";
#else
    return VERSION;
#endif
}

const char* FakeRanks::GetWebsite()
{
    return "https://swiftlycs2.net/";
}
