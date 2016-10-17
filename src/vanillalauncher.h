#ifndef VANILLALAUNCHER_H
#define VANILLALAUNCHER_H

#include "launcher.h"

class Profile;

class VanillaLauncher : public Launcher
{
public:

    static QString ID;

    VanillaLauncher(Profile *p);

};

#endif // VANILLALAUNCHER_H
