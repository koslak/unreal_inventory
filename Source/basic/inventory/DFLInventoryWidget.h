// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DFLInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class BASIC_API UDFLInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

    UDFLInventoryWidget(const FObjectInitializer& ObjectInitializer);

    bool add_item(class UDFLInventoryItemWidget *item);

private:

    UPROPERTY(meta = (BindWidget))
    class UButton *CloseButton;

    UPROPERTY(meta = (BindWidget))
    class UWrapBox *InventoryBox;

    UFUNCTION()
    void close_inventory();

    TSubclassOf<class UUserWidget> DFLInventory_item_widget_class;
    TArray<class UDFLInventoryItemWidget*> item_widget_array;

protected:

    virtual bool Initialize() override;


};
