#include "PickableItemBase.h"

APickableItemBase::APickableItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APickableItemBase::BeginPlay()
{
	Super::BeginPlay();	
}

void APickableItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool APickableItemBase::AttachItemTo(USkeletalMeshComponent* MeshRoot, FName Socket)
{
	if(IsUsed)
		return false;

	AttachToComponent(MeshRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
	SetActorRelativeLocation(FVector::ZeroVector);
	SetActorRelativeRotation(FRotator::ZeroRotator);
	
	IsUsed = true;

	return true;
}