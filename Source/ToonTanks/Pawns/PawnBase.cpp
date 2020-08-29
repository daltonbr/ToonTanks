// daltonlima.com

#include "PawnBase.h" 

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
	
}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();	
}

// TurretMesh rotation face towards the LookAtTarget passed in from Child Classes
void APawnBase::RotateTurret(const FVector LookAtTarget) const
{	 	
	const FVector LookAtTargetCleaned = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	const FVector StartLocation = TurretMesh->GetComponentLocation();
	const FRotator TurretRotation = FVector(LookAtTargetCleaned - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{
	if (ProjectileClass == nullptr) { return; }
	
	const FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	const FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
	AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
	
	TempProjectile->SetOwner(this);
	//TempProjectile->SetLifeSpan(6);
}

void APawnBase::HandleDestruction()
{
	// --- Universal functionality ---
	// Play death effects particle, sound and camera shake

	// --- Then do Child overrides ---
	// -- PawnTurret - Inform GameMode Turret died -> Then Destroy() self.

	// -- PawnTank - Inform GameMode Player died -> Then Hide() all components && stop movement input.
}

