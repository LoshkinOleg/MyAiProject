// Fill out your copyright notice in the Description page of Project Settings.


#include "EQTest_FilterOffReservedPos.h"

// #include "DrawDebugHelpers.h"

UEQTest_FilterOffReservedPos::UEQTest_FilterOffReservedPos()
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType::StaticClass();
	SetWorkOnFloatValues(false);
	ReservedPositions = UEnvQueryContext::StaticClass();

	// Context = UEnvQueryContext_Querier::StaticClass();
	// TraceData.SetGeometryOnly();
}

void UEQTest_FilterOffReservedPos::RunTest(FEnvQueryInstance& QueryInstance) const
{
	const UObject* const DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);
	const bool bWantsHit = BoolValue.GetValue();

	TArray<FVector> Positions;
	if (!QueryInstance.PrepareContext(ReservedPositions, Positions))
	{
		return;
	}

	const auto IsReserved = [&](const FVector Pos)->bool
	{
		for (const auto& Reserved : Positions)
		{
			// If two positions are less than 1m apart, consider them to be overlapping.
			constexpr const float DISTANCE_THRESHOLD_SQUARED = 100.0f * 100.0f;
			if (FVector::DistSquared2D(Pos, Reserved) < DISTANCE_THRESHOLD_SQUARED)
			{
				// DrawDebugSphere(QueryInstance.World, Pos, 25.0f, 12, FColor::Red, false, 0.25f);
				return true;
			}
		}
		// DrawDebugSphere(QueryInstance.World, Pos, 25.0f, 12, FColor::Green, false, 0.25f);
		return false;
	};

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex());
		It.SetScore(TestPurpose, FilterType, IsReserved(ItemLocation), bWantsHit);
	}
}

FText UEQTest_FilterOffReservedPos::GetDescriptionTitle() const
{
	return FText(FText::FromString("Filter off reserved positions."));
}

FText UEQTest_FilterOffReservedPos::GetDescriptionDetails() const
{
	return FText(FText::FromString("Filters off positions already reserved by other AI's."));
}
