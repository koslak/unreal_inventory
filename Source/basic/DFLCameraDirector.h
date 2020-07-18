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
    class USceneCaptureComponent2D *get_last_camera_available();

private:
    UPROPERTY(EditDefaultsOnly)
    TArray<class USceneCaptureComponent2D *> in_games_camera_array;

    bool is_arraty_initialized{ false };
};
