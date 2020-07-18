#pragma once

#include "CoreMinimal.h"
#include "DFLUsableActor.h"
#include "DFLCameraHolderActor.generated.h"

UCLASS()
class BASIC_API ADFLCameraHolderActor : public ADFLUsableActor
{
	GENERATED_BODY()
	
    void BeginPlay() override;

protected:
    ADFLCameraHolderActor();

public:
    virtual void OnUsed(APawn* InstigatorPawn) override;
    void attach_camera(class USceneCaptureComponent2D *in_game_camera);
    class USceneCaptureComponent2D *detach_camera();

    UPROPERTY(EditAnywhere, DisplayName="Pick Up Sound", Category = "Sound")
    class USoundCue* pickup_sound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Configuration")
    FText widget_text;

private:
    UPROPERTY(EditDefaultsOnly)
    class USceneCaptureComponent2D *camera{ nullptr };

    UPROPERTY(EditDefaultsOnly)
    class UDFLCameraLabelWidget *camera_label_widget;

    TSubclassOf<class UUserWidget> DFLCamera_Label_Widget_class;
};
