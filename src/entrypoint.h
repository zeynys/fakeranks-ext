#ifndef _entrypoint_h
#define _entrypoint_h

#include <string>

#include <swiftly-ext/core.h>
#include <swiftly-ext/extension.h>
#include <swiftly-ext/hooks/NativeHooks.h>

class UtilsExtension : public SwiftlyExt
{
public:
    bool Load(std::string& error, SourceHook::ISourceHook* SHPtr, ISmmAPI* ismm, bool late);
    bool Unload(std::string& error);

    void AllExtensionsLoaded();
    void AllPluginsLoaded();

    bool OnPluginLoad(std::string pluginName, void* pluginState, PluginKind_t kind, std::string& error);
    bool OnPluginUnload(std::string pluginName, void* pluginState, PluginKind_t kind, std::string& error);

public:
    const char* GetAuthor();
    const char* GetName();
    const char* GetVersion();
    const char* GetWebsite();
};

extern UtilsExtension g_Ext;
DECLARE_GLOBALVARS();

#endif