#pragma once
#include <QSysInfo>

class Platform
{
public:
    enum Type
    {
        Windows,
        OSX,
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
            return OSX;
        }
        else
        {
            return Windows;
        }
    }

private:

    Platform()
    {

    }
};


