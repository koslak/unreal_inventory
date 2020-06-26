#include "DFLShowInventoryGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"
#include "DFLHideInventoryGameState.h"

void UDFLShowInventoryGameState::Tick(float DeltaTime)
{
    TestCounter += DeltaTime;

    GEngine->AddOnScreenDebugMessage(0, 0, FColor::Green, FString::SanitizeFloat(TestCounter));
    GEngine->AddOnScreenDebugMessage(1, 0, FColor::Green, *key_pressed);

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

UDFLGameState *UDFLShowInventoryGameState::next_state_instance()
{
    if(!next_state) // || !state_instance->IsValidLowLevelFast())
    {
        next_state = NewObject<UDFLHideInventoryGameState>((UObject*)GetTransientPackage(), UDFLHideInventoryGameState::StaticClass());
    }

    return next_state;
}

UDFLGameState *UDFLShowInventoryGameState::handle_keyboard_input(class ADFLCharacter *character, const FKey &key)
{
    if(key == EKeys::Escape)
    {
        key_pressed = key.ToString();
        UE_LOG(LogTemp, Warning, TEXT("UDFLShowInventoryGameState::handle_keyboard_input %s"), *key_pressed);

        return next_state_instance();

    }else if(key == EKeys::SpaceBar)
    {
        if(character && character->inventory_widget->is_action_menu_can_be_displayed())
        {

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
            APlayerController* player_controller = static_cast<APlayerController*>(character->GetController());
            if(player_controller)
            {
                character->is_player_can_move = false;
                character->inventory_widget->show_inventory();
            }else{
                UE_LOG(LogTemp, Error, TEXT("player_controller variable is null"));
            }
        }else{
            UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
        }
    }
}
