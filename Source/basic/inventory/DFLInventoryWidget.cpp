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

   if(CloseButton)
   {
       CloseButton->OnClicked.AddDynamic(this, &UDFLInventoryWidget::close_inventory);

   } else {
       return false;
   }

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
    UE_LOG(LogTemp, Warning, TEXT("Add.................."));
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
   UE_LOG(LogTemp, Warning, TEXT("show_action_menu.....0"));
   if(VerticalBox_Menu)
   {
       UE_LOG(LogTemp, Warning, TEXT("show_action_menu.....1"));
       UPanelSlot *slot = VerticalBox_Menu->Slot;
       if(slot)
       {
           UE_LOG(LogTemp, Warning, TEXT("show_action_menu.....2"));
           UCanvasPanelSlot *vertical_box_canvas_panel_slot = Cast<UCanvasPanelSlot>(slot);
           if(vertical_box_canvas_panel_slot)
           {
               UE_LOG(LogTemp, Warning, TEXT("show_action_menu.....3"));
               FVector2D item_widget_position = get_inventory_item_widget_position();

               if(!item_widget_position.IsZero())
               {
                   UE_LOG(LogTemp, Warning, TEXT("show_action_menu.....4"));
                   FVector2D action_menu_position{ FVector2D(item_widget_position.X + 60.0, item_widget_position.Y + 60.0f) };
                   vertical_box_canvas_panel_slot->SetPosition(action_menu_position);
               }
           }
       }

       VerticalBox_Menu->SetVisibility(ESlateVisibility::Visible);
   }
}

void UDFLInventoryWidget::hide_action_menu()
{
   if(VerticalBox_Menu)
   {
       VerticalBox_Menu->SetVisibility(ESlateVisibility::Hidden);
   }
}

void UDFLInventoryWidget::select_item_to_the_east()
{
    int item_widget_array_size = item_widget_array.Num();
    UE_LOG(LogTemp, Warning, TEXT("Right: current: %d, Array Size: %d"), current_item_selected_index, item_widget_array_size);

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

FVector2D UDFLInventoryWidget::get_inventory_item_widget_position()
{
    int item_widget_array_size = item_widget_array.Num();

    UE_LOG(LogTemp, Warning, TEXT("get_inventory_item_widget_position.....0"));
    if(item_widget_array_size > 0 && current_item_selected_index >= 0 && current_item_selected_index < item_widget_array_size)
    {
        UE_LOG(LogTemp, Warning, TEXT("get_inventory_item_widget_position....1"));
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        item->FrameSelector->SetOpacity(1.0f);

        UPanelSlot *slot = item->Slot;
        if(slot)
        {
            UE_LOG(LogTemp, Warning, TEXT("get_inventory_item_widget_position....2"));
            UCanvasPanelSlot *item_canvas_panel_slot = Cast<UCanvasPanelSlot>(slot);
            if(item_canvas_panel_slot)
            {
                UE_LOG(LogTemp, Warning, TEXT("get_inventory_item_widget_position....3"));
                FVector2D item_widget_position = item_canvas_panel_slot->GetPosition();
                UE_LOG(LogTemp, Warning, TEXT("item_widget_position X: %d, Y: %d"), item_widget_position.X, item_widget_position.Y);
                return item_widget_position;
            }
        }
    }

    return FVector2D(0.0f, 0.0f);
}



















