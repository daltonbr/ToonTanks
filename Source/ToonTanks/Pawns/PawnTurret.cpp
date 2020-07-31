// daltonlima.com

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);    
}

void APawnTurret::CheckFireCondition()
{
    // If Player == null || is Dead THEN BAIL

    // If Player IS in range THEN Fire

    UE_LOG(LogTemp, Warning, TEXT("Fire Condition Checked"));
}

void APawnTurret::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
}
