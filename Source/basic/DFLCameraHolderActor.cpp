#include "DFLCameraHolderActor.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneCaptureComponent2D.h"

ADFLCameraHolderActor::ADFLCameraHolderActor()
{
    is_active = false;
    is_start_active = true;

    this->SetActorTickEnabled(true);
}

void ADFLCameraHolderActor::BeginPlay()
{
    Super::BeginPlay();

    if(widget_component)
    {
        widget_component->SetVisibility(false);
        widget_component->SetRelativeLocation(FVector(0.0f, 0.0f, widget_height));
    }
}

void ADFLCameraHolderActor::OnUsed(APawn *InstigatorPawn)
{
//    Super::OnUsed(InstigatorPawn);

    UGameplayStatics::PlaySoundAtLocation(this, pickup_sound, GetActorLocation());

    is_active = false;
}

void ADFLCameraHolderActor::set_camera(USceneCaptureComponent2D *in_game_camera)
{
    camera = in_game_camera;

    if(camera && mesh_component)
    {
        camera->AttachToComponent(mesh_component, FAttachmentTransformRules::SnapToTargetIncludingScale);
        camera->SetRelativeRotation(FRotator{0.0f, 180.0f, 0.0f});
    }
}
