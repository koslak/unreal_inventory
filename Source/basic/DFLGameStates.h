// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DFLGameStates.generated.h"

UENUM()
enum Game_State
{
    Initial          UMETA(DisplayName = "Initial"),
    Show_Inventory   UMETA(DisplayName = "Show_Inventory"),
    Hide_Inventory   UMETA(DisplayName = "Hide_Inventory"),
    Show_Action_Menu   UMETA(DisplayName = "Show_Action_Menu"),
    Hide_Action_Menu   UMETA(DisplayName = "Hide_Action_Menu"),
    Execute_Action_Menu   UMETA(DisplayName = "Execute_Action_Menu"),
    Examine_Action_Menu   UMETA(DisplayName = "Examine_Action_Menu"),
    Reset_Rotation   UMETA(DisplayName = "Reset_Rotation"),
    Spy_Inventory    UMETA(DisplayName = "Spy_Inventory")
};

UCLASS()
class BASIC_API UDFLGameStates : public UObject
{
	GENERATED_BODY()
	
public:
    void create_game_states();
    class UDFLGameState *get_game_state(Game_State game_state);

    UPROPERTY(EditDefaultsOnly)
    class UDFLGameState *initial_game_state{ nullptr };

    UPROPERTY(EditDefaultsOnly)
    class UDFLShowInventoryGameState *show_inventory_game_state{ nullptr };

    UPROPERTY(EditDefaultsOnly)
    class UDFLHideInventoryGameState *hide_inventory_game_state{ nullptr };

    UPROPERTY(EditDefaultsOnly)
    class UDFLShowActionMenuGameState *show_action_menu_game_state{ nullptr };

    UPROPERTY(EditDefaultsOnly)
    class UDFLHideActionMenuGameState *hide_action_menu_game_state{ nullptr };

    UPROPERTY(EditDefaultsOnly)
    class UDFLExecuteActionMenuGameState *execute_action_menu_game_state{ nullptr };

    UPROPERTY(EditDefaultsOnly)
    class UDFLExamineActionMenuGameState *examine_action_menu_game_state{ nullptr };

    UPROPERTY(EditDefaultsOnly)
    class UDFLResetExamineGameState *reset_rotation_game_state{ nullptr };

    UPROPERTY(EditDefaultsOnly)
    class UDFLSpyInventoryGameState *spy_inventory_game_state{ nullptr };

private:
    bool is_game_states_created{ false };
};
