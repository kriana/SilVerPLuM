#pragma once
#include <QSysInfo>

class Platform
{
public:

    enum GameTechnology
    {
        GameTechnologyXNA,
        GameTechnologyMonoGame
    };

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

    static Type getPlatformFromString(const QString & str)
    {
        if(str == "windows")
        {
            return Windows;
        }
        else if(str == "linux")
        {
            return Linux;
        }
        else if(str == "mac")
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


