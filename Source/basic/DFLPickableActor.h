// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DFLUsableActor.h"
#include "DFLPickableActor.generated.h"

/**
 * 
 */
UCLASS()
class BASIC_API ADFLPickableActor : public ADFLUsableActor
{
    GENERATED_BODY()

    void BeginPlay() override;

    UPROPERTY(EditAnywhere, DisplayName="Pick Up Sound", Category = "Sound")
    class USoundCue* pickup_sound;

protected:

    ADFLPickableActor();

    virtual void OnPickedUp();

    UPROPERTY(Transient)
    bool is_active;

public:

    virtual void OnUsed(APawn* InstigatorPawn) override;

    /* Immediately spawn on begin play */
    UPROPERTY(EditDefaultsOnly, Category = "Pickup")
    bool is_start_active;
};
