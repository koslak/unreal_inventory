#include "DFLUsableActor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "inventory/DFLInventoryItemWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

// Sets default values
ADFLUsableActor::ADFLUsableActor()
{
    mesh_component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = mesh_component;
    mesh_component->SetMobility(EComponentMobility::Movable);

    widget_component = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
    widget_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    widget_component->SetVisibility(false);
    widget_component->SetWidgetSpace(EWidgetSpace::Screen);

    ConstructorHelpers::FClassFinder<UDFLInventoryItemWidget> DFLInventory_item_widget_BP(TEXT("/Game/Blueprints/inventory/inventory_item_WBP"));
    if(DFLInventory_item_widget_BP.Class)
    {
        DFLInventory_item_widget_class = DFLInventory_item_widget_BP.Class;
    }else{
        UE_LOG(LogTemp, Error, TEXT("DFLInventory_item_widget_BP is null"));
    }

    this->SetActorTickEnabled(true);
}

void ADFLUsableActor::OnBeginFocus()
{
    mesh_component->SetRenderCustomDepth(true);
    widget_component->SetVisibility(true);
}

void ADFLUsableActor::OnEndFocus()
{
    mesh_component->SetRenderCustomDepth(false);
    widget_component->SetVisibility(false);
}

void ADFLUsableActor::OnUsed(APawn *)
{
    UUserWidget *general_widget{ nullptr };
    general_widget = CreateWidget<UUserWidget>(GetWorld(), DFLInventory_item_widget_class);

    if(general_widget && general_widget->IsA(UDFLInventoryItemWidget::StaticClass()))
    {
        inventory_item_widget = Cast<UDFLInventoryItemWidget>(general_widget);

        if(inventory_item_widget)
        {
            inventory_item_widget->parent_actor = this;
            inventory_item_widget->Thumbnail->SetBrushFromTexture(this->thumbnail_image);
            inventory_item_widget->ItemName->SetText(this->item_widget_display_name);
            inventory_item_widget->FrameSelector->SetOpacity(0.0f);
        }
    }else{
        UE_LOG(LogTemp, Error, TEXT("ADFLUsableActor inventory item widget is null"));
    }
}

void ADFLUsableActor::rotate_actor()
{
    UWorld *world = GetWorld();
    if(world)
    {
        APlayerController* player_controller = world->GetFirstPlayerController();
        if(player_controller)
        {
            control_rotation = player_controller->GetControlRotation();
            SetActorRelativeRotation(FQuat(control_rotation));
        }
    }
}

void ADFLUsableActor::reset_actor_rotation(const FRotator &new_rotation)
{
    UWorld *world = GetWorld();
    if(world)
    {
        APlayerController* player_controller = world->GetFirstPlayerController();
        if(player_controller)
        {
            control_rotation = player_controller->GetControlRotation();
            player_controller->SetControlRotation(FMath::Lerp(control_rotation, new_rotation, 0.15f));
            SetActorRelativeRotation(FMath::Lerp(control_rotation, new_rotation, 0.15f));
        }
    }
}




