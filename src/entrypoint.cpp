#include "entrypoint.h"

//////////////////////////////////////////////////////////////
/////////////////        Core Variables        //////////////
////////////////////////////////////////////////////////////

BaseExtension g_Ext;
SourceHook::ISourceHook *g_SHPtr = nullptr;
ISmmAPI* g_SMAPI = nullptr;

//////////////////////////////////////////////////////////////
/////////////////          Core Class          //////////////
////////////////////////////////////////////////////////////

EXT_EXPOSE(g_Ext);
bool BaseExtension::Load(std::string& error, SourceHook::ISourceHook *SHPtr, ISmmAPI* ismm, bool late)
{
    ismm->ConPrint("Printing a text from extensions land!\n");
    return true;
}

bool BaseExtension::Unload(std::string& error)
{
    return true;
}

void BaseExtension::AllExtensionsLoaded()
{

}

void BaseExtension::AllPluginsLoaded()
{

}

const char* BaseExtension::GetAuthor()
{
    return "Swiftly Development Team";
}

const char* BaseExtension::GetName()
{
    return "Base Extension";
}

const char* BaseExtension::GetVersion()
{
#ifndef VERSION
    return "Local";
#else
    return VERSION;
#endif
}

const char* BaseExtension::GetWebsite()
{
    return "https://swiftlycs2.net/";
}
