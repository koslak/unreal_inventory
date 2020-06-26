#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "DFLGameState.generated.h"

// TODO: This class should be called "InitialGameState"
UCLASS()
class BASIC_API UDFLGameState : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
    void Tick(float DeltaTime) override;
    bool IsTickable() const override;
    bool IsTickableInEditor() const override;
    bool IsTickableWhenPaused() const override;
    TStatId GetStatId() const override;
    UWorld* GetWorld() const override;

    virtual UDFLGameState* handle_keyboard_input(class ADFLCharacter *character, const struct FKey &key);
    virtual void enter_state(class ADFLCharacter *character);

private:
    float TestCounter;
    FString key_pressed;
};
