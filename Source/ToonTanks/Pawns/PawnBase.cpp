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

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	// Update TurretMesh rotation to face towards  the LookAtTarget passed in from Child Classes
	// TurretMesh->SetWorldRotation() ...
}

void APawnBase::Fire()
{
	// Get ProjectileSpawnPoint Location && Rotation
	// Spawn Projectile class at location firing towards Rotation.
}

void APawnBase::HandleDestruction()
{
	// --- Universal functionality ---
	// Play death effects particle, sound and camera shake

	// --- Then do Child overrides ---
	// -- PawnTurret - Inform GameMode Turret died -> Then Destroy() self.

	// -- PawnTank - Inform GameMode Player died -> Then Hide() all components && stop movement input.
}

