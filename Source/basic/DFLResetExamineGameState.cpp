#include "DFLResetExamineGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"
#include "inventory/DFLInventoryItemWidget.h"
#include "DFLUsableActor.h"
#include "DFLGameStates.h"

void UDFLResetExamineGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(this->character)
    {
		//UE_LOG(LogTemp, Warning, TEXT("UDFLResetExamineGameState::Tick -> is_reset_examine_rotation %s"), this->character->is_reset_examine_rotation ? TEXT("true") : TEXT("false"));
        
        if(this->character->is_actor_to_be_examined)
        {
            UDFLInventoryItemWidget *current_item_widget_selected = this->character->inventory_widget->get_current_item_widget_selected();
            if(current_item_widget_selected)
            {
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
                    UWorld* world = this->character->GetWorld();
                    if(world)
                    {
                        APlayerController* player_controller = world->GetFirstPlayerController();
                        if(player_controller)
                        {
                            FRotator control_rotation = player_controller->GetControlRotation();
                            FRotator new_rotation{ 0.0f, 0.0f, 0.0f };
                            current_item_widget_actor->reset_actor_rotation(new_rotation);
                            float tolerance_for_nearly_zero_calculations{ 2.0f };

                            if(control_rotation.Equals(new_rotation, tolerance_for_nearly_zero_calculations))
                            {
                                this->character->is_reset_examine_rotation = !this->character->is_reset_examine_rotation;
                            }
                        }
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

bool UDFLResetExamineGameState::IsTickable() const
{
    return true;
}

bool UDFLResetExamineGameState::IsTickableInEditor() const
{
    return false;
}

bool UDFLResetExamineGameState::IsTickableWhenPaused() const
{
    return false;
}

TStatId UDFLResetExamineGameState::GetStatId() const
{
    return TStatId();
}

UWorld* UDFLResetExamineGameState::GetWorld() const
{
    UObject *outer_object = GetOuter(); // GetOuter: returns the UObject this object resides in.
    if(outer_object)
    {
        return outer_object->GetWorld();
    }

    return nullptr;
}

UDFLGameState *UDFLResetExamineGameState::handle_keyboard_input(class ADFLCharacter *acharacter, const FKey &key)
{
    if(acharacter)
    {
        if(key == EKeys::Escape)
        {
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
                return game_states_instance->get_game_state(Game_State::Reset_Rotation);
            }
        }
    }

    return nullptr;
}

void UDFLResetExamineGameState::enter_state(ADFLCharacter *acharacter)
{
    if(acharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("UDFLResetExamineGameState::enter_state"));

        this->character = acharacter;
        this->character->is_reset_examine_rotation = !this->character->is_reset_examine_rotation;
    }
}
