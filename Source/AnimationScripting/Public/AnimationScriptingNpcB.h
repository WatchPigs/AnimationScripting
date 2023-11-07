// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "AnimationScriptingTarget.h"
#include "AnimationScriptingNpcB.generated.h"

UCLASS()
class ANIMATIONSCRIPTING_API AAnimationScriptingNpcB : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	AAnimationScriptingTarget* AnimationTarget;

	UPROPERTY(EditAnywhere)
	UAnimMontage* TalkingMontage;

protected:
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
	AAnimationScriptingNpcB();

	// Start Moving to Ready Location for pick up item
	UFUNCTION(BlueprintCallable)
	void StartMove();

	// Adjust location and rotation for talking animation
	void MoveToPrecisePosition(FAIRequestID RequestID, const FPathFollowingResult& Result);

	// Notify Target
	UFUNCTION()
	void NotifyTarget();

	// Start play talking animation
	UFUNCTION()
	void StartTalking();

	// On talking animation ended
	UFUNCTION()
	void EndTalking(UAnimMontage* Montage, bool Interrupted);

	// Move to end location
	UFUNCTION()
	void MoveToEnd();
};
