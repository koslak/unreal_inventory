#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DFLCameraDirector.generated.h"

UCLASS()
class BASIC_API UDFLCameraDirector : public UObject
{
	GENERATED_BODY()
	
public:
    UDFLCameraDirector();
    void create_cameras(class ADFLCharacter *character);
    class USceneCaptureComponent2D *get_last_camera_available();

private:
    UPROPERTY(EditDefaultsOnly)
    TArray<class USceneCaptureComponent2D *> in_games_camera_array;

    UPROPERTY(EditDefaultsOnly)
    class USceneCaptureComponent2D *in_game_camera;

    bool is_arraty_initialized{ false };
};
