# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = JsonReader
DESTDIR = ../_build/Release
QT += core
CONFIG += staticlib release
DEFINES += WIN64 QT_DLL JSONREADER_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/$(ConfigurationName) \
    $(SolutionDir)include \
    $(BOOST_ROOT)
LIBS += -L"$(BOOST_ROOT)/stage/lib"
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(JsonReader.pri)