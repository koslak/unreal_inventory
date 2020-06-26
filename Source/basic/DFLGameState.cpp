#include "DFLGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"
#include "DFLShowInventoryGameState.h"

#include "DFLGameStates.h"

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

UDFLGameState *UDFLGameState::next_state_instance()
{
    if(!show_inventory_state) // || !state_instance->IsValidLowLevelFast())
    {
        show_inventory_state = NewObject<UDFLShowInventoryGameState>((UObject*)GetTransientPackage(), UDFLShowInventoryGameState::StaticClass());
    }
    return show_inventory_state;
}

UDFLGameState *UDFLGameState::handle_keyboard_input(class ADFLCharacter *character, const FKey &key)
{
    if(character)
    {
        if(key == EKeys::Q)
        {
            key_pressed = key.ToString();
            UE_LOG(LogTemp, Warning, TEXT("UDFLGameState::handle_keyboard_input %s"), *key_pressed);

            UDFLGameStates *game_states_instance = character->game_states;
            if(game_states_instance)
            {
                return game_states_instance->get_game_state(Game_State::Show_Inventory);
            }
        }
    }

    return nullptr;
}

void UDFLGameState::enter_state(ADFLCharacter *character)
{
    // Initial game state
}
