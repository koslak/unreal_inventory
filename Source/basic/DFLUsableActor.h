// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DFLUsableActor.generated.h"

UCLASS()
class BASIC_API ADFLUsableActor : public AActor
{
    GENERATED_BODY()

protected:

    UPROPERTY(VisibleAnywhere, Category = "Mesh")
    UStaticMeshComponent* mesh_component;

public:
    ADFLUsableActor();

    /* Player is looking at */
    virtual void OnBeginFocus();

    /* Player is no longer looking at */
    virtual void OnEndFocus();

    /* Called when player interacts with object */
    virtual void OnUsed(APawn* InstigatorPawn);

    /* Public accessor to the mesh component. With FORCEINLINE we are allowed to define the function in the header, use this only for simple accessors! */
    FORCEINLINE UStaticMeshComponent* GetMeshComponent() const
    {
        return mesh_component;
    }
};
