// daltonlima.com


#include "TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
//#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();  
    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
    //UE_LOG(LogTemp, Warning, TEXT("[TankGameModeBase] ActorDied"));
    // Check what type of Actor died.
    if (DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
    }
    else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();
        TargetTurrets--;
        if (TargetTurrets <= 0)
        {
            HandleGameOver(true);
        }
        
    }    
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    return TurretActors.Num();
}

void ATankGameModeBase::HandleGameStart()
{    
    // Initialise the start countdown, turret activation, pawn check etc.
    TargetTurrets = GetTargetTurretCount();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    // Call Blueprint version GameStart();
    GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    UE_LOG(LogTemp, Warning, TEXT("[TankGameModeBase] HandleGameOver"));
    // See if the player has destroyed all the turrets, show win result.
    // else if turret destroyed player, show lose result.
    // Call blueprint version GameOver(bool).
    GameOver(PlayerWon);
}
