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

#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ADFLCharacter::ADFLCharacter()
{
    // Set this character to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

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
        UE_LOG(LogTemp, Warning, TEXT("to the left KEY"));
    }
}

void ADFLCharacter::move_widget_right()
{
    if(!player_can_move())
    {
        UE_LOG(LogTemp, Warning, TEXT("to the right KEY"));
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

        UE_LOG(LogTemp, Warning, TEXT("use_actor.........."));
        UDFLInventoryItemWidget *item = usable_actor->get_inventory_item_widget();
        if(item)
        {
            inventory_widget->add_item(item);
        }else {
            UE_LOG(LogTemp, Warning, TEXT("item widget is null.........."));
        }
//        UDFLFoodItem *food_item = NewObject<UDFLFoodItem>(this, UDFLItemClass, TEXT("food_item"));
//        inventory_component->add_item(UDFLItemClass.GetDefaultObject());
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

//    DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f);

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

    is_inventory_widget_displayed = !is_inventory_widget_displayed;
}

void ADFLCharacter::show_inventory()
{
    UE_LOG(LogTemp, Warning, TEXT("Show Inventory"));

    if(inventory_widget)
    {
        APlayerController* player_controller = static_cast<APlayerController*>(this->GetController());
        if(player_controller)
        {
            /*
            FInputModeGameAndUI input_mode_game_and_UI;
            input_mode_game_and_UI.SetWidgetToFocus(inventory_widget->TakeWidget());
            input_mode_game_and_UI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

            player_controller->bShowMouseCursor = true;
            player_controller->SetInputMode(input_mode_game_and_UI);
            */
            inventory_widget->SetVisibility(ESlateVisibility::Visible);

        }else{
            UE_LOG(LogTemp, Error, TEXT("player_controller variable is null"));
        }
    }else{
        UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
    }
}

void ADFLCharacter::hide_inventory()
{
    UE_LOG(LogTemp, Warning, TEXT("Hide Inventory"));

    if(inventory_widget)
    {
        APlayerController* player_controller = static_cast<APlayerController*>(this->GetController());
        if(player_controller)
        {
            /*
            FInputModeGameOnly input_mode_game;

            player_controller->SetInputMode(input_mode_game);
            player_controller->bShowMouseCursor = false;
            */
            inventory_widget->SetVisibility(ESlateVisibility::Hidden);

        }else{
            UE_LOG(LogTemp, Error, TEXT("player_controller variable is null"));
        }
    }else{
        UE_LOG(LogTemp, Error, TEXT("Inventory_widget variable is null"));
    }
}










