#include "DFLExamineActionMenuGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"
#include "inventory/DFLInventoryItemWidget.h"
#include "DFLUsableActor.h"
#include "DFLGameStates.h"

void UDFLExamineActionMenuGameState::Tick(float DeltaTime)
{
    TestCounter += DeltaTime;

    GEngine->AddOnScreenDebugMessage(10, 0, FColor::Cyan, FString::SanitizeFloat(TestCounter));
    GEngine->AddOnScreenDebugMessage(11, 0, FColor::Cyan, *key_pressed);

    if(this->character)
    {
        if(this->character->is_actor_to_be_examined)
        {
            UDFLInventoryItemWidget *current_item_widget_selected = this->character->inventory_widget->get_current_item_widget_selected();
            if(current_item_widget_selected)
            {
                UE_LOG(LogTemp, Warning, TEXT("UDFLExamineActionMenuGameState::Tick inside is_actor_to_be_examined"));

                ADFLUsableActor *current_item_widget_actor = current_item_widget_selected->parent_actor;
                this->character->examined_actor = current_item_widget_actor;

                UStaticMeshComponent *actor_mesh_component = current_item_widget_actor->get_mesh_component();
                actor_mesh_component->SetVisibility(true);
                current_item_widget_actor->AttachToComponent(this->character->GetCapsuleComponent(), FAttachmentTransformRules::KeepWorldTransform);

                FVector Start = this->character->camera_component->GetComponentLocation();
                FVector ForwardVector = this->character->camera_component->GetForwardVector();
                FVector End = ((ForwardVector * this->character->actor_examined_distance) + Start);

                current_item_widget_actor->SetActorLocation(End);

                if(this->character->is_reset_examine_rotation)
                {
                    FRotator control_rotation = GetWorld()->GetFirstPlayerController()->GetControlRotation();
                    FRotator new_rotation{ 0.0f, 0.0f, 0.0f };
                    current_item_widget_actor->reset_actor_rotation(new_rotation);
                    float tolerance_for_nearly_zero_calculations{ 2.0f };

                    if(control_rotation.Equals(new_rotation, tolerance_for_nearly_zero_calculations))
                    {
                        this->character->is_reset_examine_rotation = !this->character->is_reset_examine_rotation;
                    }
                }else{
                    current_item_widget_actor->rotate_actor();
                }
            }else{
                UE_LOG(LogTemp, Error, TEXT("UDFLExamineActionMenuGameState::Tick -> current_item_widget_selected is null"));
            }
        }
    }
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

UDFLGameState *UDFLExamineActionMenuGameState::handle_keyboard_input(class ADFLCharacter *acharacter, const FKey &key)
{
    if(acharacter)
    {
        if(key == EKeys::Escape)
        {
            key_pressed = key.ToString();
            UE_LOG(LogTemp, Warning, TEXT("UDFLExamineActionMenuGameState::handle_keyboard_input %s"), *key_pressed);

            UDFLGameStates *game_states_instance = acharacter->game_states;
            if(game_states_instance)
            {
                return game_states_instance->get_game_state(Game_State::Show_Inventory);
            }

        }else if(key == EKeys::E) // Reset Rotation
        {
            UDFLGameStates *game_states_instance = acharacter->game_states;
            if(game_states_instance)
            {
                return game_states_instance->get_game_state(Game_State::Show_Action_Menu);
            }
        }
    }

    return nullptr;
}

void UDFLExamineActionMenuGameState::enter_state(ADFLCharacter *acharacter)
{
    if(acharacter)
    {
        this->character = acharacter;

        UE_LOG(LogTemp, Warning, TEXT("UDFLExamineActionMenuGameState::enter_state"));
        if(acharacter->inventory_widget)
        {
            // After executing specific action, hide the Action menu
            acharacter->inventory_widget->hide_action_menu();
            acharacter->is_action_menu_displayed = false;

            // Hide the Inventory menu
            acharacter->inventory_widget->hide_inventory();
            acharacter->is_player_can_move = true;  // This is for the mouse movement, allowing the object to rotate
            acharacter->is_inventory_widget_displayed = false;

            // Display Examine menu
            acharacter->UWidget_examine->SetVisibility(ESlateVisibility::Visible);
            acharacter->is_actor_to_be_examined = true;
            acharacter->camera_component->bUsePawnControlRotation = !acharacter->camera_component->bUsePawnControlRotation;
            acharacter->bUseControllerRotationYaw = !acharacter->bUseControllerRotationYaw;

        }else{
            UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
        }
    }
}
