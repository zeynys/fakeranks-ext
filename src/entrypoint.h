#ifndef _entrypoint_h
#define _entrypoint_h

#include <string>

#include <swiftly-ext/core.h>
#include <swiftly-ext/extension.h>

class BaseExtension : public SwiftlyExt
{
public:
    bool Load(std::string& error, SourceHook::ISourceHook *SHPtr, ISmmAPI* ismm, bool late);
    bool Unload(std::string& error);
    
    void AllExtensionsLoaded();
    void AllPluginsLoaded();

public:
    const char* GetAuthor();
    const char* GetName();
    const char* GetVersion();
    const char* GetWebsite();
};

extern BaseExtension g_Ext;
extern SourceHook::ISourceHook *g_SHPtr;
extern ISmmAPI* g_SMAPI;

#endif