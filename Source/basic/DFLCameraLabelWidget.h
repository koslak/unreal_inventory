// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DFLCameraLabelWidget.generated.h"

UCLASS()
class BASIC_API UDFLCameraLabelWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UDFLCameraLabelWidget(const FObjectInitializer& ObjectInitializer);

    void set_text(FText text);

private:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock *LabelText;
};
