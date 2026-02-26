
#include "PD_NPCCharacter_Base.h"

#include "GameFramework/CharacterMovementComponent.h"

APD_NPCCharacter_Base::APD_NPCCharacter_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bRequestedMoveUseAcceleration = false;
}

void APD_NPCCharacter_Base::Attack()
{
}

void APD_NPCCharacter_Base::SpecialAttack()
{
}

