// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class UE5LAB_API Logger
{
private:
	static const FString Format;
public:
	Logger();
	~Logger();
	static void Log(const FString& Message, const bool IsOnScreen = true, const float Exist = 5.0f);
	static void Warning(const FString& Message, const bool IsOnScreen = true, const float Exist = 5.0f);
	static void Error(const FString& Message, const bool IsOnScreen = true, const float Exist = 5.0f);
protected:
private:
};
