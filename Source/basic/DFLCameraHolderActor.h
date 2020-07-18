#pragma once

#include "CoreMinimal.h"
#include "DFLUsableActor.h"
#include "DFLCameraHolderActor.generated.h"

UCLASS()
class BASIC_API ADFLCameraHolderActor : public ADFLUsableActor
{
	GENERATED_BODY()
	
    void BeginPlay() override;

    UPROPERTY(EditAnywhere, DisplayName="Pick Up Sound", Category = "Sound")
    class USoundCue* pickup_sound;

protected:
    ADFLCameraHolderActor();

    UPROPERTY(Transient)
    bool is_active;

public:
    virtual void OnUsed(APawn* InstigatorPawn) override;
    void set_camera(class USceneCaptureComponent2D *in_game_camera);

    /* Immediately spawn on begin play */
    UPROPERTY(EditDefaultsOnly, Category = "Pickup")
    bool is_start_active;

private:
    class USceneCaptureComponent2D *camera{ nullptr };

};
