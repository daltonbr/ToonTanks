// daltonlima.com

#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{	
	PrimaryComponentTick.bCanEverTick = false;
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	UE_LOG(LogTemp, Warning, TEXT("[UHealthComponent] Health at start: %f"), Health)
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
