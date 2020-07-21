#include "DFLCameraDirector.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/CapsuleComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Materials/Material.h"
#include "DFLCharacter.h"

UDFLCameraDirector::UDFLCameraDirector()
{
    if(!is_arraty_initialized)
    {
        /*
        in_games_camera_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N0"));
        in_games_camera_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N1"));
        in_games_camera_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N2"));
        in_games_camera_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N3"));
        in_games_camera_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N4"));
        in_games_camera_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N5"));
        */

        for(int i = 0; i <= 6; ++i)
        {
            UE_LOG(LogTemp, Warning, TEXT("!!!!!!!!!!!!!!!!!!!!!!!!!!!: %d"), i);

            FString camera_string(TEXT("in_game_camera_N"));
            camera_string.Append(FString::FromInt(i));
            FName camera_name(camera_string);

            USceneCaptureComponent2D *scene_component = CreateDefaultSubobject<USceneCaptureComponent2D>(camera_name);
            if(scene_component)
            {
                in_games_camera_array.Add(scene_component);
            }else{
                UE_LOG(LogTemp, Error, TEXT("UDFLCameraDirector::UDFLCameraDirector USceneCaptureComponent2D is nullptr"));
            }
        }

        is_arraty_initialized = true;
    }
}

void UDFLCameraDirector::create_cameras(ADFLCharacter *character)
{
    FString camera_string(TEXT("in_game_camera_NNN"));
    FName camera_name(camera_string);

    UE_LOG(LogTemp, Warning, TEXT("UDFLCameraDirector::create_cameras !!!!!!!!!!!!!!!!!!!!!!!!!!! - A"));
    in_game_camera = NewObject<USceneCaptureComponent2D>((UObject*)GetTransientPackage(), USceneCaptureComponent2D::StaticClass(), camera_name);
    if(character)
    {
        UE_LOG(LogTemp, Warning, TEXT("UDFLCameraDirector::create_cameras !!!!!!!!!!!!!!!!!!!!!!!!!!! - B"));
        UCapsuleComponent *capsule_component = character->GetCapsuleComponent();
        if(capsule_component)
        {
            UE_LOG(LogTemp, Warning, TEXT("UDFLCameraDirector::create_cameras !!!!!!!!!!!!!!!!!!!!!!!!!!! - C"));
//            in_game_camera->SetupAttachment(capsule_component); //, FAttachmentTransformRules::SnapToTargetIncludingScale);
        }
    }
    /*
    for(int i = 0; i < 6; ++i)
    {
        UE_LOG(LogTemp, Warning, TEXT("UDFLCameraDirector::create_cameras !!!!!!!!!!!!!!!!!!!!!!!!!!!: %s"), *FString::FromInt(i));

        FString camera_string(TEXT("in_game_camera_N"));
        camera_string.Append(FString::FromInt(i));
        FName camera_name(camera_string);

        UTextureRenderTarget2D *texture_render_target_2D = NewObject<UTextureRenderTarget2D>((UObject*)GetTransientPackage(), UTextureRenderTarget2D::StaticClass());
        UMaterial *material = NewObject<UMaterial>((UObject*)GetTransientPackage(), UMaterial::StaticClass());
        USceneCaptureComponent2D *scene_component = NewObject<USceneCaptureComponent2D>((UObject*)GetTransientPackage(), USceneCaptureComponent2D::StaticClass(), camera_name);

        texture_render_target_2D->InitCustomFormat(300, 300, GetPixelFormatFromRenderTargetFormat(ETextureRenderTargetFormat::RTF_RGBA16f), true);
        material->MaterialDomain = EMaterialDomain::MD_UI;
//        scene_component->TextureTarget = texture_render_target_2D;

        if(character)
        {
            UCapsuleComponent *capsule_component = character->GetCapsuleComponent();
            if(capsule_component)
            {
                scene_component->AttachToComponent(capsule_component, FAttachmentTransformRules::SnapToTargetIncludingScale);
            }
        }

        if(scene_component)
        {
            in_games_camera_array.Add(scene_component);
        }else{
            UE_LOG(LogTemp, Error, TEXT("UDFLCameraDirector::UDFLCameraDirector Error creating USceneCaptureComponent2D: No memory"));
        }
    }
    */
}

USceneCaptureComponent2D *UDFLCameraDirector::get_last_camera_available()
{
    int array_size_x = in_games_camera_array.Num();
    for(auto &camera : in_games_camera_array)
    {
//        UE_LOG(LogTemp, Warning, TEXT("UDFLCameraDirector::get_last_camera_available !!!: %s"), *FString::FromInt(array_size_x));
        UE_LOG(LogTemp, Warning, TEXT("UDFLCameraDirector::get_last_camera_available Array Size: %d"), array_size_x);
    }
    /*
    for(auto &camera : in_games_camera_array)
    {
        if(camera)
        {
            FString namex = camera->GetName();
            UE_LOG(LogTemp, Warning, TEXT("UDFLCameraDirector::get_last_camera_available camera name: %s"), *namex );
        }
    }
    */

    /*
    in_games_camera_array[ 0 ]->GetName();
    in_games_camera_array[ 1 ]->GetName();
    in_games_camera_array[ 2 ]->GetName();
    in_games_camera_array[ 3 ]->GetName();
    in_games_camera_array[ 4 ]->GetName();
    in_games_camera_array[ 5 ]->GetName();
    */

    return nullptr; //in_games_camera_array[ 0 ];
}
