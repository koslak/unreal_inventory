#include "DFLFoodItem.h"
#include "../DFLCharacter.h"
#include "DFLInventoryComponent.h"

void UDFLFoodItem::use(ADFLCharacter *character)
{
    if(character)
    {
        character->health += this->health_to_heal;

        if(owning_inventory)
        {
            owning_inventory->remove_item(this);
        }
    }
}
