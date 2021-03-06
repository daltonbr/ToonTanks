// daltonlima.com


#include "TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
//#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{
    Super::BeginPlay();  
    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
    // Check what type of Actor died.
    if (DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
        
        if (PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnableState(false);   
        }        
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
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

    // Blueprint version
    GameStart();

    if (PlayerControllerRef)
    {
        PlayerControllerRef->SetPlayerEnableState(false);

        FTimerHandle PlayerEnableHandle;
        const FTimerDelegate PlayerEnableDelegate =
            FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnableState, true);

        GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false, -1);        
    }   
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    UE_LOG(LogTemp, Warning, TEXT("[TankGameModeBase] HandleGameOver"));
    // See if the player has destroyed all the turrets, show win result.
    // else if turret destroyed player, show lose result.

    // Blueprint version
    GameOver(PlayerWon);
}
