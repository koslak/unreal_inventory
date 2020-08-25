// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <array>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DFLSpyInventoryWidget.generated.h"

UCLASS()
class BASIC_API UDFLSpyInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

 public:
    UDFLSpyInventoryWidget(const FObjectInitializer& ObjectInitializer);

    void hide_camera_3();
    void enable_camera_by_index(int index);
    void disable_camera_by_index(int index);
    void disable_all_cameras();
    void set_camera_marks_position();

    void handle_keyboard_input(const struct FKey &key);
    void set_components_initial_visualization();

 private:
    void update_frame_selectors_visibility();

    int current_camera_selected_index{ 0 };
    static constexpr const int FRAME_SELECTORS_ARRAY_SIZE{ 6 };
    std::array<bool, FRAME_SELECTORS_ARRAY_SIZE> frame_selectors_visibility_array;

    UPROPERTY(meta = (BindWidget))
    class UImage *image_cam_0;

    UPROPERTY(meta = (BindWidget))
    class UImage *image_cam_1;

    UPROPERTY(meta = (BindWidget))
    class UImage *image_cam_2;

    UPROPERTY(meta = (BindWidget))
    class UImage *image_cam_3;

    UPROPERTY(meta = (BindWidget))
    class UImage *image_cam_4;

    UPROPERTY(meta = (BindWidget))
    class UImage *image_cam_5;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *text_cam_0;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *text_cam_1;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *text_cam_2;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *text_cam_3;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *text_cam_4;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock *text_cam_5;

    // Camera Markers

    UPROPERTY(meta = (BindWidget))
    class UImage *image_floor_blueprint;

    UPROPERTY(meta = (BindWidget))
    class UImage *marker_on_0;

    UPROPERTY(meta = (BindWidget))
    class UImage *marker_on_1;

    UPROPERTY(meta = (BindWidget))
    class UImage *marker_on_2;

    UPROPERTY(meta = (BindWidget))
    class UImage *marker_on_3;

    UPROPERTY(meta = (BindWidget))
    class UImage *marker_on_4;

    UPROPERTY(meta = (BindWidget))
    class UImage *marker_on_5;

    // Frame Selectors

    UPROPERTY(meta = (BindWidget))
    class UImage *frame_selector_0;

    UPROPERTY(meta = (BindWidget))
    class UImage *frame_selector_1;

    UPROPERTY(meta = (BindWidget))
    class UImage *frame_selector_2;

    UPROPERTY(meta = (BindWidget))
    class UImage *frame_selector_3;

    UPROPERTY(meta = (BindWidget))
    class UImage *frame_selector_4;

    UPROPERTY(meta = (BindWidget))
    class UImage *frame_selector_5;
};
