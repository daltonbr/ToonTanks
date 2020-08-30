// daltonlima.com

#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "ToonTanks/Pawns/PawnTank.h"

AProjectileBase::AProjectileBase()
{ 	
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));	
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;
	InitialLifeSpan = 5.0f;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr) { return; }

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
		const auto Player = Cast<APawnTank>(OtherActor);
		if (Player)
		{
			TInlineComponentArray<UHealthComponent*> HealthComponents;

			// Debugging HealthComponent
			Player->GetComponents(HealthComponents);

			for(auto CompIt = HealthComponents.CreateConstIterator(); CompIt; ++CompIt)
			{
				UActorComponent* Component = *CompIt;
				UE_LOG(LogTemp, Warning, TEXT("Component: %s"), *Component->GetReadableName());
				UHealthComponent* HealthComponent = Cast<UHealthComponent>(Component);
				if (HealthComponent)
				{
					UE_LOG(LogTemp, Warning, TEXT("Health: %f"), HealthComponent->GetHealth());
				}
			}			
		}
	}
		
	Destroy();
}
