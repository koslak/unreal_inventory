#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "DFLCameraDirector.generated.h"

UCLASS()
class BASIC_API ADFLCameraDirector : public AActor
{
	GENERATED_BODY()
	
public:
    ADFLCameraDirector();
    void create_cameras(class ADFLCharacter *character);
    class USceneCaptureComponent2D *get_last_camera_available();

private:
//    UPROPERTY(EditDefaultsOnly)
//    TArray<class USceneCaptureComponent2D *> in_games_camera_array;

    UPROPERTY(EditAnywhere)
    class USceneCaptureComponent2D *in_game_camera;

    bool is_arraty_initialized{ false };
};
