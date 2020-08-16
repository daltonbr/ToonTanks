// daltonlima.com


#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{    
    // Get references and game win/lose conditions.

    // Call HandleGameStart() to initialise the start countdown, turret activation, pawn check etc.
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
    UE_LOG(LogTemp, Warning, TEXT("[TankGameModeBase] ActorDied"));
    // Check what type of Actor died.

    // If turret, tally.
    // If player -> got to lose condition.
}

void ATankGameModeBase::HandleGameStart()
{
    UE_LOG(LogTemp, Warning, TEXT("[TankGameModeBase] HandleGameStart"));
    // Initialise the start countdown, turret activation, pawn check etc.
    // Call Blueprint version GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    UE_LOG(LogTemp, Warning, TEXT("[TankGameModeBase] HandleGameOver"));
    // See if the player has destroyed all the turrets, show win result.
    // else if turret destroyed player, show lose result.
    // Call blueprint version GameOver(bool).
}
