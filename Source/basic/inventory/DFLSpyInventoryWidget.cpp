#include "DFLSpyInventoryWidget.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/PanelWidget.h"

#include <algorithm>

UDFLSpyInventoryWidget::UDFLSpyInventoryWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDFLSpyInventoryWidget::handle_keyboard_input(const FKey &key)
{
    // TODO: Change hardcoded keys here so in case the game's options allows to change keyboard shortcuts.
    if(key == EKeys::A)
    {
        // Move frame selector to left
        FString key_pressed = key.ToString();
        UE_LOG(LogTemp, Warning, TEXT("UDFLSpyInventoryWidget::handle_keyboard_input %s"), *key_pressed);

        frame_selectors_visibility_array[ current_camera_selected_index ] = false;
        current_camera_selected_index--;

        if(current_camera_selected_index < 0)
        {
            current_camera_selected_index = 0;
        }

        frame_selectors_visibility_array[ current_camera_selected_index ] = true;

        update_frame_selectors_visibility();
    }

    if(key == EKeys::D)
    {
        // Move frame selector to right
        FString key_pressed = key.ToString();
        UE_LOG(LogTemp, Warning, TEXT("UDFLSpyInventoryWidget::handle_keyboard_input %s"), *key_pressed);

        frame_selectors_visibility_array[ current_camera_selected_index ] = false;
        current_camera_selected_index++;

        if(current_camera_selected_index >= FRAME_SELECTORS_ARRAY_SIZE)
        {
            current_camera_selected_index = FRAME_SELECTORS_ARRAY_SIZE - 1;
        }

        frame_selectors_visibility_array[ current_camera_selected_index ] = true;

        update_frame_selectors_visibility();
    }

    if(key == EKeys::W)
    {
        // Move frame selector up
        FString key_pressed = key.ToString();
        UE_LOG(LogTemp, Warning, TEXT("UDFLSpyInventoryWidget::handle_keyboard_input %s"), *key_pressed);

        // We check that we are in the bottom line of cameras
        if(current_camera_selected_index >= 3 && current_camera_selected_index <= 5)
        {
            frame_selectors_visibility_array[ current_camera_selected_index ] = false;
            current_camera_selected_index -= (FRAME_SELECTORS_ARRAY_SIZE / 2);

            if(current_camera_selected_index < 0)
            {
                current_camera_selected_index = 0;
            }

            frame_selectors_visibility_array[ current_camera_selected_index ] = true;

            update_frame_selectors_visibility();
        }
    }

    if(key == EKeys::S)
    {
        // Move frame selector down
        FString key_pressed = key.ToString();
        UE_LOG(LogTemp, Warning, TEXT("UDFLSpyInventoryWidget::handle_keyboard_input %s"), *key_pressed);

        // We check that we are in the top line of cameras
        if(current_camera_selected_index >= 0 && current_camera_selected_index <= 2)
        {
            frame_selectors_visibility_array[ current_camera_selected_index ] = false;
            current_camera_selected_index += (FRAME_SELECTORS_ARRAY_SIZE / 2);

            if(current_camera_selected_index >= FRAME_SELECTORS_ARRAY_SIZE)
            {
                current_camera_selected_index = FRAME_SELECTORS_ARRAY_SIZE - 1;
            }

            frame_selectors_visibility_array[ current_camera_selected_index ] = true;

            update_frame_selectors_visibility();
        }
    }
}

void UDFLSpyInventoryWidget::set_components_initial_visualization()
{
    frame_selector_0->SetVisibility(ESlateVisibility::Visible);
    frame_selector_1->SetVisibility(ESlateVisibility::Hidden);
    frame_selector_2->SetVisibility(ESlateVisibility::Hidden);
    frame_selector_3->SetVisibility(ESlateVisibility::Hidden);
    frame_selector_4->SetVisibility(ESlateVisibility::Hidden);
    frame_selector_5->SetVisibility(ESlateVisibility::Hidden);

    current_camera_selected_index = 0;
    std::fill_n(frame_selectors_visibility_array.begin(), FRAME_SELECTORS_ARRAY_SIZE, false);
}

void UDFLSpyInventoryWidget::update_frame_selectors_visibility()
{
    for(int i = 0; i < FRAME_SELECTORS_ARRAY_SIZE; ++i)
    {
        UE_LOG(LogTemp, Warning, TEXT("UDFLSpyInventoryWidget::update_frame_selectors_visibility index: [ %d ], %s"), i, frame_selectors_visibility_array[ i ] ? TEXT("true") : TEXT("false"));
    }

    // Since the array is of a fixed size, we can visit any of its positions without being concern of exceeding limits
    frame_selector_0->SetVisibility( (frame_selectors_visibility_array[ 0 ] == true) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    frame_selector_1->SetVisibility( (frame_selectors_visibility_array[ 1 ] == true) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    frame_selector_2->SetVisibility( (frame_selectors_visibility_array[ 2 ] == true) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    frame_selector_3->SetVisibility( (frame_selectors_visibility_array[ 3 ] == true) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    frame_selector_4->SetVisibility( (frame_selectors_visibility_array[ 4 ] == true) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    frame_selector_5->SetVisibility( (frame_selectors_visibility_array[ 5 ] == true) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
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

    frame_selector_0->SetVisibility(ESlateVisibility::Visible);
    frame_selector_1->SetVisibility(ESlateVisibility::Hidden);
    frame_selector_2->SetVisibility(ESlateVisibility::Hidden);
    frame_selector_3->SetVisibility(ESlateVisibility::Hidden);
    frame_selector_4->SetVisibility(ESlateVisibility::Hidden);
    frame_selector_5->SetVisibility(ESlateVisibility::Hidden);
}

void UDFLSpyInventoryWidget::set_camera_marks_position()
{
    UPanelSlot *image_slot = image_floor_blueprint->Slot;
    if(image_slot)
    {
        UHorizontalBoxSlot *horizontal_box_slot = Cast<UHorizontalBoxSlot>(image_slot);

//        image_floor_blueprint->Brush.GetMargin().GetDesiredSize().ToString()
        UE_LOG(LogTemp, Warning, TEXT("UDFLSpyInventoryWidget::set_camera_marks_position ------WWW1--%s"), *image_floor_blueprint->Brush.ImageSize.ToString());
        UE_LOG(LogTemp, Warning, TEXT("UDFLSpyInventoryWidget::set_camera_marks_position ------WWW2--%s"), *image_floor_blueprint->Brush.GetMargin().GetDesiredSize().ToString());
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
