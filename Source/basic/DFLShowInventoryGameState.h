// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DFLGameState.h"
#include "DFLShowInventoryGameState.generated.h"

UCLASS()
class BASIC_API UDFLShowInventoryGameState : public UDFLGameState
{
	GENERATED_BODY()

public:
    UDFLGameState *next_state_instance();

    void Tick(float DeltaTime) override;
    bool IsTickable() const override;
    bool IsTickableInEditor() const override;
    bool IsTickableWhenPaused() const override;
    TStatId GetStatId() const override;
    UWorld* GetWorld() const override;

    virtual UDFLGameState *handle_keyboard_input(class ADFLCharacter *character, const struct FKey &key) override;
    virtual void enter_state(class ADFLCharacter *character) override;

private:
    UPROPERTY(EditDefaultsOnly)
    UDFLGameState *next_state{ nullptr };

    float TestCounter;
    FString key_pressed;
};

