#include "DFLGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"

void UDFLGameState::Tick(float DeltaTime)
{
    TestCounter += DeltaTime;

    GEngine->AddOnScreenDebugMessage(0, 0, FColor::Green, FString::SanitizeFloat(TestCounter));
    GEngine->AddOnScreenDebugMessage(1, 0, FColor::Green, *key_pressed);

}

bool UDFLGameState::IsTickable() const
{
    return true;
}

bool UDFLGameState::IsTickableInEditor() const
{
    return false;
}

bool UDFLGameState::IsTickableWhenPaused() const
{
    return false;
}

TStatId UDFLGameState::GetStatId() const
{
    return TStatId();
}

UWorld* UDFLGameState::GetWorld() const
{
    return GetOuter()->GetWorld();
}

bool UDFLGameState::handle_keyboard_input(class ADFLCharacter *character, const FKey &key)
{
    if(key == EKeys::N)
    {
        key_pressed = key.ToString();
        UE_LOG(LogTemp, Warning, TEXT("UDFLGameState::handle_keyboard_input %s"), *key_pressed);

        return true;
    }

    return false;
}

void UDFLGameState::enter_state(ADFLCharacter *character)
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
            }else{
                UE_LOG(LogTemp, Error, TEXT("player_controller variable is null"));
            }
        }else{
            UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
        }
    }
}
