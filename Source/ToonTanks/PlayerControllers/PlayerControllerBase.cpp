// daltonlima.com

#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnableState(bool SetPlayerEnabled)
{
    if (SetPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }

    bShowMouseCursor = SetPlayerEnabled;
}
