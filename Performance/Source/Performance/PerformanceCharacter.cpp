#include "PerformanceCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogPerformanceCharacter);

APerformanceCharacter::APerformanceCharacter()
{
        GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f); // size of the player collider

        bUseControllerRotationPitch = false;
        bUseControllerRotationYaw = false;
        bUseControllerRotationRoll = false;

        GetCharacterMovement()->bOrientRotationToMovement = true; // face movement direction
        GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); // turning speed
        GetCharacterMovement()->JumpZVelocity = 700.f; // jump strength
        GetCharacterMovement()->AirControl = 0.35f; // steering in air
        GetCharacterMovement()->MaxWalkSpeed = 500.f; // walking speed
        GetCharacterMovement()->MinAnalogWalkSpeed = 20.f; // slowest stick walk
        GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; // ground stop speed
        GetCharacterMovement()->BrakingDecelerationFalling = 1500.f; // air stop speed

        CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")); // camera arm
        CameraBoom->SetupAttachment(RootComponent);
        CameraBoom->TargetArmLength = 400.f; // camera distance
        CameraBoom->bUsePawnControlRotation = true; // rotate with controller

        FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); // main camera
        FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
        FollowCamera->bUsePawnControlRotation = false; // camera rotates with arm
}
void APerformanceCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

        if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
        {
                if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
                {
                        Subsystem->AddMappingContext(DefaultMappingContext, 0); // enable our input mappings
                }
        }
}

void APerformanceCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
        Super::SetupPlayerInputComponent(PlayerInputComponent);

        if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
        {
                EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump); // start jump
                EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping); // stop jump
                EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APerformanceCharacter::Move); // move
                EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APerformanceCharacter::Look); // look
        }
        else
        {
                UE_LOG(LogPerformanceCharacter, Error, TEXT("'%s' needs an Enhanced Input component."), *GetNameSafe(this));
        }
}

void APerformanceCharacter::Move(const FInputActionValue& Value)
{
        const FVector2D MovementVector = Value.Get<FVector2D>(); // read input

        if (Controller != nullptr)
        {
                const FRotator Rotation = Controller->GetControlRotation();
                const FRotator YawRotation(0, Rotation.Yaw, 0);

                const FRotationMatrix RotationMatrix(YawRotation);
                const FVector ForwardDirection = RotationMatrix.GetUnitAxis(EAxis::X);
                const FVector RightDirection = RotationMatrix.GetUnitAxis(EAxis::Y);

                AddMovementInput(ForwardDirection, MovementVector.Y); // forward/back
                AddMovementInput(RightDirection, MovementVector.X); // left/right
        }
}

void APerformanceCharacter::Look(const FInputActionValue& Value)
{
        FVector2D LookAxisVector = Value.Get<FVector2D>(); // read input

        if (Controller != nullptr)
        {
                AddControllerYawInput(LookAxisVector.X); // turn
                AddControllerPitchInput(LookAxisVector.Y); // look up/down
        }
}
