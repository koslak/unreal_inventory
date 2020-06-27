#include "DFLHideActionMenuGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"
#include "DFLGameStates.h"

void UDFLHideActionMenuGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TestCounter += DeltaTime;

    GEngine->AddOnScreenDebugMessage(0, 0, FColor::Green, FString::SanitizeFloat(TestCounter));
    GEngine->AddOnScreenDebugMessage(1, 0, FColor::Green, *key_pressed);
}

bool UDFLHideActionMenuGameState::IsTickable() const
{
    return true;
}

bool UDFLHideActionMenuGameState::IsTickableInEditor() const
{
    return false;
}

bool UDFLHideActionMenuGameState::IsTickableWhenPaused() const
{
    return false;
}

TStatId UDFLHideActionMenuGameState::GetStatId() const
{
    return TStatId();
}

UWorld* UDFLHideActionMenuGameState::GetWorld() const
{
    return GetOuter()->GetWorld();
}

UDFLGameState *UDFLHideActionMenuGameState::handle_keyboard_input(class ADFLCharacter *character, const FKey &key)
{
    if(character)
    {
        if(key == EKeys::Escape)
        {
            key_pressed = key.ToString();
            UE_LOG(LogTemp, Warning, TEXT("UDFLHideActionMenuGameState::handle_keyboard_input %s"), *key_pressed);

            UDFLGameStates *game_states_instance = character->game_states;
            if(game_states_instance)
            {
                return game_states_instance->get_game_state(Game_State::Hide_Inventory);
            }

        }else if(key == EKeys::SpaceBar)
        {
            UDFLGameStates *game_states_instance = character->game_states;
            if(game_states_instance)
            {
                return game_states_instance->get_game_state(Game_State::Show_Action_Menu);
            }
        }
    }

    return nullptr;
}

void UDFLHideActionMenuGameState::enter_state(ADFLCharacter *character)
{
    if(character)
    {
        UE_LOG(LogTemp, Warning, TEXT("UDFLHideActionMenuGameState::enter_state"));
        if(character->inventory_widget)
        {
            character->inventory_widget->hide_action_menu();
            character->is_action_menu_displayed = false;

        }else{
            UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
        }
    }
}
