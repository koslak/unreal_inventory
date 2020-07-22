#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DFLCameraManager.generated.h"

UCLASS()
class BASIC_API ADFLCameraManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ADFLCameraManager();
    class USceneCaptureComponent2D *get_last_camera_available();
    int get_current_camera_index() const { return current_camera_index; };

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(EditAnywhere)
    TArray<class USceneCaptureComponent2D *> in_game_cameras_array;

    int current_camera_index{ 0 };
};
