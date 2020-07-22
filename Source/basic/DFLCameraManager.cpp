#include "DFLCameraManager.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Blueprint/UserWidget.h"
#include "inventory/DFLSpyInventoryWidget.h"
//#include "Components/SlateWrapperTypes.h"

ADFLCameraManager::ADFLCameraManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    in_game_cameras_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N0"));
    in_game_cameras_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N1"));
    in_game_cameras_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N2"));
    in_game_cameras_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N3"));
    in_game_cameras_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N4"));
    in_game_cameras_array.Add(CreateDefaultSubobject<USceneCaptureComponent2D>("in_game_camera_N5"));

    ConstructorHelpers::FClassFinder<UDFLSpyInventoryWidget> DFLSpy_inventory_widget_BP(TEXT("/Game/Blueprints/inventory/spy_inventory_WBP"));
    if(DFLSpy_inventory_widget_BP.Class)
    {
        DFLSpy_Cam_Inventory_BP_class = DFLSpy_inventory_widget_BP.Class;
    }
}

void ADFLCameraManager::BeginPlay()
{
	Super::BeginPlay();

    UUserWidget *general_widget_1{ nullptr };
    general_widget_1 = CreateWidget<UUserWidget>(GetWorld(), DFLSpy_Cam_Inventory_BP_class);
    if(general_widget_1 && general_widget_1->IsA(UDFLSpyInventoryWidget::StaticClass()))
    {
        spy_inventory_widget = Cast<UDFLSpyInventoryWidget>(general_widget_1);
        if(spy_inventory_widget)
        {
            UE_LOG(LogTemp, Warning, TEXT("spy_inventory_widget Widget Created Successfully"));
            spy_inventory_widget->SetVisibility(ESlateVisibility::Hidden);
            spy_inventory_widget->AddToViewport();
            spy_inventory_widget->disable_all_cameras();
        }
    }

}

void ADFLCameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USceneCaptureComponent2D *ADFLCameraManager::get_last_camera_available()
{
    UE_LOG(LogTemp, Warning, TEXT("-----ADFLCameraManager::get_last_camera_available array size: %d"), in_game_cameras_array.Num());
    UE_LOG(LogTemp, Warning, TEXT("-----ADFLCameraManager::get_last_camera_available index: %d"), current_camera_index);
    USceneCaptureComponent2D *camera{ nullptr };

    if(in_game_cameras_array.Num() > 0 && spy_inventory_widget)
    {
        spy_inventory_widget->enable_camera_by_index(current_camera_index);

        FString namex = in_game_cameras_array[ current_camera_index ]->GetName();
        UE_LOG(LogTemp, Warning, TEXT("ADFLCameraManager::get_last_camera_available camera available: %s"), *namex );
        camera = in_game_cameras_array[ current_camera_index ];

        current_camera_index++;
        int cameras_array_size{ in_game_cameras_array.Num() };

        if(current_camera_index >= cameras_array_size)
        {
            current_camera_index = cameras_array_size - 1;
        }
    }

    return camera;
}

void ADFLCameraManager::set_spy_inventory_visibility(ESlateVisibility InVisibility)
{
    spy_inventory_widget->SetVisibility(InVisibility);
}

