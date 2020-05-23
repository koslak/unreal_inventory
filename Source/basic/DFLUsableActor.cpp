#include "DFLUsableActor.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ADFLUsableActor::ADFLUsableActor()
{
    mesh_component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = mesh_component;
}

void ADFLUsableActor::OnBeginFocus()
{
    mesh_component->SetRenderCustomDepth(true);

}

void ADFLUsableActor::OnEndFocus()
{
    mesh_component->SetRenderCustomDepth(false);
}

void ADFLUsableActor::OnUsed(APawn *)
{
    // Nothing to do here.
}



