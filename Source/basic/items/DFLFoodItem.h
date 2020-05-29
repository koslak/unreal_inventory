// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DFLItem.h"
#include "DFLFoodItem.generated.h"

/**
 * 
 */
UCLASS()
class BASIC_API UDFLFoodItem : public UDFLItem
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
    float health_to_heal;

protected:

    virtual void use(class ADFLCharacter *character) override;
};
