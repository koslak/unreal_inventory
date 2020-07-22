#include "DFLCameraManager.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/SceneCaptureComponent2D.h"

ADFLCameraManager::ADFLCameraManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    in_game_cameras_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N0"));
    in_game_cameras_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N1"));
    in_game_cameras_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N2"));
    in_game_cameras_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N3"));
    in_game_cameras_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N4"));
    in_game_cameras_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N5"));
}

void ADFLCameraManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADFLCameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USceneCaptureComponent2D *ADFLCameraManager::get_last_camera_available()
{
    UE_LOG(LogTemp, Warning, TEXT("-----ADFLCameraManager::get_last_camera_available array size: %d"), in_game_cameras_array.Num());
    UE_LOG(LogTemp, Warning, TEXT("-----ADFLCameraManager::get_last_camera_available index: %d"), current_camera_index);
    USceneCaptureComponent2D *camera{ nullptr };

    if(in_game_cameras_array.Num() > 0)
    {
        FString namex = in_game_cameras_array[ current_camera_index ]->GetName();
        UE_LOG(LogTemp, Warning, TEXT("ADFLCameraManager::get_last_camera_available camera available: %s"), *namex );
        camera = in_game_cameras_array[ current_camera_index ];

        current_camera_index++;
        int cameras_array_size{ in_game_cameras_array.Num() };

        if(current_camera_index >= cameras_array_size)
        {
            current_camera_index = cameras_array_size - 1;
        }
    }

    return camera;
}

