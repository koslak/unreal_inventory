#include "DFLCameraHolderActor.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "UObject/ConstructorHelpers.h"
#include "DFLCameraLabelWidget.h"

ADFLCameraHolderActor::ADFLCameraHolderActor()
{
    this->SetActorTickEnabled(true);

    ConstructorHelpers::FClassFinder<UDFLCameraLabelWidget> DFLCamera_Label_Widget_BP(TEXT("/Game/Blueprints/CameraLabelWidget_BP"));

    if(DFLCamera_Label_Widget_BP.Class)
    {
        DFLCamera_Label_Widget_class = DFLCamera_Label_Widget_BP.Class;
    }
}

void ADFLCameraHolderActor::BeginPlay()
{
    Super::BeginPlay();

    UUserWidget *general_widget{ nullptr };
    general_widget = CreateWidget<UUserWidget>(GetWorld(), DFLCamera_Label_Widget_class);

    if(general_widget && general_widget->IsA(UDFLCameraLabelWidget::StaticClass()))
    {
        camera_label_widget = Cast<UDFLCameraLabelWidget>(general_widget);

        if(camera_label_widget && widget_component)
        {
            camera_label_widget->set_text(FText::FromString(TEXT("Attach Camera")));
            widget_component->SetWidget(camera_label_widget);
        }
    }

    if(widget_component)
    {
        widget_component->SetVisibility(false);
        widget_component->SetRelativeLocation(FVector(0.0f, 0.0f, widget_height));
    }
}

void ADFLCameraHolderActor::OnUsed(APawn *)
{
    UGameplayStatics::PlaySoundAtLocation(this, pickup_sound, GetActorLocation());
}

void ADFLCameraHolderActor::set_camera(USceneCaptureComponent2D *in_game_camera)
{
    camera = in_game_camera;

    if(camera && mesh_component)
    {
        camera->AttachToComponent(mesh_component, FAttachmentTransformRules::SnapToTargetIncludingScale);
        camera->SetRelativeRotation(FRotator{-30.0f, 180.0f, 0.0f});
        camera_label_widget->set_text(FText::FromString(TEXT("Remove Camera")));
    }
}

void ADFLCameraHolderActor::remove_camera()
{
    if(camera)
    {
        camera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
        camera_label_widget->set_text(FText::FromString(TEXT("Attach Camera")));
    }
}





