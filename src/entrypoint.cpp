#include "entrypoint.h"

//////////////////////////////////////////////////////////////
/////////////////        Core Variables        //////////////
////////////////////////////////////////////////////////////

UtilsExtension g_Ext;
CUtlVector<FuncHookBase*> g_vecHooks;
CREATE_GLOBALVARS();

//////////////////////////////////////////////////////////////
/////////////////          Core Class          //////////////
////////////////////////////////////////////////////////////

EXT_EXPOSE(g_Ext);
bool UtilsExtension::Load(std::string& error, SourceHook::ISourceHook* SHPtr, ISmmAPI* ismm, bool late)
{
    SAVE_GLOBALVARS();
    if (!InitializeHooks()) {
        error = "Failed to initialize hooks.";
        return false;
    }

    ismm->ConPrint("Printing a text from extensions land!\n");
    return true;
}

bool UtilsExtension::Unload(std::string& error)
{
    UnloadHooks();
    return true;
}

void UtilsExtension::AllExtensionsLoaded()
{

}

void UtilsExtension::AllPluginsLoaded()
{

}

bool UtilsExtension::OnPluginLoad(std::string pluginName, void* pluginState, PluginKind_t kind, std::string& error)
{
    return true;
}

bool UtilsExtension::OnPluginUnload(std::string pluginName, void* pluginState, PluginKind_t kind, std::string& error)
{
    return true;
}

const char* UtilsExtension::GetAuthor()
{
    return "Swiftly Development Team";
}

const char* UtilsExtension::GetName()
{
    return "Utils Extension";
}

const char* UtilsExtension::GetVersion()
{
#ifndef VERSION
    return "Local";
#else
    return VERSION;
#endif
}

const char* UtilsExtension::GetWebsite()
{
    return "https://swiftlycs2.net/";
}
