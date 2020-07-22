#include "DFLSpyInventoryWidget.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/PanelWidget.h"

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

void UDFLSpyInventoryWidget::set_camera_marks_position()
{
    UPanelSlot *image_slot = image_floor_blueprint->Slot;
    if(image_slot)
    {
        UHorizontalBoxSlot *horizontal_box_slot = Cast<UHorizontalBoxSlot>(image_slot);
//        horizontal_box_slot->get
        UE_LOG(LogTemp, Warning, TEXT("UDFLSpyInventoryWidget::set_camera_marks_position ------WWW--%d"), horizontal_box_slot->Size.Value);
    }


    UPanelSlot *slot = marker_on_0->Slot;
    if(slot)
    {
        UCanvasPanelSlot *vertical_box_canvas_panel_slot = Cast<UCanvasPanelSlot>(slot);
        vertical_box_canvas_panel_slot->GetPosition();
        if(vertical_box_canvas_panel_slot)
        {
            UE_LOG(LogTemp, Warning, TEXT("UDFLSpyInventoryWidget::set_camera_marks_position -------------s"));
//            FVector2D item_widget_position = get_inventory_item_widget_position();
            vertical_box_canvas_panel_slot->SetPosition(FVector2D{50.0f, 50.0f});
        }
    }

    UPanelWidget* panel_widget_parent = image_floor_blueprint->GetParent();
    if(panel_widget_parent)
    {
        FVector2D Position1 = panel_widget_parent->GetCachedGeometry().AbsoluteToLocal(marker_on_0->GetCachedGeometry().GetAbsolutePosition()); // / 2.0f;
        UE_LOG(LogTemp, Warning, TEXT("UDFLSpyInventoryWidget::set_camera_marks_position A position: %s"), *marker_on_0->GetCachedGeometry().ToString());
        UE_LOG(LogTemp, Warning, TEXT("UDFLSpyInventoryWidget::set_camera_marks_position A position: %s"), *panel_widget_parent->GetCachedGeometry().ToString());

        Position1.X = Position1.X + marker_on_0->GetCachedGeometry().GetLocalSize().X + 10;

        UE_LOG(LogTemp, Warning, TEXT("UDFLSpyInventoryWidget::set_camera_marks_position B position: %s"), *Position1.ToString());
    }
}
