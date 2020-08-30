// daltonlima.com

#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!PlayerPawn || GetDistanceToPlayer() > FireRange)
    {
        return;
    }
    
    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{    
    if (PlayerPawn == nullptr || PlayerPawn->GetIsPlayerAlive() == false) { return; }
    
    if (GetDistanceToPlayer() <= FireRange)
    {
        Fire();
    }
}

float APawnTurret::GetDistanceToPlayer() const
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

void APawnTurret::HandleDestruction()
{
    // Call base Pawn class HandleDestruction to play effects.
    Super::HandleDestruction();

    Destroy();
}
