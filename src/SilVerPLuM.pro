#-------------------------------------------------
#
# Project created by QtCreator 2016-10-02T14:42:34
#
#-------------------------------------------------

QT       += core gui network concurrent xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SilVerPLuM
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
    dependencycheckerwidget.cpp \
    dllpipeline.cpp \
    logger.cpp \
    sundown/src/autolink.c \
    sundown/src/buffer.c \
    sundown/src/markdown.c \
    sundown/src/stack.c \
    sundown/html/houdini_href_e.c \
    sundown/html/houdini_html_e.c \
    sundown/html/html.c \
    sundown/html/html_smartypants.c \
    markdowntexteditor.cpp \
    logviewer.cpp \
    savegame.cpp \
    savegamemanager.cpp \
    backupsavegame.cpp \
    savegamemanagerwidget.cpp \
    savegamemanagerwidgetitem.cpp \
    savegamemanagerwidgetbackupitem.cpp

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
    dependencycheckerwidget.h \
    dllpipeline.h \
    logger.h \
    sundown/src/autolink.h \
    sundown/src/buffer.h \
    sundown/src/html_blocks.h \
    sundown/src/markdown.h \
    sundown/src/stack.h \
    sundown/html/houdini.h \
    sundown/html/html.h \
    markdowntexteditor.h \
    logviewer.h \
    savegame.h \
    savegamemanager.h \
    backupsavegame.h \
    savegamemanagerwidget.h \
    savegamemanagerwidgetitem.h \
    savegamemanagerwidgetbackupitem.h


FORMS    += mainwindow.ui \
    fileselectoredit.ui \
    profilesettings.ui \
    profilemanagerwidget.ui \
    modmanagerwidget.ui \
    modmanagerwidgetitem.ui \
    globalsettingsdialog.ui \
    modmanagerwidgetpipelineitem.ui \
    dependencycheckerwidget.ui \
    markdownviewer.ui \
    logviewer.ui \
    savegamemanagerwidget.ui \
    savegamemanagerwidgetitem.ui \
    savegamemanagerwidgetbackupitem.ui

RESOURCES += \
    resources.qrc

# We need zlib and quazip for extracting/installing new mods
unix: LIBS += -lquazip5 -lz
unix: INCLUDEPATH += /usr/include/quazip5/
