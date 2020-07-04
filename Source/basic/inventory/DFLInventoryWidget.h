// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Containers/Map.h"
#include "DFLInventoryWidget.generated.h"

USTRUCT()
struct FItem_widget_array 
{
    GENERATED_BODY()

public:
    void insert_item(class UDFLInventoryItemWidget *item) { if(item) { items_array.Add(item); }}
    void remove_item(class UDFLInventoryItemWidget *item) { if(item) { items_array.Remove(item); }}
    class UDFLInventoryItemWidget *operator[] (int32 i)  { if(i >= 0 && i < items_array.Num()) { return items_array[ i ]; }  return nullptr; }

    int get_number_items() { return items_array.Num(); }

private:
    UPROPERTY(EditDefaultsOnly)
    TArray<class UDFLInventoryItemWidget *> items_array;
};

USTRUCT()
struct FItem_widget_array_2D 
{
    GENERATED_BODY()

public:
    void initialize();
    TPair<int, int> add_item(class UDFLInventoryItemWidget *item);
    void remove_item(class UDFLInventoryItemWidget *item);
    bool remove_item(int row, int column);
    FItem_widget_array &operator[] (int32 i);
    int get_rows_number();
    int get_columns_number();
    bool is_empty();

private:
    UPROPERTY(EditDefaultsOnly)
    TArray<FItem_widget_array> item_widget_array;

    bool is_struct_initialized{ false };
    int current_row_index{ 0 };
    int current_column_index{ 0 };
    int MAX_NUMBER_OF_INVENTORY_ROWS{ 5 };
    int MAX_NUMBER_OF_INVENTORY_COLUMNS{ 5 };
};

DECLARE_DELEGATE_OneParam(FParamDelegateSignature, int)

UCLASS()
class BASIC_API UDFLInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

    UDFLInventoryWidget(const FObjectInitializer& ObjectInitializer);

    FParamDelegateSignature action_menu_delegate;

    bool add_item(class UDFLInventoryItemWidget *item);
    bool remove_current_selected_item();

    bool is_action_menu_can_be_displayed();
    void show_inventory();
    void hide_inventory();
    void show_action_menu();
    void hide_action_menu();

    void select_item_to_the_east();
    void select_item_to_the_east1();
    void select_item_to_the_west();
    void select_item_to_the_north();
    void select_item_to_the_south();
    void change_item_selection();

    void select_action_menu_up();
    void select_action_menu_down();
    void execute_action_menu_command();
    UDFLInventoryItemWidget *get_current_item_widget_selected();
    int get_current_action_menu_index() const;
    void update_item_text_title_and_description();
    void set_initial_highlighted_item();

    bool is_item_widget_being_examined{ false };

private:
    FVector2D get_inventory_item_widget_position();
    void update_action_menu_selection(int action_menu_index_value);

    UPROPERTY(meta = (BindWidget))
    class UVerticalBox *VerticalBox_Menu;

    UPROPERTY(meta = (BindWidget))
    class UGridPanel *InventoryGridPanel;

    UPROPERTY(meta = (BindWidget))
    class UImage *Image_Frame;

    UPROPERTY(meta = (BindWidget))
    class UImage *Image_Frame_1;

    UPROPERTY(meta = (BindWidget))
    class UImage *Image_Frame_2;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *ItemTitle;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *ItemDescription;

    //UFUNCTION()
    //void close_inventory();

    TSubclassOf<class UUserWidget> DFLInventory_item_widget_class;

    UPROPERTY(EditDefaultsOnly)
    TArray<class UDFLInventoryItemWidget*> item_widget_array;

    UPROPERTY(EditDefaultsOnly)
    FItem_widget_array_2D item_widget_array_2D;

    // TODO: To be deleted when not used
    int current_item_selected_index{ 0 };

    int current_item_selected_row_index{ 0 };
    int current_item_selected_column_index{ 0 };
    int x0{ current_item_selected_row_index };
    int y0{ current_item_selected_column_index };
    int x1{ x0 };
    int y1{ y0 };

    int action_menu_index{ 0 };

    bool is_action_menu_displayed{ false };

protected:

    virtual bool Initialize() override;


};
