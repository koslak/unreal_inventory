// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DFLInventoryWidget.generated.h"

DECLARE_DELEGATE_OneParam(FParamDelegateSignature, int)

UCLASS()
class BASIC_API UDFLInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

    UDFLInventoryWidget(const FObjectInitializer& ObjectInitializer);

    FParamDelegateSignature action_menu_delegate;

    bool add_item(class UDFLInventoryItemWidget *item);

    void show_inventory();
    void hide_inventory();
    void show_action_menu();
    void hide_action_menu();
    void select_item_to_the_east();
    void select_item_to_the_west();
    void select_item_to_the_north();
    void select_item_to_the_south();
    void select_action_menu_up();
    void select_action_menu_down();
    void execute_action_menu_command();
    UDFLInventoryItemWidget *get_current_item_widget_selected();

private:
    FVector2D get_inventory_item_widget_position();
    void update_action_menu_selection(int action_menu_index_value);

    UPROPERTY(meta = (BindWidget))
    class UWrapBox *InventoryBox;

    UPROPERTY(meta = (BindWidget))
    class UVerticalBox *VerticalBox_Menu;

    UPROPERTY(meta = (BindWidget))
    class UImage *Image_Frame;

    UPROPERTY(meta = (BindWidget))
    class UImage *Image_Frame_1;

    UPROPERTY(meta = (BindWidget))
    class UImage *Image_Frame_2;

    UFUNCTION()
    void close_inventory();

    TSubclassOf<class UUserWidget> DFLInventory_item_widget_class;
    TArray<class UDFLInventoryItemWidget*> item_widget_array;

    int current_item_selected_index{ 0 };
    int action_menu_index{ 0 };

    bool is_action_menu_displayed{ false };
    bool is_item_widget_being_examined{ false };

protected:

    virtual bool Initialize() override;


};
