// Fill out your copyright notice in the Description page of Project Settings.


#include "Logger.h"

const FString Logger::Format = FString(TEXT("{0} :: {1}"));
#define FORMAT TEXT("%s :: %s")
Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Log(const FString& Message, const bool IsOnScreen, const float Exist)
{
	UE_LOG(LogTemp, Display, FORMAT, *FDateTime::UtcNow().ToString(), *Message);
	if (IsOnScreen) {
		const FString log = FString::Format(*Format, { *FDateTime::UtcNow().ToString(), Message });
		GEngine->AddOnScreenDebugMessage(-1, Exist, FColor::Cyan, log);
	}
}

void Logger::Warning(const FString& Message, const bool IsOnScreen, const float Exist)
{
	UE_LOG(LogTemp, Warning, FORMAT, *FDateTime::UtcNow().ToString(), *Message);
	if (IsOnScreen) {
		const FString log = FString::Format(*Format, { *FDateTime::UtcNow().ToString(), Message });
		GEngine->AddOnScreenDebugMessage(-1, Exist, FColor::Yellow, log);
	}
}

void Logger::Error(const FString& Message, const bool IsOnScreen, const float Exist)
{
	UE_LOG(LogTemp, Error, FORMAT, *FDateTime::UtcNow().ToString(), *Message);
	if (IsOnScreen) {
		const FString log = FString::Format(*Format, { *FDateTime::UtcNow().ToString(), Message });
		GEngine->AddOnScreenDebugMessage(-1, Exist, FColor::Red, log);
	}
}
