// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DFLItem.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class BASIC_API UDFLItem : public UObject
{
    GENERATED_BODY()

public:

    UDFLItem();

    UPROPERTY(Transient)
    class UWorld *world;

    virtual class UWorld *GetWorld() const { return world; };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    FText use_action_text;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    class UStaticMesh *pickup_mesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    class UTexture2D *thumbnail_texture;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    FText item_display_name;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
    FText item_description;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
    float weight{ 1.0f };

    // The inventory that owns this item
    UPROPERTY()
    class UDFLInventoryComponent *owning_inventory;

    virtual void use(class ADFLCharacter *character); // PURE_VIRTUAL(UItem, );

    UFUNCTION(BlueprintImplementableEvent)
    void on_use(class ADFLCharacter *character);
};
