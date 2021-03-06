// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DFLInventoryItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class BASIC_API UDFLInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

    class ADFLUsableActor *parent_actor{ nullptr };

    UPROPERTY(meta = (BindWidget))
    class UButton *UseButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *ItemName;

    UPROPERTY(meta = (BindWidget))
    class UImage *Thumbnail;

    UPROPERTY(meta = (BindWidget))
    class UImage *FrameSelector;

    UPROPERTY(meta = (BindWidget))
    class UVerticalBox *VerticalBox_Item;
};
