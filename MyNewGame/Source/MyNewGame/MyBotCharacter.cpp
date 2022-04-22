// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBotCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyBotCharacter::AMyBotCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

int AMyBotCharacter::melee_attack_Implementation()
{
	if (montage)
	{
		PlayAnimMontage(montage);
	}
	return 0;
}

UAnimMontage* AMyBotCharacter::get_montage() const
{
	return montage;
}