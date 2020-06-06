#include "DFLInventory.h"

#include "DFLInventoryItem.h"

UDFLInventory::UDFLInventory()
{
}

void UDFLInventory::BeginPlay()
{
    Super::BeginPlay();
}

bool UDFLInventory::add_item(UDFLInventoryItem *item)
{
    if(items_array.Num() >= capacity || !item)
    {
        return false;
    }

    items_array.Add(item);

    // Update UI
    // TODO: broadcast update event
    // on_inventory_updated.Broadcast();

    return true;
}

bool UDFLInventory::remove_item(UDFLInventoryItem *item)
{
    if(item)
    {
        items_array.RemoveSingle(item);

        // Update UI
        // TODO: broadcast update event
        // on_inventory_updated.Broadcast();

        return true;
    }

    return false;
}

void UDFLInventory::update_UI()
{

}




