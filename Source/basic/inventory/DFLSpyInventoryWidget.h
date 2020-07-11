// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DFLSpyInventoryWidget.generated.h"

UCLASS()
class BASIC_API UDFLSpyInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

 public:
    UDFLSpyInventoryWidget(const FObjectInitializer& ObjectInitializer);

    void hide_camera_3();

 private:
    UPROPERTY(meta = (BindWidget))
    class UImage *image_cam_1;

    UPROPERTY(meta = (BindWidget))
    class UImage *image_cam_2;

    UPROPERTY(meta = (BindWidget))
    class UImage *image_cam_3;

};
