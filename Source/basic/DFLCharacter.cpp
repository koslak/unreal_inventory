#include "DFLCharacter.h"

#include "Components/InputComponent.h"

// Sets default values
ADFLCharacter::ADFLCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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


}

