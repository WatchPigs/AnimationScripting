// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationScriptingNpcB.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAnimationScriptingNpcB::AAnimationScriptingNpcB()
{
}

// Called when the game starts or when spawned
void AAnimationScriptingNpcB::BeginPlay()
{
	Super::BeginPlay();
	
	if (AnimationTarget)
	{
		ReadyLocation = AnimationTarget->NPCBReady->GetComponentLocation();
		ReadyRotation = AnimationTarget->NPCBReady->GetComponentRotation();
		EndLocation = AnimationTarget->NPCBEnd->GetComponentLocation();
	}
	AIController = Cast<AAIController>(GetController());
}

// Moving to Ready Location for pick up item
void AAnimationScriptingNpcB::StartMove()
{
	AIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AAnimationScriptingNpcB::MoveToPrecisePosition);
	AIController->MoveToLocation(ReadyLocation);
}

// Adjust location and rotation for talking animation
void AAnimationScriptingNpcB::MoveToPrecisePosition(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	AIController->GetPathFollowingComponent()->OnRequestFinished.RemoveAll(this);
	FVector TargetLocation = ReadyLocation - GetMesh()->GetRelativeLocation();
	TargetLocation.Z = RootComponent->GetComponentLocation().Z;
	FRotator TargetRotation = UKismetMathLibrary::InverseTransformRotation(GetMesh()->GetRelativeTransform(), ReadyRotation);
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("NotifyTarget");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = 0;
	UKismetSystemLibrary::MoveComponentTo(RootComponent, TargetLocation, TargetRotation, true, true, 0.5f, true, EMoveComponentAction::Type::Move, LatentInfo);
}

// Notify Target
void AAnimationScriptingNpcB::NotifyTarget()
{
	AnimationTarget->OnAllReady.AddDynamic(this, &AAnimationScriptingNpcB::StartTalking);
	AnimationTarget->NotifyReady();
}

// Start play talking animation
void AAnimationScriptingNpcB::StartTalking()
{
	PlayAnimMontage(TalkingMontage);
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AAnimationScriptingNpcB::EndTalking);
}

// On talking animation ended
void AAnimationScriptingNpcB::EndTalking(UAnimMontage* Montage, bool Interrupted)
{
	GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveAll(this);
	MoveToEnd();
}

// Move to end location
void AAnimationScriptingNpcB::MoveToEnd()
{
	AIController->MoveToLocation(EndLocation);
}
