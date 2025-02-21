// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/Time.h"
#include "Game/Timestamp.h"

FTime::FTime()
{
	Remainder = 0;
	Minutes = 0;
	Hours = 0;
	Days = 0;
}

FTime::FTime(const FTimestamp Timestamp)
{
	Remainder = Timestamp.Value;
	
	Minutes = FMath::FloorToInt(Remainder / TimePerMinute);
	Remainder = FMath::Fmod(Remainder, TimePerMinute);
	
	Hours = FMath::FloorToInt(Minutes / MinutesPerHour);
	Minutes = FMath::Fmod(Minutes, MinutesPerHour);

	Days = FMath::FloorToInt(Hours / HoursPerDay);
	Hours = FMath::Fmod(Hours, HoursPerDay);
}

FTime FTime::Difference(const FTime Other) const
{
	return FTime(ToTimestamp().Difference(Other.ToTimestamp()));
}

FTimestamp FTime::ToTimestamp() const
{
	FTimestamp Timestamp;
	
	Timestamp.Value = Days;

	Timestamp.Value *= HoursPerDay;
	Timestamp.Value += Hours;

	Timestamp.Value *= MinutesPerHour;
	Timestamp.Value += Minutes;

	Timestamp.Value *= TimePerMinute;
	Timestamp.Value += Remainder;
	
	return Timestamp;
}

FString FTime::ToString() const
{
	FString Ret;

	if(Days > 0)
	{
		Ret += FString::FromInt(Days) + "d";
	}

	if(Hours > 0)
	{
		Ret += FString::FromInt(Hours) + "h";
	}

	if(Minutes > 0)
	{
		Ret += FString::FromInt(Minutes) + "m";
	}

	return Ret;
}
