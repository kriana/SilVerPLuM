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

    /**
     * @brief Returns the current platform
     * @return
     */
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

    /**
     * @brief Returns the platfrom from a platformstring
     * @param str
     * @return
     */
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

    /**
     * @brief Returns the platform as platformstring
     * @return
     */
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


