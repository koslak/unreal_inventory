#include "DFLInventoryItem.h"

#include "Blueprint/UserWidget.h"

UDFLInventoryItem::UDFLInventoryItem()
{
    widget = CreateDefaultSubobject<UUserWidget>(TEXT("Widget"));
}

void UDFLInventoryItem::use()
{

}
