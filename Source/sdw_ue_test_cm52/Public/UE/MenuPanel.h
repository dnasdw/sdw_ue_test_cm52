// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuPanel.generated.h"

UCLASS()
class SDW_UE_TEST_CM52_API UMenuPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	UMenuPanel(const FObjectInitializer& ObjectInitializer);

private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonGame5x5Clicked();
	UFUNCTION()
	void OnButtonGame4x4Clicked();

	void OnButtonGameClicked(const std::string& a_sRowAndColumn);

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* m_pButtonGame5x5;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* m_pButtonGame4x4;
};
