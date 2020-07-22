#include "DFLSpyInventoryGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"
#include "inventory/DFLSpyInventoryWidget.h"
#include "DFLGameStates.h"
#include "DFLUsableActor.h"
#include "DFLCameraManager.h"

void UDFLSpyInventoryGameState::Tick(float DeltaTime)
{
    TestCounter += DeltaTime;
}

bool UDFLSpyInventoryGameState::IsTickable() const
{
    return true;
}

bool UDFLSpyInventoryGameState::IsTickableInEditor() const
{
    return false;
}

bool UDFLSpyInventoryGameState::IsTickableWhenPaused() const
{
    return false;
}

TStatId UDFLSpyInventoryGameState::GetStatId() const
{
    return TStatId();
}

UWorld* UDFLSpyInventoryGameState::GetWorld() const
{
    return GetOuter()->GetWorld();
}

UDFLGameState *UDFLSpyInventoryGameState::handle_keyboard_input(class ADFLCharacter *character, const FKey &key)
{
    if(character)
    {
        if(key == EKeys::Escape)
        {
            key_pressed = key.ToString();
            UE_LOG(LogTemp, Warning, TEXT("UDFLShowInventoryGameState::handle_keyboard_input %s"), *key_pressed);

            UDFLGameStates *game_states_instance = character->game_states;
            if(game_states_instance)
            {
                return game_states_instance->get_game_state(Game_State::Hide_Inventory);
            }

        }else if(key == EKeys::SpaceBar)
        {
            if(character->inventory_widget->is_action_menu_can_be_displayed())
            {
                UDFLGameStates *game_states_instance = character->game_states;
                if(game_states_instance)
                {
                    return game_states_instance->get_game_state(Game_State::Show_Action_Menu);
                }
            }
        }
    }

    return nullptr;
}

void UDFLSpyInventoryGameState::enter_state(ADFLCharacter *character)
{
    if(character)
    {
        UE_LOG(LogTemp, Warning, TEXT("UDFLSpyInventoryGameState::enter_state"));
        character->camera_manager->set_spy_inventory_visibility(ESlateVisibility::Visible);
    }
}
