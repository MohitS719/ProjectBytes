// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_ChooseNextWaypoint.h"

EBTNodeResult::Type UCPP_ChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{


	// Get Patrol Route
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();								// Get the pawn from controller
	auto PatrolRoute = ControlledPawn->FindComponentByClass <UPatrolRoute> ();				// Get patrol route from pawn
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }								// Check for No Patrol Route

	auto PatrolPoints = PatrolRoute->GetPatrolPoints();										// Get Patrolling points from the gaurd
	if (PatrolPoints.Num() == 0)															// Check for empty Patrol points
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Gaurd has no patrol points!"))
		return EBTNodeResult::Failed;
	}

	// Set Next way point
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();								// Get blackboard component
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);					// Get the index of blackboard comp
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);		// Set the value of object

	// Cycle the index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();										// Increment the index and cycle it
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);						// Set the next index as the index

	return EBTNodeResult::Succeeded;
}


