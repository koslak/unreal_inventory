// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DFLInventoryComponent.generated.h"

// Blueprints will bind to this to update the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASIC_API UDFLInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UDFLInventoryComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:

    bool add_item(class UDFLItem* item);
    bool remove_item(class UDFLItem* item);

    UPROPERTY(EditDefaultsOnly, Instanced)
    TArray<class UDFLItem*> default_items_array;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    int32 capacity{ 20 };

    UPROPERTY(BlueprintAssignable, Category = "Inventory")
    FOnInventoryUpdated on_inventory_updated;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
    TArray<class UDFLItem*> items_array;
};
