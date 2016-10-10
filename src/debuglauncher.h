#ifndef DEBUGLAUNCHER_H
#define DEBUGLAUNCHER_H

#include "launcher.h"

class Profile;

class DebugLauncher : public Launcher
{
    static QString ID;

public:
    DebugLauncher(Profile * p);

    void start();
};

#endif // DEBUGLAUNCHER_H
