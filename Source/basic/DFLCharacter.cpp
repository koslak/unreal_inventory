#include "DFLCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "DFLUsableActor.h"
#include "Blueprint/UserWidget.h"
#include "items/DFLItem.h"
#include "items/DFLFoodItem.h"
#include "items/DFLInventoryComponent.h"
#include "inventory/DFLInventoryWidget.h"
#include "inventory/DFLInventoryItemWidget.h"

#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ADFLCharacter::ADFLCharacter()
{
    // Set this character to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    camera_component = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    camera_component->SetupAttachment(GetCapsuleComponent());
    camera_component->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
    camera_component->bUsePawnControlRotation = true;

    /*
    // Don't use any post processing effect for the camera
    camera_component->PostProcessBlendWeight = 0.0f;

    camera_component->PostProcessSettings.DepthOfFieldFstop = 1.0f;
    camera_component->PostProcessSettings.DepthOfFieldMinFstop = 1.2f;
    camera_component->PostProcessSettings.DepthOfFieldFocalDistance = 50.0f;
    */

    inventory_component = CreateDefaultSubobject<UDFLInventoryComponent>("Inventory");
    inventory_component->capacity = 20;

    ConstructorHelpers::FClassFinder<UDFLInventoryWidget> DFLInventory_widget_BP(TEXT("/Game/Blueprints/inventory/inventory_WBP"));
    if(DFLInventory_widget_BP.Class)
    {
        DFLInventory_widget_class = DFLInventory_widget_BP.Class;
    }

    ConstructorHelpers::FClassFinder<UDFLItem> UDFLItemBP(TEXT("/Game/Blueprints/Items/Food_Item_BP"));
    UDFLItemClass = UDFLItemBP.Class;
}

// Called when the game starts or when spawned
void ADFLCharacter::BeginPlay()
{
    Super::BeginPlay();

    UUserWidget *general_widget{ nullptr };
    general_widget = CreateWidget<UUserWidget>(GetWorld(), DFLInventory_widget_class);
    if(general_widget && general_widget->IsA(UDFLInventoryWidget::StaticClass()))
    {
        inventory_widget = Cast<UDFLInventoryWidget>(general_widget);

        UE_LOG(LogTemp, Warning, TEXT("Inventory Widget Created Successfully"));
        inventory_widget->SetVisibility(ESlateVisibility::Hidden);
        inventory_widget->AddToViewport();
    }
}

// Called every frame
void ADFLCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Controller && Controller->IsLocalController())
    {
        ADFLUsableActor* usable_actor = get_usable_actor_in_view();

        // End Focus
        if (focused_usable_actor != usable_actor)
        {
            if (focused_usable_actor)
            {
                focused_usable_actor->OnEndFocus();
            }

            is_usable_actor_has_new_focus = true;
        }

        // Assign new Focus
        focused_usable_actor = usable_actor;

        // Start Focus.
        if (usable_actor)
        {
            if (is_usable_actor_has_new_focus)
            {
                usable_actor->OnBeginFocus();
                is_usable_actor_has_new_focus = false;
            }
        }
    }

    if(is_actor_to_be_examined)
    {
        UDFLInventoryItemWidget *current_item_widget_selected = inventory_widget->get_current_item_widget_selected();
        if(current_item_widget_selected)
        {
            /*
            camera_component->PostProcessBlendWeight = 1.0f;
            camera_component->PostProcessSettings.DepthOfFieldFstop = 1.2f;
            camera_component->PostProcessSettings.DepthOfFieldMinFstop = 1.2f;
            camera_component->PostProcessSettings.DepthOfFieldFocalDistance = 60.0f;
            */

            ADFLUsableActor *current_item_widget_actor = current_item_widget_selected->parent_actor;
//            current_item_widget_actor->SetActorScale3D(FVector(0.1f, 0.1f, 0.1f));
            UStaticMeshComponent *actor_mesh_component = current_item_widget_actor->get_mesh_component();
//            actor_mesh_component->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));
            actor_mesh_component->SetVisibility(true);

            current_item_widget_actor->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepWorldTransform);

            FVector Start = camera_component->GetComponentLocation();
            FVector ForwardVector = camera_component->GetForwardVector();
            FVector End = ((ForwardVector * 70.0f) + Start);

//            current_item_widget_actor->SetActorRelativeLocation(FVector(0.0f, 50.0f, 50.0f));
            current_item_widget_actor->SetActorLocation(End);

//            GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax = 179.9000002f;
//            GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin = -179.9000002f;
            current_item_widget_actor->rotate_actor();

        }else{
            UE_LOG(LogTemp, Error, TEXT("ADFLCharacter::menu_action -> current_item_widget_selected is null"));
        }


    }
}

void ADFLCharacter::move_forward(float value)
{
    if(player_can_move())
    {
        AddMovementInput(GetActorForwardVector() * value);
    }
}

void ADFLCharacter::move_right(float value)
{
    if(player_can_move())
    {
        AddMovementInput(GetActorRightVector() * value);
    }
}

void ADFLCharacter::lookup(float value)
{
    if(player_can_move())
    {
        AddControllerPitchInput(value);
    }
}

