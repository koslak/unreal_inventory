#include "DFLInventoryWidget.h"

#include "DFLInventoryItemWidget.h"
#include "../DFLUsableActor.h"
#include "Components/Button.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridSlot.h"
#include "Components/GridPanel.h"

void FItem_widget_array_2D::initialize()
{
    int number_of_rows{ this->get_rows_number() };

    for(int i = 0; i < number_of_rows; ++i)
    {
        item_widget_array.Add(FItem_widget_array());
    }

    is_struct_initialized = true;
}

TPair<int, int> FItem_widget_array_2D::add_item(class UDFLInventoryItemWidget *item)
{
    if(!is_struct_initialized)
    {
        UE_LOG(LogTemp, Error, TEXT("FItem_widget_array_2D::add_item -> The FItem_widget_array struct has not been initialized. Call the method: FItem_widget_array_2D::initialize first"));
        return TPair<int, int>{ 0, 0 };
    }

    if(item)
    {
        int number_of_rows{ this->get_rows_number() };
        int number_of_columns{ this->get_columns_number() };

        item_widget_array[ current_row_index ].insert_item(item);
        TPair<int, int> index_coordinate{ current_row_index, current_column_index };

        if(current_column_index < number_of_columns - 1)
        {
            current_column_index++;

        }else{
            current_column_index = 0;
            current_row_index++;

            if(current_row_index >= number_of_rows)
            {
                current_row_index = number_of_rows - 1;
            }
        }

        return index_coordinate;
    }

    return TPair<int, int>{ 0, 0 };
}

bool FItem_widget_array_2D::remove_item(int row, int column)
{
    if(row >= 0 && row <= current_row_index && column >= 0 && column <= current_column_index)
    {
        UDFLInventoryItemWidget *item_to_be_removed = item_widget_array[ row ][ column ];
        if(item_to_be_removed)
        {
            item_widget_array[ row ].remove_item(item_to_be_removed);

            return true;
        }
    }

    return false;
}

FItem_widget_array &FItem_widget_array_2D::operator[](int32 i)
{
    check(i >= 0 && i < item_widget_array.Num());

    return item_widget_array[ i ];
}

void FItem_widget_array_2D::remove_item(class UDFLInventoryItemWidget *item)
{
}

int FItem_widget_array_2D::get_rows_number()
{
    return MAX_NUMBER_OF_INVENTORY_ROWS;
}

int FItem_widget_array_2D::get_columns_number()
{
    return MAX_NUMBER_OF_INVENTORY_COLUMNS;
}

bool FItem_widget_array_2D::is_empty()
{
    return  item_widget_array.Num() == 0 ? true : false;
}

UDFLInventoryWidget::UDFLInventoryWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    ConstructorHelpers::FClassFinder<UDFLInventoryItemWidget> DFLInventory_item_widget_BP(TEXT("/Game/Blueprints/inventory/inventory_item_WBP"));
    if(DFLInventory_item_widget_BP.Class)
    {
        DFLInventory_item_widget_class = DFLInventory_item_widget_BP.Class;
    }
}

bool UDFLInventoryWidget::Initialize()
{
    bool super_initialized_successfully{ Super::Initialize() };

    if(!super_initialized_successfully)
    {
        return false;
    }

    item_widget_array_2D.initialize();

   if(VerticalBox_Menu)
   {
       VerticalBox_Menu->SetVisibility(ESlateVisibility::Hidden);
   }

    return true;
}

bool UDFLInventoryWidget::add_item(UDFLInventoryItemWidget *item)
{
    if(!item)
    {
        return false;
    }

    TPair<int, int> index_pair = item_widget_array_2D.add_item(item);

    int row{ index_pair.Key };
    int column{ index_pair.Value };

    UE_LOG(LogTemp, Warning, TEXT("Row: %d, Col: %d"), row, column);

    if(InventoryGridPanel)
    {
        InventoryGridPanel->AddChildToGrid(item, row, column);
    }
    else {
        return false;
    }

    return true;
}

