#include "scopesettings.h"

scopeSettings::scopeSettings(){}

static scopeSettings& get() {
    static scopeSettings instance;
    return instance;
}


