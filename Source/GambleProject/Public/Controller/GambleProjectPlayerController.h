#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GambleProjectPlayerController.generated.h"

class UPlayerInputData;
class UInputVectorValue;
class UInputBoolValue;
class UInputMappingContext;
class UUserWidget;
struct FInputActionValue;

/**
 *  Simple first person Player Controller
 *  Manages the input mapping context.
 *  Overrides the Player Camera Manager class.
 */
UCLASS(Abstract)
class GAMBLEPROJECT_API AGambleProjectPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	AGambleProjectPlayerController();

protected:
	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** Gameplay initialization */
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
	
#pragma region PLAYER_INPUTS
public:
	UPROPERTY(EditDefaultsOnly, Category ="Inputs")
	TObjectPtr<UPlayerInputData> InputData;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputVectorValue* MovementInput;

	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputVectorValue* AimInput;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputBoolValue* JumpInput;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputBoolValue* SprintInput;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputBoolValue* CrouchInput;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputBoolValue* FireInput;
	
	UPROPERTY(BlueprintReadOnly, Category = "Inputs")
	UInputBoolValue* RerollInput;
	
private:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	
	void InputValuesInit();
	
	void InputValuesTick(float DeltaTime);
	
	void OnInputMove(const FInputActionValue& InputActionValue);
	
	void OnInputAim(const FInputActionValue& InputActionValue);
	
	void OnInputJump(const FInputActionValue& InputActionValue);
	
	void OnInputSprint(const FInputActionValue& InputActionValue);
	
	void OnInputCrouch(const FInputActionValue& InputActionValue);
	
	void OnInputFire(const FInputActionValue& InputActionValue);
	
	void OnInputReroll(const FInputActionValue& InputActionValue);
#pragma endregion

};