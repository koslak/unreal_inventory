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

public:
    ADFLUsableActor();

    /* Player is looking at */
    virtual void OnBeginFocus();

    /* Player is no longer looking at */
    virtual void OnEndFocus();

    /* Called when player interacts with object */
    virtual void OnUsed(APawn* InstigatorPawn);

    void rotate_actor();
    void reset_actor_rotation(const FRotator &new_rotation);

    /* Public accessor to the mesh component. With FORCEINLINE we are allowed to define the function in the header, use this only for simple accessors! */
    FORCEINLINE UStaticMeshComponent* get_mesh_component() const
    {
        return mesh_component;
    }

    FORCEINLINE class UWidgetComponent* get_widget_component() const
    {
        return widget_component;
    }

    FORCEINLINE class UDFLInventoryItemWidget* get_inventory_item_widget() const
    {
        return inventory_item_widget;
    }

//protected:

    UPROPERTY(VisibleAnywhere, Category = "Mesh")
    UStaticMeshComponent* mesh_component;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Widget Configuration")
    class UWidgetComponent* widget_component;

    UPROPERTY(EditAnywhere, DisplayName="Widget Height", Category = "Widget Configuration")
    float widget_height{ 100.0f };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Configuration")
    class UTexture2D *thumbnail_image;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Configuration")
    FText item_widget_display_name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Configuration", meta = (MultiLine = "true"))
    FText item_widget_description_text;

    class UDFLInventoryItemWidget *inventory_item_widget;

private:

    TSubclassOf<class UUserWidget> DFLInventory_item_widget_class;
    FRotator control_rotation;
};
