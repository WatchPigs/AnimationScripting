// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"
#include "AITypes.h"
#include "AnimationScriptingTarget.h"
#include "AnimationScriptingNpcA.generated.h"

UCLASS()
class ANIMATIONSCRIPTING_API AAnimationScriptingNpcA : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	AAnimationScriptingTarget* AnimationTarget;

	UPROPERTY(EditAnywhere)
	UAnimMontage* PickUpMontage;

	UPROPERTY(EditAnywhere)
	FName GrabNotifyName;

	UPROPERTY(EditAnywhere)
	FName ReleaseNotifyName;

	UPROPERTY(EditAnywhere)
	FName HandSocketName;

protected:
	/** Item mesh for NPC_A to pick up */
	UPROPERTY()
	UStaticMeshComponent* ItemMesh;

	/** The location ready for picking up item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector ReadyLocation;

	/** The rotation ready for picking up item */
	UPROPERTY()
	FRotator ReadyRotation;

	/** The location for the end */
	UPROPERTY()
	FVector EndLocation;

	/** AI Controller for Navigation */
	UPROPERTY()
	AAIController* AIController;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	AAnimationScriptingNpcA();

	// Start Moving to Ready Location for pick up item
	UFUNCTION(BlueprintCallable)
	void StartMove();

	// Adjust location and rotation to start pick up item
	void MoveToPrecisePosition(FAIRequestID RequestID, const FPathFollowingResult& Result);

	// Notify Target
	UFUNCTION()
	void NotifyTarget();

	// Start play pick up animation
	UFUNCTION()
	void StartPickup();

	// Attach item to character's hand
	UFUNCTION()
	void GrabItem(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	// Detach item to character's hand
	UFUNCTION()
	void ReleaseItem(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	// On pick up animation ended
	UFUNCTION()
	void EndPickup(UAnimMontage* Montage, bool Interrupted);

	// Move to end location
	UFUNCTION()
	void MoveToEnd();
};
