#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T16:14:40
#
#-------------------------------------------------

QT       += core gui network positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PolygonCreator
TEMPLATE = app


SOURCES += main.cpp\
        main_window.cpp

HEADERS  += main_window.h

FORMS    += main_window.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

