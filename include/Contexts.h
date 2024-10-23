#ifndef CONTEXTS_H
#define CONTEXTS_H

#include "MenuContext.h"

union Contexts
{
    MenuContext menuContext;
    AnalysisContext analysisContext;
    SettingsContext settingsContext;
};

#endif