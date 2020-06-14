#include "DFLInventoryWidget.h"

#include "DFLInventoryItemWidget.h"
#include "Components/Button.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/CanvasPanelSlot.h"

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

    /*
   if(CloseButton)
   {
       CloseButton->OnClicked.AddDynamic(this, &UDFLInventoryWidget::close_inventory);

   } else {
       return false;
   }
   */

   if(VerticalBox_Menu)
   {
       VerticalBox_Menu->SetVisibility(ESlateVisibility::Hidden);
   }

    return true;
}

void UDFLInventoryWidget::close_inventory()
{
    UE_LOG(LogTemp, Warning, TEXT("close inventory function called"));

    UUserWidget *general_widget{ nullptr };
    general_widget = CreateWidget<UUserWidget>(GetWorld(), DFLInventory_item_widget_class);

    if(general_widget && general_widget->IsA(UDFLInventoryItemWidget::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Widget is a UDFLInventoryItemWidget"));

        UDFLInventoryItemWidget *inventoryItemWidget = Cast<UDFLInventoryItemWidget>(general_widget);

        if(inventoryItemWidget)
        {
            item_widget_array.Add(inventoryItemWidget);

            UE_LOG(LogTemp, Warning, TEXT("Cast successful"));
            inventoryItemWidget->ItemName->SetText(FText::FromString("Case Blue"));

            if(InventoryBox)
            {
                UE_LOG(LogTemp, Warning, TEXT("Inventory Box exists!"));
                InventoryBox->AddChildToWrapBox(inventoryItemWidget);
            }

        }
    }
}

bool UDFLInventoryWidget::add_item(UDFLInventoryItemWidget *item)
{
    if(!item)
    {
        return false;
    }

    item_widget_array.Add(item);

    if(InventoryBox)
    {
        InventoryBox->AddChildToWrapBox(item);

    }else{
        return false;
    }

    return true;
}

void UDFLInventoryWidget::show_inventory()
{
    this->SetVisibility(ESlateVisibility::Visible);

    // Highlight the first inventory item
    if(item_widget_array.Num() > 0)
    {
        current_item_selected_index = 0;
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        item->FrameSelector->SetOpacity(1.0f);
    }

    VerticalBox_Menu->SetVisibility(ESlateVisibility::Hidden);
}

void UDFLInventoryWidget::hide_inventory()
{
    this->SetVisibility(ESlateVisibility::Hidden);
    current_item_selected_index = 0;

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
        Image_Frame->SetOpacity(0.4f);
        Image_Frame_1->SetOpacity(0.0f);
        Image_Frame_2->SetOpacity(0.0f);
        break;

    case 1:
        Image_Frame->SetOpacity(0.0f);
        Image_Frame_1->SetOpacity(0.4f);
        Image_Frame_2->SetOpacity(0.0f);
        break;

    case 2:
        Image_Frame->SetOpacity(0.0f);
        Image_Frame_1->SetOpacity(0.0f);
        Image_Frame_2->SetOpacity(0.4f);
        break;
    }
}

void UDFLInventoryWidget::select_item_to_the_east()
{
    int item_widget_array_size = item_widget_array.Num();
//    UE_LOG(LogTemp, Warning, TEXT("Right: current: %d, Array Size: %d"), current_item_selected_index, item_widget_array_size);

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
    switch(action_menu_index)
    {
        case 0:
            UE_LOG(LogTemp, Warning, TEXT("ACTION 0!!!!!!!!!!!!!!!!!!!!!!!!!"));
        break;

        case 1:
        {
            UE_LOG(LogTemp, Warning, TEXT("ACTION 1!!!!!!!!!!!!!!!!!!!!!!!!!"));
        }
        break;

        case 2:
            UE_LOG(LogTemp, Warning, TEXT("ACTION 2!!!!!!!!!!!!!!!!!!!!!!!!!"));
        break;
    }

}

UDFLInventoryItemWidget *UDFLInventoryWidget::get_current_item_widget_selected()
{
    int item_widget_array_size = item_widget_array.Num();

    if(item_widget_array_size > 0)
    {
        current_item_selected_index = 0;
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];

        if(item)
        {
            return item;
        }
    }

    return nullptr;
}

FVector2D UDFLInventoryWidget::get_inventory_item_widget_position()
{
    int item_widget_array_size = item_widget_array.Num();

    if(item_widget_array_size > 0 && current_item_selected_index >= 0 && current_item_selected_index < item_widget_array_size)
    {
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];

        UPanelWidget* panel_widget_parent = VerticalBox_Menu->GetParent();
        if(panel_widget_parent)
        {
            FVector2D Position1 = panel_widget_parent->GetCachedGeometry().AbsoluteToLocal(item->VerticalBox_Item->GetCachedGeometry().GetAbsolutePosition()); // / 2.0f;
            Position1.X = Position1.X + item->VerticalBox_Item->GetCachedGeometry().GetLocalSize().X + 10;
            return Position1;
        }
    }

    return FVector2D(0.0f, 0.0f);
}



















