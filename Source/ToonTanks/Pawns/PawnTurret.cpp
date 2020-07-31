// daltonlima.com

#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);    
}

void APawnTurret::CheckFireCondition()
{    
    if (!PlayerPawn) { return; }
    
    if (GetDistanceToPlayer() <= FireRange)
    {
        //TODO: Fire
        UE_LOG(LogTemp, Warning, TEXT("Fire Condition Success"));
    }
}

float APawnTurret::GetDistanceToPlayer()
{
    if (!PlayerPawn) { return 0.0f; }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());    
}

void APawnTurret::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
