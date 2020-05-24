// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DFLUsableActor.generated.h"

class UUserWidget;

UCLASS()
class BASIC_API ADFLUsableActor : public AActor
{
    GENERATED_BODY()

protected:

    UPROPERTY(VisibleAnywhere, Category = "Mesh")
    UStaticMeshComponent* mesh_component;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Widget Configuration")
    class UWidgetComponent* widget_component;

    UPROPERTY(EditAnywhere, DisplayName="Widget Height", Category = "Widget Configuration")
    float widget_height{ 100.0f };

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

    FORCEINLINE UWidgetComponent* get_widget_component() const
    {
        return widget_component;
    }

};
