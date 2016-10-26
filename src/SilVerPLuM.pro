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
    sundown/src/houdini_href_e.c \
    sundown/src/houdini_html_e.c \
    sundown/src/html.c \
    sundown/src/html_smartypants.c \
    markdowntexteditor.cpp \
    logviewer.cpp \
    savegame.cpp \
    savegamemanager.cpp \
    backupsavegame.cpp \
    savegamemanagerwidget.cpp \
    savegamemanagerwidgetitem.cpp \
    savegamemanagerwidgetbackupitem.cpp \
    savegameviewerdialog.cpp \
    debuglauncher.cpp \
    encryptedcontentpasswordgenerator.cpp \
    quazipcompress.cpp \
    modimporter.cpp \
    modimportercontentitem.cpp \
    identifierlineedit.cpp \
    filestash.cpp \
    externalprogram.cpp \
    externalprogramsettingswidget.cpp \
    custompipeline.cpp \
    messagewidget.cpp \
    modrepositorywindow.cpp \
    modrepository.cpp \
    repositorypipeline.cpp \
    programpipeline.cpp \
    downloadmanager.cpp \
    pipelinelistwidget.cpp \
    modrepositoryentry.cpp \
    modrepositoryentrywidget.cpp \
    modrepositoryentrylist.cpp \
    categorycombobox.cpp \
    activatemoddialog.cpp \
    dependencytree.cpp \
    modrepositorysource.cpp \
    imagemergepipeline.cpp

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
    sundown/src/houdini.h \
    sundown/src/html.h \
    markdowntexteditor.h \
    logviewer.h \
    savegame.h \
    savegamemanager.h \
    backupsavegame.h \
    savegamemanagerwidget.h \
    savegamemanagerwidgetitem.h \
    savegamemanagerwidgetbackupitem.h \
    savegameviewerdialog.h \
    debuglauncher.h \
    encryptedcontentpasswordgenerator.h \
    quazipcompress.h \
    modimporter.h \
    modimportercontentitem.h \
    identifierlineedit.h \
    filestash.h \
    externalprogram.h \
    externalprogramsettingswidget.h \
    custompipeline.h \
    messagewidget.h \
    modrepositorywindow.h \
    modrepository.h \
    repositorypipeline.h \
    programpipeline.h \
    downloadmanager.h \
    pipelinelistwidget.h \
    modrepositoryentry.h \
    modrepositoryentrywidget.h \
    modrepositoryentrylist.h \
    categorycombobox.h \
    activatemoddialog.h \
    dependencytree.h \
    modrepositorysource.h \
    imagemergepipeline.h


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
    savegamemanagerwidgetbackupitem.ui \
    savegameviewerdialog.ui \
    encryptedcontentpasswordgenerator.ui \
    modimporter.ui \
    modimportercontentitem.ui \
    filestash.ui \
    externalprogramsettingswidget.ui \
    messagewidget.ui \
    modrepositorywindow.ui \
    pipelinelistwidget.ui \
    modrepositoryentrywidget.ui \
    modrepositoryentrylist.ui \
    activatemoddialog.ui

RESOURCES += \
    resources.qrc


# The icon theme is only needed for Mac and Windows
#win32: RESOURCES += icons/icontheme.qrc
#win64: RESOURCES += icons/icontheme.qrc
#macx: RESOURCES += icons/icontheme.qrc

# Removed this from the executable. use rcc -binary icontheme.qrc -o icontheme.rcc to build the icon theme


# We need zlib and quazip for extracting/installing new mods

unix {
    LIBS += -lquazip5 -lz
    INCLUDEPATH += /usr/include/quazip5/
}

win32 {
    INCLUDEPATH += $$PWD/../quazip-0.7.2/quazip
    DEPENDPATH += $$PWD/../build-quazip-Desktop_Qt_5_7_0_MinGW_32bit-Release/quazip/release
    LIBS += -L$$PWD/../build-quazip-Desktop_Qt_5_7_0_MinGW_32bit-Release/quazip/release/ -lquazip

    INCLUDEPATH += C:/GnuWin32/include/
    LIBS += -LC:/GnuWin32/bin/ -lz

    # OpenSSL
    LIBS += -LC:/Qt/Qt5.7.0/Tools/mingw530_32/opt/bin/ -llibeay32 -lssleay32
}

# Make the windows executable have an icon
RC_FILE = SilVerPLuM.rc


