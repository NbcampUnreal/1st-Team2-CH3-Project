// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Splatoon/Character/SplatoonCharacter.h"
#include "SplatoonPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class SPLATOON_API ASplatoonPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ASplatoonPlayerController();

	// Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* FireAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* TransforAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	UUserWidget* HUDWidgetInstance;
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowHUD();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main")
	TSubclassOf<UUserWidget> MainWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main")
	UUserWidget* MainWidgetInatance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Menu")
	UUserWidget* GameOverWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clear")
	TSubclassOf<UUserWidget> ClearWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clear")
	UUserWidget* ClearWidgetInstance;

	UFUNCTION(BlueprintCallable, Category = "Main")
	void ShowMainMenu();
	UFUNCTION(BlueprintCallable, Category = "Main")
	void StartGame();
	UFUNCTION(BlueprintCallable, Category = "Main")
	void ShowGameOver();
	UFUNCTION(BlueprintCallable, Category = "Main")
	void ShowClearWidget();
};
