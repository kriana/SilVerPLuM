#pragma once
#include <QSysInfo>

class Platform
{
public:
    enum Type
    {
        Windows,
        Mac,
        Linux
    };

    static Type getCurrentPlatform()
    {
        if(QSysInfo::kernelType() == "winnt")
        {
            return Windows;
        }
        else if(QSysInfo::kernelType() == "linux")
        {
            return Linux;
        }
        else if(QSysInfo::kernelType() == "darwin")
        {
            return Mac;
        }
        else
        {
            return Windows;
        }
    }

    static QString getPlatformString()
    {
        switch(getCurrentPlatform())
        {
        case Windows:
            return "windows";
        case Linux:
            return "linux";
        case Mac:
            return "mac";
        default:
            return "windows";
        }
    }

private:

    Platform()
    {

    }
};


