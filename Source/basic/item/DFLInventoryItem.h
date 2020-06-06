// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DFLInventoryItem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class BASIC_API UDFLInventoryItem : public UObject
{
	GENERATED_BODY()
	
public:

    UDFLInventoryItem();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    class UTexture2D *thumbnail_texture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    class UUserWidget* widget;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    FText item_display_name;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
    FText item_description;

protected:

    virtual void use();
};
