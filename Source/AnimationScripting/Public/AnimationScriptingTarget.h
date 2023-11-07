// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnimationScriptingTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimationDelegate);

UCLASS()
class ANIMATIONSCRIPTING_API AAnimationScriptingTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimationScriptingTarget();

	/** The item mesh for NPC_A to pick up */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh;

	/** The table mesh */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* TableMesh;

	/** NPC_A's status ready for picking up item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* NPCAReady;

	/** NPC_B's status ready for talking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* NPCBReady;

	/** NPC_A's status for the end */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* NPCAEnd;

	/** NPC_B's status for the end */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* NPCBEnd;

	/** Number of characters */
	UPROPERTY(EditAnywhere)
	int NumChar;

	UPROPERTY()
	FAnimationDelegate OnAllReady;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int NumReady = 0;

public:	
	// Notify the character is in position
	UFUNCTION()
	void NotifyReady();
};
