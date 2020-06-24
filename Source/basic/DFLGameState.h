#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "DFLGameState.generated.h"

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

    virtual bool handle_keyboard_input(class ADFLCharacter *character, const struct FKey &key);
    virtual void enter_state(class ADFLCharacter *character);

    float TestCounter;
    FString key_pressed;
};
