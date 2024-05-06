QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/../ffmpeg-n4.3-19/ffmpeg.pri)
INCLUDEPATH += $$PWD/../SDL2-2.0.20/include

LIBS +=$$PWD/../SDL2-2.0.20/lib/x64/SDL2.lib
LIBS +=$$PWD/../SDL2-2.0.20/lib/x64/SDL2main.lib

SOURCES += \
        main.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# HEADERS += \
#     cmdutils.h \
#     config.h
