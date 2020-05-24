#include "DFLUsableActor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ADFLUsableActor::ADFLUsableActor()
{
    mesh_component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = mesh_component;

    widget_component = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
    widget_component->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    widget_component->SetVisibility(false);
    widget_component->SetWidgetSpace(EWidgetSpace::Screen);
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
    // Nothing to do here.
}