bool UDFLInventoryWidget::remove_current_selected_item()
{
    UDFLInventoryItemWidget *current_selected_item = get_current_item_widget_selected();
    if(current_selected_item)
    {
        item_widget_array.Remove(current_selected_item);
        item_widget_array_2D.remove_item(current_item_selected_row_index, current_item_selected_column_index);

        if(InventoryGridPanel)
        {
            if(InventoryGridPanel->RemoveChild(current_selected_item))
            {
                select_item_to_the_west();

                return true;
            }
        }
    }

    return false;
}

bool UDFLInventoryWidget::is_action_menu_can_be_displayed()
{
    if(!item_widget_array_2D.is_empty())
    {
        return true;
    }

    return false;
}

void UDFLInventoryWidget::set_initial_highlighted_item()
{
    if(!item_widget_array_2D.is_empty())
    {
        if(!is_item_widget_being_examined)
        {
            UDFLInventoryItemWidget *current_item_widget_selected = get_current_item_widget_selected();
            if(current_item_widget_selected)
            {
                current_item_widget_selected->FrameSelector->SetOpacity(0.0f);
            }

            // If the array is not empty, it's safe to access the first row: 0, col: 0, index.
            current_item_selected_row_index = 0;
            current_item_selected_column_index = 0;

            UDFLInventoryItemWidget *item = item_widget_array_2D[ current_item_selected_row_index ][ current_item_selected_column_index ];
            if(item)
            {
                item->FrameSelector->SetOpacity(1.0f);
            }
        }
    }
}

void UDFLInventoryWidget::show_inventory()
{
    this->SetVisibility(ESlateVisibility::Visible);

    set_initial_highlighted_item();

    update_item_text_title_and_description();
    VerticalBox_Menu->SetVisibility(ESlateVisibility::Hidden);
}

void UDFLInventoryWidget::hide_inventory()
{
    this->SetVisibility(ESlateVisibility::Hidden);

    // Clear the highlight from all items in the inventory.
    for (auto& item : item_widget_array)
    {
        item->FrameSelector->SetOpacity(0.0f);
    }
}

void UDFLInventoryWidget::show_action_menu()
{
if(VerticalBox_Menu)
{
   UPanelSlot *slot = VerticalBox_Menu->Slot;
       if(slot)
       {
           UCanvasPanelSlot *vertical_box_canvas_panel_slot = Cast<UCanvasPanelSlot>(slot);
           if(vertical_box_canvas_panel_slot)
           {
               FVector2D item_widget_position = get_inventory_item_widget_position();
               vertical_box_canvas_panel_slot->SetPosition(item_widget_position);
           }
       }

       action_menu_index = 0;
       is_action_menu_displayed = true;
       update_action_menu_selection(action_menu_index);

       VerticalBox_Menu->SetVisibility(ESlateVisibility::Visible);
   }
}

void UDFLInventoryWidget::hide_action_menu()
{
   if(VerticalBox_Menu)
   {
       VerticalBox_Menu->SetVisibility(ESlateVisibility::Hidden);

       is_action_menu_displayed = false;
       action_menu_index = 0;
       update_action_menu_selection(action_menu_index);
   }
}

void UDFLInventoryWidget::update_action_menu_selection(int action_menu_index_value)
{
    switch(action_menu_index_value)
    {
        case 0:
        {
            Image_Frame->SetOpacity(0.4f);
            Image_Frame_1->SetOpacity(0.0f);
            Image_Frame_2->SetOpacity(0.0f);
        }
        break;

        case 1:
        {
            Image_Frame->SetOpacity(0.0f);
            Image_Frame_1->SetOpacity(0.4f);
            Image_Frame_2->SetOpacity(0.0f);
        }
        break;

        case 2:
        {
            Image_Frame->SetOpacity(0.0f);
            Image_Frame_1->SetOpacity(0.0f);
            Image_Frame_2->SetOpacity(0.4f);
        }
        break;
    }
}

