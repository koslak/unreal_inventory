#include "DFLSpyInventoryWidget.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/Image.h"

UDFLSpyInventoryWidget::UDFLSpyInventoryWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDFLSpyInventoryWidget::hide_camera_3()
{
    image_cam_3->SetVisibility(ESlateVisibility::Hidden);
}
