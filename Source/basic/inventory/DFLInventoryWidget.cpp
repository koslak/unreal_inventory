#include "DFLInventoryWidget.h"

#include "DFLInventoryItemWidget.h"
#include "Components/Button.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Components/Image.h"

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
    current_item_selected_index = 0;

    // Highlight the first inventory item
    if(item_widget_array.Num() > 0)
    {
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        if(item)
        {
            item->FrameSelector->SetOpacity(1.0f);
        }
    }
}

void UDFLInventoryWidget::hide_inventory()
{
    this->SetVisibility(ESlateVisibility::Hidden);
    current_item_selected_index = 0;

    // TODO: Clear the highlight from all items in the inventory except for the first item.
    int first_index{ 0 };
    for (auto& item : item_widget_array)
    {
        if(first_index == 0)
        {
            item->FrameSelector->SetOpacity(1.0f);
            first_index++;
        }else{
            item->FrameSelector->SetOpacity(0.0f);
        }
    }
}

void UDFLInventoryWidget::select_item_to_the_right()
{
    // Remove highlight from current inventory item
    if(current_item_selected_index < item_widget_array.Num())
    {
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        if(item)
        {
            item->FrameSelector->SetOpacity(0.0f);
        }
    }

    current_item_selected_index++;
    if(current_item_selected_index < item_widget_array.Num())
    {
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        if(item)
        {
            item->FrameSelector->SetOpacity(1.0f);
        }
    }else{
        // Highlight the last element
        current_item_selected_index = item_widget_array.Num() - 1;
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        if(item)
        {
            item->FrameSelector->SetOpacity(1.0f);
        }
    }
}

void UDFLInventoryWidget::select_item_to_the_left()
{
    // Remove highlight from current inventory item
    if(current_item_selected_index >= 0)
    {
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        if(item)
        {
            item->FrameSelector->SetOpacity(0.0f);
        }
    }

    current_item_selected_index--;
    if(current_item_selected_index >= 0)
    {
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        if(item)
        {
            item->FrameSelector->SetOpacity(1.0f);
        }
    }else{
        // Highlight the first element
        current_item_selected_index = 0;
        UDFLInventoryItemWidget *item = item_widget_array[ current_item_selected_index ];
        if(item)
        {
            item->FrameSelector->SetOpacity(1.0f);
        }
    }

}



















