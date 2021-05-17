QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    car/car.cpp \
    car/sensor.cpp \
    main.cpp \
    map/map.cpp \
    map/crossroad.cpp \
    map/entrance.cpp \
    map/milestone.cpp \
    map/road.cpp \

HEADERS += \
    car/car.h \
    car/sensor.h \
    map/map.h \
    map/crossroad.h \
    map/entrance.h \
    map/milestone.h \
    map/road.h \

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    saves/default.txt \
    window.png
