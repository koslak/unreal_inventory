#include "DFLShowActionMenuGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"
#include "DFLGameStates.h"

void UDFLShowActionMenuGameState::Tick(float DeltaTime)
{
    TestCounter += DeltaTime;

    GEngine->AddOnScreenDebugMessage(0, 0, FColor::Green, FString::SanitizeFloat(TestCounter));
    GEngine->AddOnScreenDebugMessage(1, 0, FColor::Green, *key_pressed);
}

bool UDFLShowActionMenuGameState::IsTickable() const
{
    return true;
}

bool UDFLShowActionMenuGameState::IsTickableInEditor() const
{
    return false;
}

bool UDFLShowActionMenuGameState::IsTickableWhenPaused() const
{
    return false;
}

TStatId UDFLShowActionMenuGameState::GetStatId() const
{
    return TStatId();
}

UWorld* UDFLShowActionMenuGameState::GetWorld() const
{
    return GetOuter()->GetWorld();
}

UDFLGameState *UDFLShowActionMenuGameState::handle_keyboard_input(class ADFLCharacter *character, const FKey &key)
{
    if(character)
    {
        if(key == EKeys::Escape)
        {
            key_pressed = key.ToString();
            UE_LOG(LogTemp, Warning, TEXT("UDFLShowActionMenuGameState::handle_keyboard_input %s"), *key_pressed);

            UDFLGameStates *game_states_instance = character->game_states;
            if(game_states_instance)
            {
                return game_states_instance->get_game_state(Game_State::Hide_Action_Menu);
            }

        }else if(key == EKeys::SpaceBar)
        {
            // Execute selected action menu action
        }
    }

    return nullptr;
}

void UDFLShowActionMenuGameState::enter_state(ADFLCharacter *character)
{
    if(character)
    {
        UE_LOG(LogTemp, Warning, TEXT("UDFLShowActionMenuGameState::enter_state"));
        if(character->inventory_widget)
        {
            APlayerController* player_controller = static_cast<APlayerController*>(character->GetController());
            if(player_controller)
            {
                character->inventory_widget->show_action_menu();
                character->is_action_menu_displayed = true;

            }else{
                UE_LOG(LogTemp, Error, TEXT("player_controller variable is null"));
            }
        }else{
            UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
        }
    }
}
