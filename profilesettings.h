#ifndef PROFILESETTINGS_H
#define PROFILESETTINGS_H

#include <QWidget>
#include <QAbstractButton>
#include "profile.h"

namespace Ui {
class ProfileSettings;
}

class ProfileSettings : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileSettings(QWidget *parent = 0);
    ~ProfileSettings();

public slots:

    void setCurrentProfile(Profile * profile);

    void saveOrDiscart(QAbstractButton * button);

    void discart();

    void save();

private:
    Ui::ProfileSettings *ui;
    Profile * m_CurrentProfile = nullptr;
};

#endif // PROFILESETTINGS_H
