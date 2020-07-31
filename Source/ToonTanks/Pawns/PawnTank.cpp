// daltonlima.com

#include "PawnTank.h"

APawnTank::APawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void APawnTank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Rotate();
    Move();
}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward",this, &APawnTank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
}

void APawnTank::CalculateMoveInput(float Value)
{
    // X is the forward axis
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(float Value)
{
    const float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    const FRotator Rotation = FRotator(0, RotateAmount, 0);
    RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
    AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
    AddActorLocalRotation(RotationDirection, true);
}

void APawnTank::BeginPlay()
{
    Super::BeginPlay();
}
