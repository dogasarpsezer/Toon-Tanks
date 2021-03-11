// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerController(bool enabled)
{
	if(!enabled)
	{
		GetPawn()->DisableInput(this);
	}
	else
	{
		GetPawn()->EnableInput(this);
	}

	bShowMouseCursor = enabled;
}

