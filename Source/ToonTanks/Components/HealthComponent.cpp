// daltonlima.com

#include "HealthComponent.h"

#include "ToonTanks/Actors/ProjectileBase.h"

UHealthComponent::UHealthComponent()
{	
	PrimaryComponentTick.bCanEverTick = false;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);	
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == 0 || Health <= 0)
	{	
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
		
	Health -= Damage;
	if (Health <= 0.0f)
	{
		if (GameModeRef)
		{
			GameModeRef->ActorDied(GetOwner());
			Health = 0;			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[UHealthComponent] Error! GameModeRef not found!"))
		}
	}
}
