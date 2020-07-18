#include "DFLCameraDirector.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/SceneCaptureComponent2D.h"

UDFLCameraDirector::UDFLCameraDirector()
{
    if(!is_arraty_initialized)
    {
        for(int i = 0; i < 5; ++i)
        {
            FString camera_string(TEXT("in_game_camera_N"));
            camera_string.Append(FString::FromInt(i));
            FName camera_name(camera_string);

            in_games_camera_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>(camera_name));
        }

        is_arraty_initialized = true;
        UE_LOG(LogTemp, Warning, TEXT(",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"));
    }
}

USceneCaptureComponent2D *UDFLCameraDirector::get_last_camera_available()
{
//    return in_games_camera_array.Pop();
    return nullptr;
}
