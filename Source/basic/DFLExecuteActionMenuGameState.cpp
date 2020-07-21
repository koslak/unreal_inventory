#include "DFLExecuteActionMenuGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"
#include "DFLGameStates.h"
#include "DFLCameraHolderActor.h"
#include "DFLCameraDirector.h"
#include "inventory/DFLInventoryItemWidget.h"
#include "Components/TextBlock.h"

void UDFLExecuteActionMenuGameState::Tick(float DeltaTime)
{
    TestCounter += DeltaTime;
}

bool UDFLExecuteActionMenuGameState::IsTickable() const
{
    return true;
}

bool UDFLExecuteActionMenuGameState::IsTickableInEditor() const
{
    return false;
}

bool UDFLExecuteActionMenuGameState::IsTickableWhenPaused() const
{
    return false;
}

TStatId UDFLExecuteActionMenuGameState::GetStatId() const
{
    return TStatId();
}

UWorld* UDFLExecuteActionMenuGameState::GetWorld() const
{
    return GetOuter()->GetWorld();
}

UDFLGameState *UDFLExecuteActionMenuGameState::handle_keyboard_input(class ADFLCharacter *character, const FKey &key)
{
    if(character)
    {
        if(key == EKeys::Escape)
        {
            key_pressed = key.ToString();
            UE_LOG(LogTemp, Warning, TEXT("UDFLExecuteActionMenuGameState::handle_keyboard_input %s"), *key_pressed);

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

void UDFLExecuteActionMenuGameState::enter_state(ADFLCharacter *character)
{
    if(character)
    {
        UE_LOG(LogTemp, Warning, TEXT("UDFLExecuteActionMenuGameState::enter_state"));
        if(character->inventory_widget)
        {
            UDFLInventoryItemWidget *inventory_item_widget = character->inventory_widget->get_current_item_widget_selected();
            if(inventory_item_widget)
            {
                // TODO: Avoid comparison of strings, use an Enum instead.
                if(inventory_item_widget->ItemName->Text.EqualTo(FText::FromString(TEXT("Spy Camera"))))
                {
                    ADFLUsableActor *usable_actor = character->get_usable_actor_in_view();
                    ADFLCameraHolderActor *camera_holder_actor{ nullptr };

                    camera_holder_actor = Cast<ADFLCameraHolderActor>(usable_actor);

                    if(camera_holder_actor && character->camera_director)
                    {
                        USceneCaptureComponent2D *camera = character->camera_director->get_last_camera_available();
                        if(camera)
                        {
                            camera_holder_actor->attach_camera(camera);
                            camera_holder_actor->set_camera_inventory_item_widget(inventory_item_widget);
                            camera_holder_actor->OnUsed(character);
                        }
                    }
                }
            }

            // Remove the current inventory item.
            character->inventory_widget->remove_current_selected_item();

            // After executing use action, hide the action menu
            character->inventory_widget->hide_action_menu();
            character->is_action_menu_displayed = false;

            // And now go to the initial game state where the inventory will be hidden
            // we do this by triggering the "Esc" key.
            character->handle_keyboard_input(EKeys::Escape);

        }else{
            UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
        }
    }
}
