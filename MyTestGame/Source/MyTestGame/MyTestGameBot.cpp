// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestGameBot.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyTestGameBot::AMyTestGameBot()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

int AMyTestGameBot::melee_attack_Implementation()
{
	if (montage)
	{
		PlayAnimMontage(montage);
	}
	return 0;
}

UAnimMontage* AMyTestGameBot::get_montage() const
{
	return montage;
}
