#include "DFLCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "DFLUsableActor.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ADFLCharacter::ADFLCharacter()
{
    // Set this character to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADFLCharacter::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ADFLCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Controller && Controller->IsLocalController())
    {
        ADFLUsableActor* usable_actor = get_usable_actor_in_view();

        // End Focus
        if (focused_usable_actor != usable_actor)
        {
            if (focused_usable_actor)
            {
                focused_usable_actor->OnEndFocus();
            }

            is_usable_actor_has_new_focus = true;
        }

        // Assign new Focus
        focused_usable_actor = usable_actor;

        // Start Focus.
        if (usable_actor)
        {
            if (is_usable_actor_has_new_focus)
            {
                usable_actor->OnBeginFocus();
                is_usable_actor_has_new_focus = false;
            }
        }
    }
}

void ADFLCharacter::move_forward(float value)
{
    AddMovementInput(GetActorForwardVector() * value);
}

void ADFLCharacter::move_right(float value)
{
    AddMovementInput(GetActorRightVector() * value);
}

// Called to bind functionality to input
void ADFLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ADFLCharacter::move_forward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ADFLCharacter::move_right);

    PlayerInputComponent->BindAxis("LookUp", this, &ADFLCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("Turn", this, &ADFLCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ADFLCharacter::use_actor);
}

void ADFLCharacter::use_actor()
{
    UE_LOG(LogTemp, Warning, TEXT("use_actor being called") );

    ADFLUsableActor* usable_actor = get_usable_actor_in_view();
    if (usable_actor)
    {
        usable_actor->OnUsed(this);
    }
}

ADFLUsableActor *ADFLCharacter::get_usable_actor_in_view()
{
    FVector CamLoc;
    FRotator CamRot;

    if (Controller == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("ADFLCharacter::get_usable_actor_in_view -> Controller is null") );
        return nullptr;
    }

    Controller->GetPlayerViewPoint(CamLoc, CamRot);
    const FVector TraceStart = CamLoc;
    const FVector Direction = CamRot.Vector();
    const FVector TraceEnd = TraceStart + (Direction * max_use_distance);

    FCollisionQueryParams TraceParams(FName(TEXT("TraceUsableActor")), true, this);
    TraceParams.bReturnPhysicalMaterial = false;
    TraceParams.bTraceComplex = true;

    FHitResult Hit(ForceInit);
    GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, TraceParams);

//    DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f);

    return Cast<ADFLUsableActor>(Hit.GetActor());
}

