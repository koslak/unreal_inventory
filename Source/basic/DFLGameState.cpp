#include "DFLGameState.h"

#include "DFLCharacter.h"
#include "Engine.h"
#include "InputCoreTypes.h"

#include "inventory/DFLInventoryWidget.h"

#include "DFLGameStates.h"

void UDFLGameState::Tick(float DeltaTime)
{
    TestCounter += DeltaTime;
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

UDFLGameState *UDFLGameState::handle_keyboard_input(class ADFLCharacter *character, const FKey &key)
{
    if(character)
    {
        // TODO: Don't hardcode keyboard input. Have a class as a wrapper for keyboard keys
        // so end user will have the option to change keyboard input shortcuts.
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
        else if(key == EKeys::U)
        {
            key_pressed = key.ToString();
            UE_LOG(LogTemp, Warning, TEXT("UDFLGameState::handle_keyboard_input %s"), *key_pressed);

            UDFLGameStates *game_states_instance = character->game_states;
            if(game_states_instance)
            {
                return game_states_instance->get_game_state(Game_State::Spy_Inventory);
            }
        }
    }

    return nullptr;
}

void UDFLGameState::enter_state(ADFLCharacter *character)
{
    // Initial game state
}
