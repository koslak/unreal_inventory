#include "DFLInventoryComponent.h"
#include "DFLItem.h"

// Sets default values for this component's properties
UDFLInventoryComponent::UDFLInventoryComponent()
{
}


// Called when the game starts
void UDFLInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    for(auto& item : default_items_array)
    {
        add_item(item);
    }
}

bool UDFLInventoryComponent::add_item(UDFLItem *item)
{
    if(items_array.Num() >= capacity || !item)
    {
        return false;
    }

    item->owning_inventory = this;
    item->world = GetWorld();
    items_array.Add(item);

    // Update UI
    on_inventory_updated.Broadcast();

    return true;
}

bool UDFLInventoryComponent::remove_item(UDFLItem *item)
{
    if(item)
    {
        item->owning_inventory = nullptr;
        item->world = nullptr;
        items_array.RemoveSingle(item);
        on_inventory_updated.Broadcast();

        return true;
    }

    return false;
}


