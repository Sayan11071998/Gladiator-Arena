#include "AICharacter.h"
#include "PickableItemBase.h"
#include "PickableWeapon.h"
#include "Engine/World.h"
#include "PlayerCharacter.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Components/BoxComponent.h"

AAICharacter::AAICharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAICharacter::BeginPlay()
{
    Super::BeginPlay();

    CreateAndAttachWeapons();
}

void AAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(bIsAttacking)
    {
        if(WeaponCollider != nullptr)
        {
            WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        }
    }
    else
    {
        if(WeaponCollider != nullptr)
        {
            WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            if(CanDetectCollision)
                CanDetectCollision = false;
        }
    }
}

void AAICharacter::CreateAndAttachWeapons()
{
    FVector Position = GetActorLocation();
    FRotator Rotation = GetActorRotation();

    if(Shield != nullptr)
    {
        APickableItemBase* NewShield = Cast<APickableItemBase>(GetWorld()->SpawnActor(Shield, &Position, &Rotation));
        NewShield->AttachItemTo(GetMesh(), TEXT("DualWeaponPoint"));
    }

    if(Weapon != nullptr)
    {
        APickableWeapon* NewWeapon = Cast<APickableWeapon>(GetWorld()->SpawnActor(Weapon, &Position, &Rotation));
        NewWeapon->AttachItemTo(GetMesh(), TEXT("WeaponPoint"));

        WeaponCollider = NewWeapon->GetDamageBox();
        if(WeaponCollider != nullptr)
        {
            WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &AAICharacter::OnWeaponBeginOverlap);
        }
    }
}

void AAICharacter::TriggerAttack()
{
    if(DisableAttack)
        return;

    CanDetectCollision = true;
    Attack();
}

void AAICharacter::OnWeaponBeginOverlap(UPrimitiveComponent* OverlapComp,
            AActor* OtherActor,
            UPrimitiveComponent* OtherComp,
            int32 OtherBodyIndex,
            bool bSweepFrom,
            const FHitResult& SweepResult)
{
    if(OtherActor->ActorHasTag("Player"))
    {
        if(CanDetectCollision)
        {
            CanDetectCollision = false;

            APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
            bool bCanAttack = Player->ApplyDamage();

            DisableAttack = bCanAttack;
        }
    }
}

bool AAICharacter::ApplyDamage()
{
    Health -= 10.f;
    if(Health <= 0.f)
    {
        bIsAlive = false;
        
        AAIController* MyAI = Cast<AAIController>(GetController());
        // MyAI->BrainComponent->StopLogic("");
        MyAI->UnPossess();

        return true;
    }
    return false;
}
