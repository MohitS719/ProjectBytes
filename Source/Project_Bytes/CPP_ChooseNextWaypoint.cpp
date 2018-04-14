// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_ChooseNextWaypoint.h"

EBTNodeResult::Type UCPP_ChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	UE_LOG(LogTemp, Warning, TEXT("Index : %i"), Index)

	return EBTNodeResult::Succeeded;
}


