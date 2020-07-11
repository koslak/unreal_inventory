// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DFLCharacter.generated.h"

UCLASS()
class BASIC_API ADFLCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ADFLCharacter();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    void move_forward(float value);
    void move_right(float value);
    void lookup(float value);
    void turn(float value);
    void move_widget_left();
    void move_widget_right();
    void move_widget_up();
    void move_widget_down();
    void menu_action();
    void escape_current_state();
    void pause_game(bool pause_game);

    bool player_can_move();

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    class UCameraComponent *camera_component;

    UFUNCTION()
    void action_menu_delegate_slot(int action_menu_index);

    void handle_keyboard_input(FKey key);

    //************************************************************************
    //  Inventory                                                            *
    //************************************************************************
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    class UDFLInventoryComponent *inventory_component;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
    float health{ 100.0f };

    UFUNCTION(BlueprintCallable, Category = "Items")
    void use_item(class UDFLItem *item);

    //************************************************************************
    //  Object Interaction                                                   *
    //************************************************************************

    /* Use the usable actor currently in focus, if any */
    virtual void use_actor(FKey key);

    class ADFLUsableActor* get_usable_actor_in_view();

    /*Max distance to use/focus on actors. */
    UPROPERTY(EditInstanceOnly, Category = "ObjectInteraction")
    float max_use_distance{ 200 };


    //************************************************************************
    //  Game States
    //************************************************************************

    // Because UE4 wants to handle memory management of UObjects, you will also need to add a UPROPERTY() macro above it
    // If you don't add the UPROPERTY() macro above the UObject to be used, you are in for a special bounding experience with your debugger.
    UPROPERTY(EditDefaultsOnly)
    class UDFLGameState *current_game_state;
//    TSubclassOf<class UDFLGameState> game_state;

//    UPROPERTY(EditDefaultsOnly)
//    class UDFLShowInventoryGameState *inventory_game_state;
//    TSubclassOf<class UDFLGameState> inventory_game_state;

    UPROPERTY(EditDefaultsOnly)
    class UDFLGameStates *game_states;

    //************************************************************************

    /* True only in first frame when focused on a new usable actor. */
    bool is_usable_actor_has_new_focus{ true };

    class ADFLUsableActor* focused_usable_actor{ nullptr };
    class ADFLUsableActor* examined_actor{ nullptr };

    TSubclassOf<class UDFLItem> UDFLItemClass;
    TSubclassOf<class UUserWidget> DFLInventory_widget_class;
    TSubclassOf<class UUserWidget> UWidget_Examined_BP_class;
    TSubclassOf<class UUserWidget> DFLSpy_Cam_Inventory_BP_class;
    class UUserWidget *UWidget_examine{ nullptr };

    UPROPERTY(EditDefaultsOnly)
    class USceneCaptureComponent2D *in_game_camera_1{ nullptr };

    class UDFLInventoryWidget *inventory_widget{ nullptr };
    class UDFLSpyInventoryWidget *spy_inventory_widget{ nullptr };
    bool is_inventory_widget_displayed{ false };
    bool is_player_can_move{ true };
    bool is_action_menu_displayed{ false };
    bool is_actor_to_be_examined{ false };
    bool is_game_paused{ false };
    bool is_reset_examine_rotation{ false };

    FRotator camera_last_rotation{ 0.0f, 0.0f, 0.0f };
    float actor_examined_distance{ 90.0f };
    const float MAX_ACTOR_EXAMINED_DISTANCE{ 110.0f };
    const float MIN_ACTOR_EXAMINED_DISTANCE{ 70.0f };

    void process_inventory_visualization();
    void show_inventory();
    void hide_inventory();

};
