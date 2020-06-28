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
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerInput.h"

#include "DFLGameStates.h"
#include "DFLGameState.h"
#include "DFLShowInventoryGameState.h"

// Sets default values
ADFLCharacter::ADFLCharacter()
{
    // Set this character to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    camera_component = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    camera_component->SetupAttachment(GetCapsuleComponent());
    camera_component->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
    camera_component->bUsePawnControlRotation = true;

    inventory_component = CreateDefaultSubobject<UDFLInventoryComponent>("Inventory");
    inventory_component->capacity = 20;

    ConstructorHelpers::FClassFinder<UDFLInventoryWidget> DFLInventory_widget_BP(TEXT("/Game/Blueprints/inventory/inventory_WBP"));
    if(DFLInventory_widget_BP.Class)
    {
        DFLInventory_widget_class = DFLInventory_widget_BP.Class;
    }

    ConstructorHelpers::FClassFinder<UUserWidget> UWidget_Examined_BP(TEXT("/Game/Blueprints/inventory/examine_WBP"));
    if(UWidget_Examined_BP.Class)
    {
        UWidget_Examined_BP_class = UWidget_Examined_BP.Class;
    }

    ConstructorHelpers::FClassFinder<UDFLItem> UDFLItemBP(TEXT("/Game/Blueprints/Items/Food_Item_BP"));
    UDFLItemClass = UDFLItemBP.Class;

    // use CreateDefaultSubobject only inside a constructor, use NewObject everywhere else Tick, BeginPlay, etc.
//    inventory_game_state = CreateDefaultSubobject<UDFLShowInventoryGameState>(TEXT("InventoryGameState"));

    game_states = CreateDefaultSubobject<UDFLGameStates>(TEXT("GameStates"));
    current_game_state = CreateDefaultSubobject<UDFLGameState>(TEXT("GameState"));
}

// Called when the game starts or when spawned
void ADFLCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Creating game states
    if(game_states)
    {
        game_states->create_game_states();
        UE_LOG(LogTemp, Warning, TEXT("ADFLCharacter::BeginPlay Game states created successfully"));
    }else{
        UE_LOG(LogTemp, Error, TEXT("ADFLCharacter::BeginPlay Error creating game states"));
    }

//    game_state = NewObject<UDFLGameState>((UObject*)GetTransientPackage(), UDFLGameState::StaticClass());
//    if(inventory_game_state)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("wwwwwwwwwwwwwwwwwwwwww"));
//        current_game_state = inventory_game_state;
//    }

    UUserWidget *general_widget{ nullptr };
    general_widget = CreateWidget<UUserWidget>(GetWorld(), DFLInventory_widget_class);
    if(general_widget && general_widget->IsA(UDFLInventoryWidget::StaticClass()))
    {
        inventory_widget = Cast<UDFLInventoryWidget>(general_widget);

        if(inventory_widget)
        {
            inventory_widget->action_menu_delegate.BindUObject(this, &ADFLCharacter::action_menu_delegate_slot);

            UE_LOG(LogTemp, Warning, TEXT("Inventory Widget Created Successfully"));
            inventory_widget->SetVisibility(ESlateVisibility::Hidden);
            inventory_widget->AddToViewport();
        }
    }

    UWidget_examine = CreateWidget<UUserWidget>(GetWorld(), UWidget_Examined_BP_class);
    if(UWidget_examine)
    {
        UE_LOG(LogTemp, Warning, TEXT("UWidget_examine Widget Created Successfully"));
        UWidget_examine->SetVisibility(ESlateVisibility::Hidden);
        UWidget_examine->AddToViewport();
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
        if(!is_actor_to_be_examined)
        {
            AddMovementInput(GetActorForwardVector() * value);
        }else{

            if(examined_actor)
            {
                actor_examined_distance += value;
                if(actor_examined_distance >= MAX_ACTOR_EXAMINED_DISTANCE)
                {
                    actor_examined_distance = MAX_ACTOR_EXAMINED_DISTANCE;
                }

                if(actor_examined_distance <= MIN_ACTOR_EXAMINED_DISTANCE)
                {
                    actor_examined_distance = MIN_ACTOR_EXAMINED_DISTANCE;
                }
            }
        }
    }
}

void ADFLCharacter::move_right(float value)
{
    if(player_can_move())
    {
        if(!is_actor_to_be_examined)
        {
            AddMovementInput(GetActorRightVector() * value);
        }
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
//        AddControllerYawInput(value * 45.0f * GetWorld()->GetDeltaSeconds());
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
            inventory_widget->execute_action_menu_command();
            inventory_widget->hide_action_menu();
        }else{
            inventory_widget->show_action_menu();
        }

        is_action_menu_displayed = !is_action_menu_displayed;
    }
}

