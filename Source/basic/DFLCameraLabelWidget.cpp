#include "DFLCameraLabelWidget.h"

#include "Components/TextBlock.h"

UDFLCameraLabelWidget::UDFLCameraLabelWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{

}

void UDFLCameraLabelWidget::set_text(FText text)
{
    LabelText->SetText(text);
}
