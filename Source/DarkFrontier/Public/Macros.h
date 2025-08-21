// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define GUARD(Condition) \
	if(!(Condition)) { return; }

#define GUARD_RETURN(Condition, ReturnValue) \
	if(!(Condition)) { return ReturnValue; }
