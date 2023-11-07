// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationScriptingTarget.h"

// Sets default values
AAnimationScriptingTarget::AAnimationScriptingTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);

	TableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TableMesh"));
	TableMesh->SetupAttachment(RootComponent);

	NPCAReady = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("NPCAReady"));
	NPCAReady->SetupAttachment(RootComponent);

	NPCAReady->SetVisibility(false);

	NPCBReady = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("NPCBReady"));
	NPCBReady->SetupAttachment(RootComponent);

	NPCBReady->SetVisibility(false);

	NPCAEnd = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("NPCAEnd"));
	NPCAEnd->SetupAttachment(RootComponent);

	NPCAEnd->SetVisibility(false);

	NPCBEnd = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("NPCBEnd"));
	NPCBEnd->SetupAttachment(RootComponent);

	NPCBEnd->SetVisibility(false);
}

// Called when the game starts or when spawned
void AAnimationScriptingTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Notify the character is in position
void AAnimationScriptingTarget::NotifyReady()
{
	NumReady++;
	if (NumReady >= 2)
	{
		OnAllReady.Broadcast();
	}
}