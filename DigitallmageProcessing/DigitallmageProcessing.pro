# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

QT += core gui widgets

TEMPLATE = app
TARGET = DigitallmageProcessing
DESTDIR = ../x64/Debug
CONFIG += debug
LIBS += -L"."
DEPENDPATH += .
MOC_DIR += GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += debug
UI_DIR += GeneratedFiles
RCC_DIR += GeneratedFiles
HEADERS += ./DigitallmageProcessing.h \
	numericselection.h
SOURCES += ./DigitallmageProcessing.cpp \
    ./main.cpp \
    numericselection.cpp
FORMS += ./DigitallmageProcessing.ui \
	numericselection.ui
RESOURCES += DigitallmageProcessing.qrc
