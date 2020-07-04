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
    for(int i = 0; i < MAX_NUMBER_OF_INVENTORY_ROWS; ++i)
    {
        item_widget_array.Add(FItem_widget_array());
    }

    is_struct_initialized = true;
}

TPair<int, int> FItem_widget_array_2D::add_item(class UDFLInventoryItemWidget *item)
{
    if(is_struct_initialized && item)
    {
        item_widget_array[ current_row_index ].insert_item(item);
        TPair<int, int> index_coordinate{ current_row_index, current_column_index };

        if(current_column_index < MAX_NUMBER_OF_INVENTORY_COLUMNS - 1)
        {
            current_column_index++;
        }else{
            current_column_index = 0;
            current_row_index++;
            if(current_row_index >= MAX_NUMBER_OF_INVENTORY_ROWS)
            {
                current_row_index = MAX_NUMBER_OF_INVENTORY_ROWS - 1;
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
    // This method defines what is going to be the item that will be highlighted when displaying the inventory.
    
    if(!item_widget_array_2D.is_empty())
    {
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
    int item_widget_array_size = item_widget_array.Num();

    // Remove highlight from current inventory item
    if(current_item_selected_index >= 0 && current_item_selected_index < item_widget_array_size)
    {
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        item->FrameSelector->SetOpacity(0.0f);
    }

    current_item_selected_index++;
    if(current_item_selected_index >= 0 && current_item_selected_index < item_widget_array_size)
    {
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        item->FrameSelector->SetOpacity(1.0f);
    }

    // If we are in the last item, keep it highlighted.
    if(item_widget_array_size > 0 && current_item_selected_index == item_widget_array_size)
    {
        current_item_selected_index = item_widget_array_size - 1;
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        item->FrameSelector->SetOpacity(1.0f);
    }
    UE_LOG(LogTemp, Warning, TEXT("select_item_to_the_east: %d"), current_item_selected_index);

    update_item_text_title_and_description();
}

void UDFLInventoryWidget::select_item_to_the_east1()
{
    /*
     * There are two situations when moving to the right:
     *
     *  - Case 1: The current position (x0, y0) and next position (x1, y1) reside in the same row. This means y0 == y1.
     *  - Case 2: The next position (x1, y1) is in a different row than the current position (x0, y0). This means x1 = x0 + 1.
     *
     */

    // Case 1:

    // Current position:
    int x0{ current_item_selected_row_index };
    int y0{ current_item_selected_column_index };

    // Next position
    int x1{ x0 + 1 };
    int y1{ y0 };

    current_item_selected_column_index--;
    if(current_item_selected_column_index >= 0)
    {
//        if(current_item_selected_row_index >= 0 && current_item_selected_row_index <= number_of_rows && current_item_selected_column_index >= 0 && current_item_selected_column_index <= number_of_columns)
        {
            UDFLInventoryItemWidget *item_to_be_removed = item_widget_array_2D[ current_item_selected_row_index ][ current_item_selected_column_index ];
        }
    }else{
        current_item_selected_column_index = 0;
    }
}

void UDFLInventoryWidget::select_item_to_the_west()
{
    int item_widget_array_size = item_widget_array.Num();

    // Remove highlight from current inventory item
    if(current_item_selected_index >= 0 && current_item_selected_index < item_widget_array_size)
    {
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        item->FrameSelector->SetOpacity(0.0f);
    }

    current_item_selected_index--;
    if(current_item_selected_index >= 0 && current_item_selected_index < item_widget_array_size)
    {
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        item->FrameSelector->SetOpacity(1.0f);
    }

    // If we are in the first item, keep it highlighted
    if(item_widget_array_size > 0 && current_item_selected_index < 0)
    {
        current_item_selected_index = 0;
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        item->FrameSelector->SetOpacity(1.0f);
    }
    UE_LOG(LogTemp, Warning, TEXT("select_item_to_the_west: %d"), current_item_selected_index);

    update_item_text_title_and_description();
}

void UDFLInventoryWidget::select_item_to_the_north()
{

}

void UDFLInventoryWidget::select_item_to_the_south()
{

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
    int number_of_rows = item_widget_array_2D.get_rows_number();
    int number_of_columns = item_widget_array_2D.get_columns_number();

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
            UE_LOG(LogTemp, Warning, TEXT("UDFLInventoryWidget::get_current_item_widget_selected. Valid Item"));
            return item;
        }
    }

    return nullptr;

    /*
    int item_widget_array_size{ item_widget_array.Num() };

    if(item_widget_array_size > 0 && current_item_selected_index >= 0 && current_item_selected_index < item_widget_array_size)
    {
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];

        if(item)
        {
            return item;
        }
    }

    return nullptr;
    */
}

int UDFLInventoryWidget::get_current_action_menu_index() const
{
    return action_menu_index;
}

void UDFLInventoryWidget::update_item_text_title_and_description()
{
    if(item_widget_array.Num() == 0)
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



















