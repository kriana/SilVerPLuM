#-------------------------------------------------
#
# Project created by QtCreator 2016-10-02T14:42:34
#
#-------------------------------------------------

QT       += core gui network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CSDVMM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fileselectoredit.cpp \
    modification.cpp \
    dependency.cpp \
    pipeline.cpp \
    profilemanager.cpp \
    profile.cpp \
    profilesettings.cpp \
    launcher.cpp \
    vanillalauncher.cpp \
    profilemanagerwidget.cpp \
    game.cpp \
    qtsingleapplication/src/qtlocalpeer.cpp \
    qtsingleapplication/src/qtlockedfile.cpp \
    qtsingleapplication/src/qtlockedfile_unix.cpp \
    qtsingleapplication/src/qtlockedfile_win.cpp \
    qtsingleapplication/src/qtsingleapplication.cpp \
    qtsingleapplication/src/qtsinglecoreapplication.cpp \
    globalsettings.cpp \
    launcherexecutable.cpp \
    modmanagerwidget.cpp \
    modmanager.cpp \
    filepipeline.cpp \
    modmanagerwidgetitem.cpp \
    globalsettingsdialog.cpp \
    modmanagerwidgetpipelineitem.cpp \
    dependencycheckerwidget.cpp

HEADERS  += mainwindow.h \
    fileselectoredit.h \
    platform.h \
    modification.h \
    dependency.h \
    pipeline.h \
    profilemanager.h \
    profile.h \
    utils.h \
    profilesettings.h \
    launcher.h \
    vanillalauncher.h \
    profilemanagerwidget.h \
    game.h \
    qtsingleapplication/src/qtlocalpeer.h \
    qtsingleapplication/src/qtlockedfile.h \
    qtsingleapplication/src/qtsingleapplication.h \
    qtsingleapplication/src/qtsinglecoreapplication.h \
    globalsettings.h \
    launcherexecutable.h \
    modmanagerwidget.h \
    modmanager.h \
    filepipeline.h \
    modmanagerwidgetitem.h \
    globalsettingsdialog.h \
    modmanagerwidgetpipelineitem.h \
    dependencycheckerwidget.h

FORMS    += mainwindow.ui \
    fileselectoredit.ui \
    profilesettings.ui \
    profilemanagerwidget.ui \
    modmanagerwidget.ui \
    modmanagerwidgetitem.ui \
    globalsettingsdialog.ui \
    modmanagerwidgetpipelineitem.ui \
    dependencycheckerwidget.ui

RESOURCES += \
    resources.qrc
