TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

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
    ../../Source/basic/items/DFLFoodItem.h \
    ../../Source/basic/item/DFLInventory.h \
    ../../Source/basic/item/DFLInventoryItem.h \
    ../../Source/basic/inventory/DFLInventoryWidget.h \
    ../../Source/basic/inventory/DFLInventoryItemWidget.h \
    ../../Source/basic/DFLGameStates.h \
    ../../Source/basic/DFLGameState.h \
    ../../Source/basic/DFLShowInventoryGameState.h \
    ../../Source/basic/DFLShowActionMenuGameState.h \
    ../../Source/basic/DFLHideActionMenuGameState.h \
    ../../Source/basic/DFLHideInventoryGameState.h \
    ../../Source/basic/DFLExecuteActionMenuGameState.h \
    ../../Source/basic/DFLExamineActionMenuGameState.h \
    ../../Source/basic/DFLResetExamineGameState.h \
    ../../Source/basic/DFLSpyInventoryGameState.h \
    ../../Source/basic/inventory/DFLSpyInventoryWidget.h \
    ../../Source/basic/DFLCameraHolderActor.h \
    ../../Source/basic/DFLCameraLabelWidget.h \
    ../../Source/basic/DFLCameraDirector.h \
    ../../Source/basic/DFLCameraManager.h

SOURCES +=  ../../Source/basic/basic.cpp \
    ../../Source/basic/basicGameModeBase.cpp \
    ../../Source/basic/DFLCharacter.cpp \
    ../../Source/basic/DFLUsableActor.cpp \
    ../../Source/basic/DFLPickableActor.cpp \
    ../../Source/basic/items/DFLInventoryComponent.cpp \
    ../../Source/basic/items/DFLItem.cpp \
    ../../Source/basic/items/DFLFoodItem.cpp \
    ../../Source/basic/item/DFLInventory.cpp \
    ../../Source/basic/item/DFLInventoryItem.cpp \
    ../../Source/basic/inventory/DFLInventoryWidget.cpp \
    ../../Source/basic/inventory/DFLInventoryItemWidget.cpp \
    ../../Source/basic/DFLGameState.cpp \
    ../../Source/basic/DFLGameStates.cpp \
    ../../Source/basic/DFLShowInventoryGameState.cpp \
    ../../Source/basic/DFLShowActionMenuGameState.cpp \
    ../../Source/basic/DFLHideActionMenuGameState.cpp \
    ../../Source/basic/DFLHideInventoryGameState.cpp \
    ../../Source/basic/DFLExecuteActionMenuGameState.cpp \
    ../../Source/basic/DFLExamineActionMenuGameState.cpp \
    ../../Source/basic/DFLResetExamineGameState.cpp \
    ../../Source/basic/DFLSpyInventoryGameState.cpp \
    ../../Source/basic/inventory/DFLSpyInventoryWidget.cpp \
    ../../Source/basic/DFLCameraHolderActor.cpp \
    ../../Source/basic/DFLCameraLabelWidget.cpp \
    ../../Source/basic/DFLCameraDirector.cpp \
    ../../Source/basic/DFLCameraManager.cpp

# All your generated includes will go in this file
# You can not put this on the repository as this contains hardcoded paths
# and is dependend on your windows install and engine version
include(includes.pri)

