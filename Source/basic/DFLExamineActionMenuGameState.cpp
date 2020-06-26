#include "DFLExamineActionMenuGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"
#include "DFLGameStates.h"

void UDFLExamineActionMenuGameState::Tick(float DeltaTime)
{
    TestCounter += DeltaTime;

    GEngine->AddOnScreenDebugMessage(0, 0, FColor::Green, FString::SanitizeFloat(TestCounter));
    GEngine->AddOnScreenDebugMessage(1, 0, FColor::Green, *key_pressed);
}

bool UDFLExamineActionMenuGameState::IsTickable() const
{
    return true;
}

bool UDFLExamineActionMenuGameState::IsTickableInEditor() const
{
    return false;
}

bool UDFLExamineActionMenuGameState::IsTickableWhenPaused() const
{
    return false;
}

TStatId UDFLExamineActionMenuGameState::GetStatId() const
{
    return TStatId();
}

UWorld* UDFLExamineActionMenuGameState::GetWorld() const
{
    return GetOuter()->GetWorld();
}

UDFLGameState *UDFLExamineActionMenuGameState::handle_keyboard_input(class ADFLCharacter *character, const FKey &key)
{
    if(character)
    {
        if(key == EKeys::Escape)
        {
            key_pressed = key.ToString();
            UE_LOG(LogTemp, Warning, TEXT("UDFLExamineActionMenuGameState::handle_keyboard_input %s"), *key_pressed);

            UDFLGameStates *game_states_instance = character->game_states;
            if(game_states_instance)
            {
                return game_states_instance->get_game_state(Game_State::Show_Inventory);
            }

        }else if(key == EKeys::E) // Reset Rotation
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

void UDFLExamineActionMenuGameState::enter_state(ADFLCharacter *character)
{
    if(character)
    {
        UE_LOG(LogTemp, Warning, TEXT("UDFLExamineActionMenuGameState::enter_state"));
        if(character->inventory_widget)
        {
            character->inventory_widget->hide_inventory();
            character->is_player_can_move = false;
            character->is_inventory_widget_displayed = false;

            character->UWidget_examine->SetVisibility(ESlateVisibility::Visible);
            character->is_actor_to_be_examined = true;
            character->camera_component->bUsePawnControlRotation = !character->camera_component->bUsePawnControlRotation;
            character->bUseControllerRotationYaw = !character->bUseControllerRotationYaw;

            // After executing specific action, hide the action menu
            character->inventory_widget->hide_action_menu();
            character->is_action_menu_displayed = false;

        }else{
            UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
        }
    }
}
