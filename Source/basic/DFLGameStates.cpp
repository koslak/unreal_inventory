#include "DFLGameStates.h"

#include "Engine.h"

#include "DFLGameState.h"
#include "DFLShowInventoryGameState.h"
#include "DFLHideInventoryGameState.h"
#include "DFLShowActionMenuGameState.h"
#include "DFLHideActionMenuGameState.h"
#include "DFLExecuteActionMenuGameState.h"
#include "DFLExamineActionMenuGameState.h"
#include "DFLResetExamineGameState.h"
#include "DFLSpyInventoryGameState.h"

void UDFLGameStates::create_game_states()
{
    if(!initial_game_state) // || !state_instance->IsValidLowLevelFast())
    {
        initial_game_state = NewObject<UDFLGameState>((UObject*)GetTransientPackage(), UDFLGameState::StaticClass());
    }

    if(!show_inventory_game_state) // || !state_instance->IsValidLowLevelFast())
    {
        show_inventory_game_state = NewObject<UDFLShowInventoryGameState>((UObject*)GetTransientPackage(), UDFLShowInventoryGameState::StaticClass());
    }

    if(!hide_inventory_game_state) // || !state_instance->IsValidLowLevelFast())
    {
        hide_inventory_game_state = NewObject<UDFLHideInventoryGameState>((UObject*)GetTransientPackage(), UDFLHideInventoryGameState::StaticClass());
    }

    if(!show_action_menu_game_state) // || !state_instance->IsValidLowLevelFast())
    {
        show_action_menu_game_state = NewObject<UDFLShowActionMenuGameState>((UObject*)GetTransientPackage(), UDFLShowActionMenuGameState::StaticClass());
    }

    if(!hide_action_menu_game_state) // || !state_instance->IsValidLowLevelFast())
    {
        hide_action_menu_game_state = NewObject<UDFLHideActionMenuGameState>((UObject*)GetTransientPackage(), UDFLHideActionMenuGameState::StaticClass());
    }

    if(!execute_action_menu_game_state) // || !state_instance->IsValidLowLevelFast())
    {
        execute_action_menu_game_state = NewObject<UDFLExecuteActionMenuGameState>((UObject*)GetTransientPackage(), UDFLExecuteActionMenuGameState::StaticClass());
    }

    if(!examine_action_menu_game_state) // || !state_instance->IsValidLowLevelFast())
    {
        examine_action_menu_game_state = NewObject<UDFLExamineActionMenuGameState>((UObject*)GetTransientPackage(), UDFLExamineActionMenuGameState::StaticClass());
    }
    
    if(!reset_rotation_game_state) // || !state_instance->IsValidLowLevelFast())
    {
        reset_rotation_game_state = NewObject<UDFLResetExamineGameState>((UObject*)GetTransientPackage(), UDFLResetExamineGameState::StaticClass());
    }

    if(!spy_inventory_game_state) // || !state_instance->IsValidLowLevelFast())
    {
        spy_inventory_game_state = NewObject<UDFLSpyInventoryGameState>((UObject*)GetTransientPackage(), UDFLSpyInventoryGameState::StaticClass());
    }

    is_game_states_created = true;
}

UDFLGameState *UDFLGameStates::get_game_state(Game_State game_state)
{
    if(!is_game_states_created)
    {
        UE_LOG(LogTemp, Error, TEXT("UDFLGameStates::get_game_state Game states have not been created. Call first the method UDFLGameState::create_game_states"));
        return nullptr;
    }

    switch (game_state)
    {
        case Game_State::Initial:
            return initial_game_state;
        break;

        case Game_State::Show_Inventory:
            return show_inventory_game_state;
        break;

        case Game_State::Hide_Inventory:
            return hide_inventory_game_state;
        break;

        case Game_State::Show_Action_Menu:
            return show_action_menu_game_state;
        break;

        case Game_State::Hide_Action_Menu:
            return hide_action_menu_game_state;
        break;

        case Game_State::Execute_Action_Menu:
            return execute_action_menu_game_state;
        break;

        case Game_State::Examine_Action_Menu:
            return examine_action_menu_game_state;
        break;

        case Game_State::Reset_Rotation:
            return reset_rotation_game_state;
        break;

        case Game_State::Spy_Inventory:
            return spy_inventory_game_state;
        break;

        default:
            return nullptr;
        break;
    }
}
