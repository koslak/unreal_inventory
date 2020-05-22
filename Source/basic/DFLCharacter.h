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

};
