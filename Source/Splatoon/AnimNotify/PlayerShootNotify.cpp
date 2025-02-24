// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShootNotify.h"
#include "Splatoon/Character/SplatoonCharacter.h"

void UPlayerShootNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* ActorCheck = MeshComp->GetOwner();

	if (ActorCheck) {
		ASplatoonCharacter* PlayerCharacter = Cast<ASplatoonCharacter>(ActorCheck);

		if (PlayerCharacter) {
			GunActor = Cast<ABaseGun>(PlayerCharacter->GunClass);

			if (GunActor) {
				GunActor->Fire();
			}
		}
	}
}
