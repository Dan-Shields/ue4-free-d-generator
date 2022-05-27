// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FreeDPacketGenerator.generated.h"

/**
 * 
 */
UCLASS()
class FreeDGenerator_API UFreeDPacketGenerator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "FreeD", DisplayName = "Generate FreeD Packet")
	static TArray<uint8> CreateFreeDPacket(FVector position, FRotator rotation);
};
