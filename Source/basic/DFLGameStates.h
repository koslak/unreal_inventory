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
};

UCLASS()
class BASIC_API UDFLGameStates : public UObject
{
	GENERATED_BODY()
	
public:
    void create_game_states();
    class UDFLGameState *get_game_state(Game_State game_state);

    class UDFLGameState *initial_game_state{ nullptr };
    class UDFLShowInventoryGameState *show_inventory_game_state{ nullptr };
    class UDFLHideInventoryGameState *hide_inventory_game_state{ nullptr };

private:
    bool is_game_states_created{ false };
};
