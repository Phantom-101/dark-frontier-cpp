// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/GameTime.h"
#include "Game/GameTimestamp.h"

UGameTime* UGameTime::FromTimestamp(const UGameTimestamp* Timestamp)
{
	UGameTime* Time = NewObject<UGameTime>();
	
	Time->Fractional = Timestamp->Value;
	
	Time->Minutes = FMath::FloorToInt(Time->Fractional / FractionalPerMinute);
	Time->Fractional = FMath::Fmod(Time->Fractional, FractionalPerMinute);
	
	Time->Hours = FMath::FloorToInt(Time->Minutes / MinutesPerHour);
	Time->Minutes = FMath::Fmod(Time->Minutes, MinutesPerHour);

	Time->Days = FMath::FloorToInt(Time->Hours / HoursPerDay);
	Time->Hours = FMath::Fmod(Time->Hours, HoursPerDay);

	return Time;
}

UGameTimestamp* UGameTime::ToTimestamp() const
{
	UGameTimestamp* Timestamp = NewObject<UGameTimestamp>();
	
	Timestamp->Value = Days;

	Timestamp->Value *= HoursPerDay;
	Timestamp->Value += Hours;

	Timestamp->Value *= MinutesPerHour;
	Timestamp->Value += Minutes;

	Timestamp->Value *= FractionalPerMinute;
	Timestamp->Value += Fractional;
	
	return Timestamp;
}
