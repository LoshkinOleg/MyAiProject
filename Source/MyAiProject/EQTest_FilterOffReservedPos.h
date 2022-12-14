// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EQTest_FilterOffReservedPos.generated.h"

/**
 * 
 */
UCLASS()
class MYAIPROJECT_API UEQTest_FilterOffReservedPos : public UEnvQueryTest
{
	GENERATED_BODY()

	UEQTest_FilterOffReservedPos();

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;

	UPROPERTY(EditDefaultsOnly, Category = YoloMate)
	TSubclassOf<UEnvQueryContext> ReservedPositions;
};
