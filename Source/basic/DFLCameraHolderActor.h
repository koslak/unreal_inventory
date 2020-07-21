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
    bool has_camera_attached(){ return is_has_camera_attached; };
    class UDFLInventoryItemWidget *get_camera_inventory_item_widget();
    void set_camera_inventory_item_widget(class UDFLInventoryItemWidget *camera_item);

    UPROPERTY(EditAnywhere, DisplayName="Pick Up Sound", Category = "Sound")
    class USoundCue* pickup_sound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Configuration")
    FText widget_text;

private:
    UPROPERTY(EditDefaultsOnly)
    class USceneCaptureComponent2D *camera{ nullptr };

    UPROPERTY(EditDefaultsOnly)
    class UDFLCameraLabelWidget *camera_label_widget{ nullptr };

    UPROPERTY(EditDefaultsOnly)
    class UDFLInventoryItemWidget *inventory_item_widget{ nullptr };

    TSubclassOf<class UUserWidget> DFLCamera_Label_Widget_class;

    bool is_has_camera_attached{ false };
};