void UDFLInventoryWidget::select_item_to_the_east()
{
    /*
     * There are two situations when moving to the right:
     *
     *  - Case 1: The current position (x0, y0) and next position (x1, y1) reside in the same row. This means: x0 == x1.
     *  - Case 2: The next position (x1, y1) is in a different row than the current position (x0, y0). This means: y1 = y0 + 1.
     */

    // Common variables to both cases:
    int number_of_rows{ item_widget_array_2D.get_rows_number() };
    int number_of_columns{ item_widget_array_2D.get_columns_number() };
    x0 = current_item_selected_row_index;
    y0 = current_item_selected_column_index;

    UE_LOG(LogTemp, Warning, TEXT("UDFLInventoryWidget::select_item_to_the_east1: {current_item_selected_row_index = %d, current_item_selected_column_index = %d}"), current_item_selected_row_index, current_item_selected_column_index);

    // We need to validate which case we are facing
    if(y0 == number_of_columns - 1)  // This means we are in the last column. Note: y0 will never be equal to the number_of_columns
    {
        // This is Case 2.
        x1 = x0 + 1;
        y1 = 0;

        // We need to validate if we are in the last row
        if(x1 == number_of_rows)
        {
            x1 = number_of_rows - 1;
        }
    }else{
        // This is Case 1.
        x1 = x0;
        y1 = y0 + 1;

        // We need to validate if we are in the last column
        if(y1 == number_of_columns)
        {
            y1 = number_of_columns - 1;
        }
    }

    change_item_selection();
    update_item_text_title_and_description();
}

void UDFLInventoryWidget::select_item_to_the_west()
{
    /*
     * There are two situations when moving to the right:
     *
     *  - Case 1: The current position (x0, y0) and next position (x1, y1) reside in the same row. This means: x0 == x1.
     *  - Case 2: The next position (x1, y1) is in a different row than the current position (x0, y0). This means: y1 = number_of_columns - 1.
     */

    int number_of_columns{ item_widget_array_2D.get_columns_number() };
    x0 = current_item_selected_row_index;
    y0 = current_item_selected_column_index;

    UE_LOG(LogTemp, Warning, TEXT("UDFLInventoryWidget::select_item_to_the_east1: {current_item_selected_row_index = %d, current_item_selected_column_index = %d}"), current_item_selected_row_index, current_item_selected_column_index);

    if(x0 == 0 && y0 == 0)
    {
        x1 = x0;
        y1 = y0;

        current_item_selected_row_index = x1;
        current_item_selected_column_index = y1;
    }
    else{
        // We need to validate which case we are facing
        if(y0 == 0)  // This means we are in the first column.
        {
            // This is Case 2.
            x1 = x0 - 1;
            y1 = number_of_columns - 1;

            // We need to validate if we are behind the first row
            if(x1 < 0)
            {
                x1 = 0;
            }
        }else{
            // This is Case 1.
            x1 = x0;
            y1 = y0 - 1;

            // We need to validate if we are in the first column
            if(y1 < 0)
            {
                y1 = 0;
            }
        }

        change_item_selection();
    }

    update_item_text_title_and_description();
}

void UDFLInventoryWidget::select_item_to_the_north()
{

}

void UDFLInventoryWidget::select_item_to_the_south()
{

}

void UDFLInventoryWidget::change_item_selection()
{
    int number_of_rows{ item_widget_array_2D.get_rows_number() };
    int number_of_columns{ item_widget_array_2D.get_columns_number() };

    UE_LOG(LogTemp, Warning, TEXT("UDFLInventoryWidget::select_item_to_the_east1: {x0 = %d, y0 = %d}, {x1 = %d, y1 = %d}"), x0, y0, x1, y1);

    if(x0 >= 0 && x0 < number_of_rows    && x1 >= 0 && x1 < number_of_rows &&
       y0 >= 0 && y0 < number_of_columns && y1 >= 0 && y1 < number_of_columns)
    {
        UDFLInventoryItemWidget *current_item = item_widget_array_2D[ x0 ][ y0 ];
        UDFLInventoryItemWidget *next_item = item_widget_array_2D[ x1 ][ y1 ];

        if(current_item && next_item)
        {
            current_item_selected_row_index = x1;
            current_item_selected_column_index = y1;

            current_item->FrameSelector->SetOpacity(0.0f);
            next_item->FrameSelector->SetOpacity(1.0f);
        }
    }
}

