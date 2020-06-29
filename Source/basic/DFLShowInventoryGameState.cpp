#include "DFLShowInventoryGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"
#include "DFLGameStates.h"
#include "DFLUsableActor.h"

void UDFLShowInventoryGameState::Tick(float DeltaTime)
{
    TestCounter += DeltaTime;
}

bool UDFLShowInventoryGameState::IsTickable() const
{
    return true;
}

bool UDFLShowInventoryGameState::IsTickableInEditor() const
{
    return false;
}

bool UDFLShowInventoryGameState::IsTickableWhenPaused() const
{
    return false;
}

TStatId UDFLShowInventoryGameState::GetStatId() const
{
    return TStatId();
}

UWorld* UDFLShowInventoryGameState::GetWorld() const
{
    return GetOuter()->GetWorld();
}

UDFLGameState *UDFLShowInventoryGameState::handle_keyboard_input(class ADFLCharacter *character, const FKey &key)
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

void UDFLShowInventoryGameState::enter_state(ADFLCharacter *character)
{
    if(character)
    {
        UE_LOG(LogTemp, Warning, TEXT("UDFLShowInventoryGameState::enter_state"));
        if(character->inventory_widget)
        {
            if(character->is_actor_to_be_examined)
            {
                character->UWidget_examine->SetVisibility(ESlateVisibility::Hidden);

                if(character->examined_actor)
                {
                    UStaticMeshComponent *actor_mesh_component = character->examined_actor->get_mesh_component();
                    actor_mesh_component->SetVisibility(false);

                    character->is_actor_to_be_examined = !character->is_actor_to_be_examined;
                    character->Controller->SetControlRotation(character->camera_last_rotation);
                    character->camera_component->bUsePawnControlRotation = !character->camera_component->bUsePawnControlRotation;
                    character->bUseControllerRotationYaw = !character->bUseControllerRotationYaw;
                }
            }

            character->inventory_widget->show_inventory();
            character->is_player_can_move = false;
            character->is_inventory_widget_displayed = true;

        }else{
            UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
        }
    }
}