void ADFLCharacter::escape_current_state()
{
    UE_LOG(LogTemp, Warning, TEXT("The Escape Key has been pressed"));

    if(is_actor_to_be_examined)
    {
        UWidget_examine->SetVisibility(ESlateVisibility::Hidden);

        if(examined_actor)
        {
            UStaticMeshComponent *actor_mesh_component = examined_actor->get_mesh_component();
            actor_mesh_component->SetVisibility(false);

            is_actor_to_be_examined = !is_actor_to_be_examined;

            process_inventory_visualization();

            Controller->SetControlRotation(camera_last_rotation);

            camera_component->bUsePawnControlRotation = !camera_component->bUsePawnControlRotation;
            bUseControllerRotationYaw = !bUseControllerRotationYaw;
        }
    }
}

void ADFLCharacter::pause_game(bool pause_game)
{
    is_game_paused = pause_game;
    UGameplayStatics::SetGamePaused(GetWorld(), pause_game);
}

bool ADFLCharacter::player_can_move()
{
//    return !is_inventory_widget_displayed;
    return is_player_can_move;
}

void ADFLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ADFLCharacter::move_forward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ADFLCharacter::move_right);

    PlayerInputComponent->BindAxis("LookUp", this, &ADFLCharacter::lookup);
    PlayerInputComponent->BindAxis("Turn", this, &ADFLCharacter::turn);

    PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ADFLCharacter::use_actor);
//    PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ADFLCharacter::process_inventory_visualization);
    PlayerInputComponent->BindAction("WidgetLeft", IE_Pressed, this, &ADFLCharacter::move_widget_left);
    PlayerInputComponent->BindAction("WidgetRight", IE_Pressed, this, &ADFLCharacter::move_widget_right);
    PlayerInputComponent->BindAction("WidgetUp", IE_Pressed, this, &ADFLCharacter::move_widget_up);
    PlayerInputComponent->BindAction("WidgetDown", IE_Pressed, this, &ADFLCharacter::move_widget_down);
//    PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ADFLCharacter::menu_action);
//    PlayerInputComponent->BindAction("EscapeCurrentState", IE_Pressed, this, &ADFLCharacter::escape_current_state);

    PlayerInputComponent->BindAction("AnyKey", IE_Pressed, this, &ADFLCharacter::handle_keyboard_input);
}

void ADFLCharacter::handle_keyboard_input(FKey key)
{
    if(current_game_state)
    {
        UDFLGameState *next_game_state = current_game_state->handle_keyboard_input(this, key);
        if(next_game_state)
        {
            current_game_state = next_game_state;
            next_game_state->enter_state(this);
        }
    }else{
        UE_LOG(LogTemp, Error, TEXT("Error: GameState instance has not been created"));
    }
}

void ADFLCharacter::action_menu_delegate_slot(int action_menu_index)
{
    camera_last_rotation = Controller->GetControlRotation();
    process_inventory_visualization();

    switch(action_menu_index)
    {
        case 0: // Use menu
        {
            UE_LOG(LogTemp, Warning, TEXT("action_menu_delegate_slot called. action menu index: %d"), action_menu_index);
        }
        break;

        case 1: // Examine menu
        {
            UWidget_examine->SetVisibility(ESlateVisibility::Visible);

            UE_LOG(LogTemp, Warning, TEXT("action_menu_delegate_slot called. action menu index: %d"), action_menu_index);
            is_actor_to_be_examined = true;
            camera_component->bUsePawnControlRotation = !camera_component->bUsePawnControlRotation;
            bUseControllerRotationYaw = !bUseControllerRotationYaw;
        }
        break;

        case 2: // Combine menu
        {
            UE_LOG(LogTemp, Warning, TEXT("action_menu_delegate_slot called. action menu index: %d"), action_menu_index);
        }
        break;
    }
}

void ADFLCharacter::use_item(UDFLItem *item)
{
    item->use(this);
    item->on_use(this); // This is the Blueprint event.
}

void ADFLCharacter::use_actor(FKey key)
{
    //if(!is_actor_to_be_examined)
    //{
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
    //}else{
        //is_reset_examine_rotation = !is_reset_examine_rotation;
    //}
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
    if(!is_actor_to_be_examined)
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










