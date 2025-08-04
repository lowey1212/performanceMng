#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PerformanceCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogPerformanceCharacter, Log, All);

UCLASS(config=Game)
class APerformanceCharacter : public ACharacter
{
	GENERATED_BODY()

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true", ToolTip = "Arm that keeps the camera behind the player"))
        USpringArmComponent* CameraBoom;

        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true", ToolTip = "Camera following the player"))
        UCameraComponent* FollowCamera;

        UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true", ToolTip = "Input setup used by this character"))
        UInputMappingContext* DefaultMappingContext;

        UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true", ToolTip = "Input action that makes the character jump"))
        UInputAction* JumpAction;

        UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true", ToolTip = "Input action that moves the character"))
        UInputAction* MoveAction;

        UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true", ToolTip = "Input action that turns the camera"))
        UInputAction* LookAction;

public:
	APerformanceCharacter();
	

protected:
        void Move(const FInputActionValue& Value); // handle movement input
        void Look(const FInputActionValue& Value); // handle look input

protected:
        virtual void NotifyControllerChanged() override;
        virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
        FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; } // access camera arm
        FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; } // access main camera
};