void ADFLCharacter::turn(float value)
{
    if(player_can_move())
    {
        AddControllerYawInput(value);
    }
}

void ADFLCharacter::move_widget_left()
{
    if(!player_can_move())
    {
        if(!is_action_menu_displayed)
        {
            inventory_widget->select_item_to_the_west();
        }
    }
}

void ADFLCharacter::move_widget_right()
{
    if(!player_can_move())
    {
        if(!is_action_menu_displayed)
        {
            inventory_widget->select_item_to_the_east();
        }
    }
}

void ADFLCharacter::move_widget_up()
{
    if(!player_can_move())
    {
        if(!is_action_menu_displayed)
        {
            inventory_widget->select_item_to_the_north();
        }else{
            // Move action menu options up
            inventory_widget->select_action_menu_up();
        }
    }
}

void ADFLCharacter::move_widget_down()
{
    if(!player_can_move())
    {
        if(!is_action_menu_displayed)
        {
            inventory_widget->select_item_to_the_south();
        }else{
            // Move action menu options down
            inventory_widget->select_action_menu_down();
        }
    }
}

void ADFLCharacter::menu_action()
{
    if(!player_can_move())
    {
        if(is_action_menu_displayed)
        {
            is_actor_to_be_examined = true;
            camera_component->bUsePawnControlRotation = !camera_component->bUsePawnControlRotation;
            bUseControllerRotationYaw = !bUseControllerRotationYaw;

            inventory_widget->execute_action_menu_command();
            inventory_widget->hide_action_menu();
        }else{
            inventory_widget->show_action_menu();
        }

        is_action_menu_displayed = !is_action_menu_displayed;
    }
}

bool ADFLCharacter::player_can_move()
{
    return !is_inventory_widget_displayed;
}

// Called to bind functionality to input
void ADFLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ADFLCharacter::move_forward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ADFLCharacter::move_right);

    PlayerInputComponent->BindAxis("LookUp", this, &ADFLCharacter::lookup);
    PlayerInputComponent->BindAxis("Turn", this, &ADFLCharacter::turn);

    PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ADFLCharacter::use_actor);
    PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ADFLCharacter::process_inventory_visualization);
    PlayerInputComponent->BindAction("WidgetLeft", IE_Pressed, this, &ADFLCharacter::move_widget_left);
    PlayerInputComponent->BindAction("WidgetRight", IE_Pressed, this, &ADFLCharacter::move_widget_right);
    PlayerInputComponent->BindAction("WidgetUp", IE_Pressed, this, &ADFLCharacter::move_widget_up);
    PlayerInputComponent->BindAction("WidgetDown", IE_Pressed, this, &ADFLCharacter::move_widget_down);
    PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ADFLCharacter::menu_action);
}

void ADFLCharacter::use_item(UDFLItem *item)
{
    item->use(this);
    item->on_use(this); // This is the Blueprint event.
}

void ADFLCharacter::use_actor()
{
    ADFLUsableActor* usable_actor = get_usable_actor_in_view();
    if (usable_actor)
    {
        usable_actor->OnUsed(this);

        UDFLInventoryItemWidget *item = usable_actor->get_inventory_item_widget();
        if(item)
        {
            inventory_widget->add_item(item);
        }
    }
}

ADFLUsableActor *ADFLCharacter::get_usable_actor_in_view()
{
    FVector CamLoc;
    FRotator CamRot;

    if (Controller == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("ADFLCharacter::get_usable_actor_in_view -> Controller is null"));
        return nullptr;
    }

    Controller->GetPlayerViewPoint(CamLoc, CamRot);
    const FVector TraceStart = CamLoc;
    const FVector Direction = CamRot.Vector();
    const FVector TraceEnd = TraceStart + (Direction * max_use_distance);

    FCollisionQueryParams TraceParams(FName(TEXT("TraceUsableActor")), true, this);
    TraceParams.bReturnPhysicalMaterial = false;
    TraceParams.bTraceComplex = true;

    FHitResult Hit(ForceInit);
    GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, TraceParams);

    return Cast<ADFLUsableActor>(Hit.GetActor());
}

void ADFLCharacter::process_inventory_visualization()
{
    if(is_inventory_widget_displayed)
    {
        hide_inventory();

    }else{
        show_inventory();
    }

    is_action_menu_displayed = false;
    is_inventory_widget_displayed = !is_inventory_widget_displayed;
}

void ADFLCharacter::show_inventory()
{
    if(inventory_widget)
    {
        APlayerController* player_controller = static_cast<APlayerController*>(this->GetController());
        if(player_controller)
        {
            inventory_widget->show_inventory();

        }else{
            UE_LOG(LogTemp, Error, TEXT("player_controller variable is null"));
        }
    }else{
        UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
    }
}

void ADFLCharacter::hide_inventory()
{
    if(inventory_widget)
    {
        APlayerController* player_controller = static_cast<APlayerController*>(this->GetController());
        if(player_controller)
        {
            inventory_widget->hide_inventory();

        }else{
            UE_LOG(LogTemp, Error, TEXT("player_controller variable is null"));
        }
    }else{
        UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
    }
}










