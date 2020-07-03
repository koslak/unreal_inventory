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
    /*
    class UDFLInventoryItemWidget *operator[] (int32 i) 
    {
        if(i >= 0 && i < items_array.Num())
        {
            return items_array[ i ];
        }

        return nullptr;
    }
    */

    void insert_item(class UDFLInventoryItemWidget *item)
    {
        if(item)
        {
            items_array.Add(item);
        }
    }

    int get_number_items()
    {
        return items_array.Num();
    }

private:
    UPROPERTY(EditDefaultsOnly)
    TArray<class UDFLInventoryItemWidget *> items_array;
};

USTRUCT()
struct FItem_widget_array_2D 
{
    GENERATED_BODY()

public:
    void initialize()
    {
        for(int i = 0; i < MAX_NUMBER_OF_INVENTORY_ROWS; ++i)
        {
            item_widget_array.Add(FItem_widget_array());
        }

        is_struct_initialized = true;
    }

    TPair<int, int> Add(class UDFLInventoryItemWidget *item)
    {
        if(is_struct_initialized && item)
        {
            item_widget_array[ current_row_index ].insert_item(item);
            TPair<int, int> index_coordinate{ current_row_index, current_column_index };

            current_column_index++;
            if(current_column_index == MAX_NUMBER_OF_INVENTORY_ROWS)
            {
                current_column_index = 0;
                current_row_index++;
                if(current_row_index >= item_widget_array.Num())
                {
                    current_row_index = item_widget_array.Num() - 1;
                }
            }

            return index_coordinate;
        }

        return TPair<int, int>{ 0, 0 };
    }

    int get_rows_number()
    {
        return current_row_index;
    }

    int get_columns_number()
    {
        return current_column_index;
    }

private:
    UPROPERTY(EditDefaultsOnly)
    TArray<FItem_widget_array> item_widget_array;

    bool is_struct_initialized{ false };
    int current_row_index{ 0 };
    int current_column_index{ 0 };
    int MAX_NUMBER_OF_INVENTORY_ROWS{ 5 };
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
    void select_item_to_the_west();
    void select_item_to_the_north();
    void select_item_to_the_south();
    void select_action_menu_up();
    void select_action_menu_down();
    void execute_action_menu_command();
    UDFLInventoryItemWidget *get_current_item_widget_selected();
    int get_current_action_menu_index() const;
    void update_item_text_title_and_description();
    void set_initial_highlighted_item();

private:
    FVector2D get_inventory_item_widget_position();
    void update_action_menu_selection(int action_menu_index_value);

    UPROPERTY(meta = (BindWidget))
    class UWrapBox *InventoryBox;

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

    int index_row{ 0 };
    int index_column{ 0 };

    int current_item_selected_index{ 0 };
    int action_menu_index{ 0 };

    bool is_action_menu_displayed{ false };
    bool is_item_widget_being_examined{ false };

protected:

    virtual bool Initialize() override;


};
