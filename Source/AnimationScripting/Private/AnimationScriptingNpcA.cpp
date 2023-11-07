// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationScriptingNpcA.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAnimationScriptingNpcA::AAnimationScriptingNpcA()
{
}

// Called when the game starts or when spawned
void AAnimationScriptingNpcA::BeginPlay()
{
	Super::BeginPlay();
	
	if (AnimationTarget)
	{
		ItemMesh = AnimationTarget->ItemMesh;
		ReadyLocation = AnimationTarget->NPCAReady->GetComponentLocation();
		ReadyRotation = AnimationTarget->NPCAReady->GetComponentRotation();
		EndLocation = AnimationTarget->NPCAEnd->GetComponentLocation();
	}
	AIController = Cast<AAIController>(GetController());
}

// Moving to Ready Location for pick up item
void AAnimationScriptingNpcA::StartMove()
{
	AIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AAnimationScriptingNpcA::MoveToPrecisePosition);
	AIController->MoveToLocation(ReadyLocation);
}

// Adjust location and rotation to start pick up item
void AAnimationScriptingNpcA::MoveToPrecisePosition(FAIRequestID RequestID, const FPathFollowingResult& Result)
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
	UKismetSystemLibrary::MoveComponentTo(RootComponent, TargetLocation, TargetRotation, true, true, 0.5f, true,EMoveComponentAction::Type::Move, LatentInfo);
}

// Notify Target
void AAnimationScriptingNpcA::NotifyTarget()
{
	AnimationTarget->OnAllReady.AddDynamic(this, &AAnimationScriptingNpcA::StartPickup);
	AnimationTarget->NotifyReady();
}

// Start play pick up animation
void AAnimationScriptingNpcA::StartPickup()
{
	ItemMesh->SetSimulatePhysics(false);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlayAnimMontage(PickUpMontage);
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &AAnimationScriptingNpcA::GrabItem);
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &AAnimationScriptingNpcA::ReleaseItem);
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AAnimationScriptingNpcA::EndPickup);
}

// Attach item to character's hand
void AAnimationScriptingNpcA::GrabItem(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (NotifyName == GrabNotifyName)
	{
		ItemMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true), HandSocketName);
	}
}

// Detach item to character's hand
void AAnimationScriptingNpcA::ReleaseItem(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (NotifyName == ReleaseNotifyName)
	{
		ItemMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ItemMesh->SetSimulatePhysics(true);
	}
}

// On pick up animation ended
void AAnimationScriptingNpcA::EndPickup(UAnimMontage* Montage, bool Interrupted)
{
	GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveAll(this);
	MoveToEnd();
}

// Move to end location
void AAnimationScriptingNpcA::MoveToEnd()
{
	AIController->MoveToLocation(EndLocation);
}