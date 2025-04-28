#include "entrypoint.h"
#include "ranksclass.h"
#include <ehandle.h>
#include <swiftly-ext/config.h>
#include <embedder/src/Embedder.h>

#include <swiftly-ext/sdk.h>

//////////////////////////////////////////////////////////////
/////////////////        Core Variables        //////////////
////////////////////////////////////////////////////////////

FakeRanks g_Ext;
CREATE_GLOBALVARS();
std::map<int, int> points;
std::map<int, int> rank;

dyno::ReturnAction Hook_CCSPlayerPawnBase_PostThink(dyno::CallbackType cbType, dyno::IHook& hook);

FunctionHook CCSPlayerPawnBase_PostThink("CCSPlayerPawnBase_PostThink", dyno::CallbackType::Pre, Hook_CCSPlayerPawnBase_PostThink, "p", 'v');

//////////////////////////////////////////////////////////////
/////////////////          Core Class          //////////////
////////////////////////////////////////////////////////////


EXT_EXPOSE(g_Ext);
bool FakeRanks::Load(std::string& error, SourceHook::ISourceHook* SHPtr, ISmmAPI* ismm, bool late)
{
    SAVE_GLOBALVARS();

    std::string ranking = FetchConfigValue<std::string>("fakeranks.type");
    rankType = (ranking == "wingman") ? 7 : (ranking == "premier") ? 11 : 12;


    return true;
}

dyno::ReturnAction Hook_CCSPlayerPawnBase_PostThink(dyno::CallbackType cbType, dyno::IHook& hook)
{
    void* _this = hook.getArgument<void*>(0);
    if (!_this) return dyno::ReturnAction::Ignored;
    CHandle<CEntityInstance> controller = SDKGetProp<CHandle<CEntityInstance>>((void*)_this, "CCSPlayerPawnBase", "m_hOriginalController");
    if (!controller) return dyno::ReturnAction::Ignored;
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
    return dyno::ReturnAction::Handled;
}

bool FakeRanks::Unload(std::string& error)
{
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
        EContext* state = (EContext*)pluginState;
    
        SetupScripting(state);
    
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
