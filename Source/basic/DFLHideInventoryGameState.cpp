#include "DFLHideInventoryGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"
#include "DFLShowInventoryGameState.h"

void UDFLHideInventoryGameState::Tick(float DeltaTime)
{
    TestCounter += DeltaTime;

    GEngine->AddOnScreenDebugMessage(0, 0, FColor::Green, FString::SanitizeFloat(TestCounter));
    GEngine->AddOnScreenDebugMessage(1, 0, FColor::Green, *key_pressed);
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

UDFLGameState *UDFLHideInventoryGameState::next_state_instance()
{
    if(!hide_inventory_state_) // || !state_instance->IsValidLowLevelFast())
    {
        hide_inventory_state_ = NewObject<UDFLShowInventoryGameState>((UObject*)GetTransientPackage(), UDFLShowInventoryGameState::StaticClass());
    }

    return hide_inventory_state_;
}

UDFLGameState *UDFLHideInventoryGameState::handle_keyboard_input(class ADFLCharacter *character, const FKey &key)
{
    if(key == EKeys::N)
    {
        key_pressed = key.ToString();
        UE_LOG(LogTemp, Warning, TEXT("UDFLGameState::handle_keyboard_input %s"), *key_pressed);

        return next_state_instance();
    }

    return nullptr;
}

void UDFLHideInventoryGameState::enter_state(ADFLCharacter *character)
{
    if(character)
    {
        UE_LOG(LogTemp, Warning, TEXT("UDFLGameState::enter_state"));
        if(character->inventory_widget)
        {
            APlayerController* player_controller = static_cast<APlayerController*>(character->GetController());
            if(player_controller)
            {
                character->inventory_widget->show_inventory();
                character->is_player_can_move = false;
            }else{
                UE_LOG(LogTemp, Error, TEXT("player_controller variable is null"));
            }
        }else{
            UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
        }
    }
}
