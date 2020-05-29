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

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
};
