// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define GUARD(Condition) \
	if(!(Condition)) { return; }

#define GUARD_RETURN(Condition, ReturnValue) \
	if(!(Condition)) { return ReturnValue; }

#define ACCESS_COMPONENT(Actor, Component) \
	(Actor->Implements<U##Component##Interface>() ? Cast<I##Component##Interface>(Actor)->Get##Component() : nullptr)

#define REGISTER_ACTOR(Actor, Type, Registry) \
	if(Actor->IsA<Type>()) { Registry.Add(Cast<Type>(Actor)); }

#define UNREGISTER_ACTOR(Actor, Type, Registry) \
	if(Actor->IsA<Type>()) { Registry.Remove(Cast<Type>(Actor)); }

#define REGISTER_COMPONENT_INTERFACE(Actor, Component, Registry) \
	if(Actor->Implements<U##Component##Interface>()) { Registry.Add(Cast<I##Component##Interface>(Actor)->Get##Component()); }

#define UNREGISTER_COMPONENT_INTERFACE(Actor, Component, Registry) \
	if(Actor->Implements<U##Component##Interface>()) { Registry.Remove(Cast<I##Component##Interface>(Actor)->Get##Component()); }
