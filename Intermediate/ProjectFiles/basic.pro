TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++17

# All the defines of your project will go in this file
# You can put this file on your repository, but you will need to remake it once you upgrade the engine.
include(defines.pri)

HEADERS +=  ../../Source/basic/basic.h \
    ../../Source/basic/basicGameModeBase.h \
    ../../Source/basic/DFLCharacter.h \
    ../../Source/basic/DFLUsableActor.h \
    ../../Source/basic/DFLPickableActor.h \
    ../../Source/basic/items/DFLInventoryComponent.h \
    ../../Source/basic/items/DFLItem.h \
    ../../Source/basic/items/DFLFoodItem.h

SOURCES +=  ../../Source/basic/basic.cpp \
    ../../Source/basic/basicGameModeBase.cpp \
    ../../Source/basic/DFLCharacter.cpp \
    ../../Source/basic/DFLUsableActor.cpp \
    ../../Source/basic/DFLPickableActor.cpp \
    ../../Source/basic/items/DFLInventoryComponent.cpp \
    ../../Source/basic/items/DFLItem.cpp \
    ../../Source/basic/items/DFLFoodItem.cpp

# All your generated includes will go in this file
# You can not put this on the repository as this contains hardcoded paths
# and is dependend on your windows install and engine version
include(includes.pri)

