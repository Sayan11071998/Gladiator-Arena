#include "PickableWeapon.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"

APickableWeapon::APickableWeapon()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    MySphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    MySphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    MySkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Hammer"));
    MySkeletalMesh->AttachToComponent(MySphere, FAttachmentTransformRules::KeepRelativeTransform);

    DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Box"));
    DamageBox->AttachToComponent(MySphere, FAttachmentTransformRules::KeepRelativeTransform);
}

void APickableWeapon::BeginPlay()
{
    Super::BeginPlay();
}

void APickableWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

UBoxComponent* APickableWeapon::GetDamageBox() const
{
    return DamageBox;
}
