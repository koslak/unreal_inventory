#include "DFLSpyInventoryWidget.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

UDFLSpyInventoryWidget::UDFLSpyInventoryWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDFLSpyInventoryWidget::hide_camera_3()
{
    image_cam_3->SetVisibility(ESlateVisibility::Hidden);
}

void UDFLSpyInventoryWidget::enable_camera_by_index(int index)
{
    switch(index)
    {
        case 0:
            image_cam_0->SetColorAndOpacity(FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f });
            text_cam_0->SetVisibility(ESlateVisibility::Hidden);
        break;
        case 1:
            image_cam_1->SetColorAndOpacity(FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f });
            text_cam_1->SetVisibility(ESlateVisibility::Hidden);
        break;
        case 2:
            image_cam_2->SetColorAndOpacity(FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f });
            text_cam_2->SetVisibility(ESlateVisibility::Hidden);
        break;
        case 3:
            image_cam_3->SetColorAndOpacity(FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f });
            text_cam_3->SetVisibility(ESlateVisibility::Hidden);
        break;
        case 4:
            image_cam_4->SetColorAndOpacity(FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f });
            text_cam_4->SetVisibility(ESlateVisibility::Hidden);
        break;
        case 5:
            image_cam_5->SetColorAndOpacity(FLinearColor{ 1.0f, 1.0f, 1.0f, 1.0f });
            text_cam_5->SetVisibility(ESlateVisibility::Hidden);
        break;
    }
}

void UDFLSpyInventoryWidget::disable_camera_by_index(int index)
{
    switch(index)
    {
        case 0:
            image_cam_0->SetColorAndOpacity(FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
            text_cam_0->SetVisibility(ESlateVisibility::Visible);
        break;
        case 1:
            image_cam_1->SetColorAndOpacity(FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
            text_cam_1->SetVisibility(ESlateVisibility::Visible);
        break;
        case 2:
            image_cam_2->SetColorAndOpacity(FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
            text_cam_2->SetVisibility(ESlateVisibility::Visible);
        break;
        case 3:
            image_cam_3->SetColorAndOpacity(FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
            text_cam_3->SetVisibility(ESlateVisibility::Visible);
        break;
        case 4:
            image_cam_4->SetColorAndOpacity(FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
            text_cam_4->SetVisibility(ESlateVisibility::Visible);
        break;
        case 5:
            image_cam_5->SetColorAndOpacity(FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
            text_cam_5->SetVisibility(ESlateVisibility::Visible);
        break;
    }

}

void UDFLSpyInventoryWidget::disable_all_cameras()
{
    image_cam_0->SetColorAndOpacity(FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
    image_cam_1->SetColorAndOpacity(FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
    image_cam_2->SetColorAndOpacity(FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
    image_cam_3->SetColorAndOpacity(FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
    image_cam_4->SetColorAndOpacity(FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });
    image_cam_5->SetColorAndOpacity(FLinearColor{ 0.0f, 0.0f, 0.0f, 1.0f });

    text_cam_0->SetVisibility(ESlateVisibility::Visible);
    text_cam_1->SetVisibility(ESlateVisibility::Visible);
    text_cam_2->SetVisibility(ESlateVisibility::Visible);
    text_cam_3->SetVisibility(ESlateVisibility::Visible);
    text_cam_4->SetVisibility(ESlateVisibility::Visible);
    text_cam_5->SetVisibility(ESlateVisibility::Visible);
}
