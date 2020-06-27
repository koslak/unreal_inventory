#include "DFLHideInventoryGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"
#include "DFLGameStates.h"

void UDFLHideInventoryGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TestCounter += DeltaTime;

    /*
    GEngine->AddOnScreenDebugMessage(3, 0, FColor::Blue, FString::SanitizeFloat(TestCounter));
    GEngine->AddOnScreenDebugMessage(4, 0, FColor::Blue, *key_pressed);
    GEngine->AddOnScreenDebugMessage(5, 0, FColor::Blue, TEXT("UDFLHideInventoryGameState::Tick"));
    */
}

bool UDFLHideInventoryGameState::IsTickable() const
{
    return true;
}

bool UDFLHideInventoryGameState::IsTickableInEditor() const
{
    return false;
}

bool UDFLHideInventoryGameState::IsTickableWhenPaused() const
{
    return false;
}

TStatId UDFLHideInventoryGameState::GetStatId() const
{
    return TStatId();
}

UWorld* UDFLHideInventoryGameState::GetWorld() const
{
    return GetOuter()->GetWorld();
}

// TODO: This state shouldn't exist, From the ShowInventoryGameState, when pressing Esc, it should go to the initial game state
UDFLGameState *UDFLHideInventoryGameState::handle_keyboard_input(class ADFLCharacter *character, const FKey &key)
{
    if(character)
    {
        if(key == EKeys::Q)
        {
            key_pressed = key.ToString();
            UE_LOG(LogTemp, Warning, TEXT("UDFLHideInventoryGameState::handle_keyboard_input %s"), *key_pressed);

            UDFLGameStates *game_states_instance = character->game_states;
            if(game_states_instance)
            {
                return game_states_instance->get_game_state(Game_State::Show_Inventory);
            }
        }
    }

    return nullptr;
}

void UDFLHideInventoryGameState::enter_state(ADFLCharacter *character)
{
    if(character)
    {
        UE_LOG(LogTemp, Warning, TEXT("UDFLHideInventoryGameState::enter_state"));
        if(character->inventory_widget)
        {
            character->inventory_widget->hide_inventory();
            character->is_player_can_move = true;
            character->is_inventory_widget_displayed = false;
        }else{
            UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
        }
    }
}