void UDFLInventoryWidget::select_action_menu_up()
{
    if(is_action_menu_displayed)
    {
        action_menu_index--;
        if(action_menu_index <= 0)
        {
            action_menu_index = 0;
        }

        update_action_menu_selection(action_menu_index);
    }
}

void UDFLInventoryWidget::select_action_menu_down()
{
    if(is_action_menu_displayed)
    {
        action_menu_index++;
        if(action_menu_index >= 2)
        {
            action_menu_index = 2;
        }

        update_action_menu_selection(action_menu_index);
    }
}

void UDFLInventoryWidget::execute_action_menu_command()
{
//    action_menu_delegate.ExecuteIfBound(action_menu_index);
}

UDFLInventoryItemWidget *UDFLInventoryWidget::get_current_item_widget_selected()
{
    int number_of_rows{ item_widget_array_2D.get_rows_number() };
    int number_of_columns{ item_widget_array_2D.get_columns_number() };

    UE_LOG(LogTemp, Warning, TEXT("UDFLInventoryWidget::get_current_item_widget_selected. number_of_rows: %d, number_of_columns: %d"), number_of_rows, number_of_columns);

    if(!item_widget_array_2D.is_empty() &&
       current_item_selected_row_index >= 0 &&
       current_item_selected_row_index < number_of_rows &&
       current_item_selected_column_index >= 0 &&
       current_item_selected_column_index < number_of_columns)
    {
        UDFLInventoryItemWidget *item = item_widget_array_2D[ current_item_selected_row_index ][ current_item_selected_column_index ];

        UE_LOG(LogTemp, Warning, TEXT("UDFLInventoryWidget::get_current_item_widget_selected. current_item_selected_row_index: %d, current_item_selected_column_index: %d"), current_item_selected_row_index, current_item_selected_column_index);
        if(item)
        {
            return item;
        }
    }

    return nullptr;
}

int UDFLInventoryWidget::get_current_action_menu_index() const
{
    return action_menu_index;
}

void UDFLInventoryWidget::update_item_text_title_and_description()
{
    if(item_widget_array_2D.is_empty())
    {
        ItemTitle->SetText(FText::FromString(""));
        ItemDescription->SetText(FText::FromString(""));
    }
    else {
        UDFLInventoryItemWidget *current_item_widget_selected = get_current_item_widget_selected();
        if(current_item_widget_selected)
        {
            ADFLUsableActor *current_item_widget_actor = current_item_widget_selected->parent_actor;
            if(current_item_widget_actor)
            {
                ItemTitle->SetText(current_item_widget_actor->item_widget_display_name);
                ItemDescription->SetText(current_item_widget_actor->item_widget_description_text);
            }
        }
    }
}

FVector2D UDFLInventoryWidget::get_inventory_item_widget_position()
{
    UDFLInventoryItemWidget *item = get_current_item_widget_selected();
    if(item)
    {
        UPanelWidget* panel_widget_parent = VerticalBox_Menu->GetParent();
        if(panel_widget_parent)
        {
            const int distance_between_selected_item_and_action_menu{ 10 };
            FVector2D position = panel_widget_parent->GetCachedGeometry().AbsoluteToLocal(item->VerticalBox_Item->GetCachedGeometry().GetAbsolutePosition());
            position.X = position.X + item->VerticalBox_Item->GetCachedGeometry().GetLocalSize().X + distance_between_selected_item_and_action_menu;

            return position;
        }
    }

    return FVector2D(0.0f, 0.0f);
}



















