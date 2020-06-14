#include "DFLPickableActor.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/WidgetComponent.h"

ADFLPickableActor::ADFLPickableActor()
{
    if (mesh_component)
    {
        /* Ignore Pawn - this is to prevent objects shooting through the level or pawns glitching on top of small items. */
        mesh_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
    }

    is_active = false;
    is_start_active = true;
}

void ADFLPickableActor::BeginPlay()
{
    Super::BeginPlay();

    if(widget_component)
    {
        widget_component->SetVisibility(false);
        widget_component->SetRelativeLocation(FVector(0.0f, 0.0f, widget_height));
    }
}

void ADFLPickableActor::OnPickedUp()
{
    if (mesh_component)
    {
        mesh_component->SetVisibility(false);
        mesh_component->SetSimulatePhysics(false);
        mesh_component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void ADFLPickableActor::OnUsed(APawn *InstigatorPawn)
{
    Super::OnUsed(InstigatorPawn);

    UGameplayStatics::PlaySoundAtLocation(this, pickup_sound, GetActorLocation());

    is_active = false;
    OnPickedUp();

//    Destroy();
}
