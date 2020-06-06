// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DFLInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASIC_API UDFLInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDFLInventory();

    bool add_item(class UDFLInventoryItem* item);
    bool remove_item(class UDFLInventoryItem* item);

    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    int32 capacity{ 20 };

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
    TArray<class UDFLInventoryItem*> items_array;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Widget Configuration")
    class UWidgetComponent* widget_component;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    void update_UI();

};
