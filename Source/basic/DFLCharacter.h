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
    void pause_game(bool pause_game);

    bool player_can_move();

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    class UCameraComponent *camera_component;

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
    virtual void use_actor();

    class ADFLUsableActor* get_usable_actor_in_view();

    /*Max distance to use/focus on actors. */
    UPROPERTY(EditInstanceOnly, Category = "ObjectInteraction")
    float max_use_distance{ 200 };

    /* True only in first frame when focused on a new usable actor. */
    bool is_usable_actor_has_new_focus{ true };

    class ADFLUsableActor* focused_usable_actor{ nullptr };
    class ADFLUsableActor* examined_actor{ nullptr };

    TSubclassOf<class UDFLItem> UDFLItemClass;

    TSubclassOf<class UUserWidget> DFLInventory_widget_class;
    class UDFLInventoryWidget *inventory_widget{ nullptr };
    bool is_inventory_widget_displayed{ false };
    bool is_action_menu_displayed{ false };
    bool is_actor_to_be_examined{ false };
    bool is_game_paused{ false };

    void process_inventory_visualization();
    void show_inventory();
    void hide_inventory();

};
