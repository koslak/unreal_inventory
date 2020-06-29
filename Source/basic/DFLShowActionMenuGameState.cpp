#include "DFLShowActionMenuGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"
#include "DFLGameStates.h"

void UDFLShowActionMenuGameState::Tick(float DeltaTime)
{
    TestCounter += DeltaTime;
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
            UE_LOG(LogTemp, Warning, TEXT("UDFLShowActionMenuGameState::handle_keyboard_input %s"), *key.ToString());

            UDFLGameStates *game_states_instance = character->game_states;
            if(game_states_instance)
            {
                return game_states_instance->get_game_state(Game_State::Hide_Action_Menu);
            }

        }else if(key == EKeys::SpaceBar)
        {
            UE_LOG(LogTemp, Warning, TEXT("UDFLShowActionMenuGameState::handle_keyboard_input %s"), *key.ToString());

            // Execute selected action menu action
            UDFLGameStates *game_states_instance = character->game_states;
            if(game_states_instance)
            {
                switch(character->inventory_widget->get_current_action_menu_index())
                {
                    case 0: // Use menu
                    {
                        return game_states_instance->get_game_state(Game_State::Execute_Action_Menu);
                    }
                    break;

                    case 1: // Examine menu
                    {
                        return game_states_instance->get_game_state(Game_State::Examine_Action_Menu);
                    }
                    break;
                }
            }
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
            // Save last camera rotation in case the current inventory item is about to be examined, so we don't lose the current camera position.
            AController* controller = character->Controller;
            if(controller)
            {
                character->camera_last_rotation = controller->GetControlRotation();
            }

            character->inventory_widget->show_action_menu();
            character->is_action_menu_displayed = true;

        }else{
            UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
        }
    }
}
