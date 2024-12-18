// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define ATTRIBUTE_GETTER_PASSTHROUGH(ObjectName, AttributeName) \
	UFUNCTION(BlueprintCallable) \
	FORCEINLINE float Get##AttributeName() \
	{ \
		return ObjectName->Get##AttributeName(); \
	}

#define ATTRIBUTE_GETTER_PASSTHROUGH_ALIAS(ObjectName, AttributeName, Alias) \
	UFUNCTION(BlueprintCallable) \
	FORCEINLINE float Get##Alias() \
	{ \
		return ObjectName->Get##AttributeName(); \
	}

#define ATTRIBUTE_SETTER_PASSTHROUGH(ObjectName, AttributeName) \
	UFUNCTION(BlueprintCallable) \
	FORCEINLINE void Set##AttributeName(float NewVal) \
	{ \
		return ObjectName->Set##AttributeName(NewVal); \
	}

#define ATTRIBUTE_SETTER_PASSTHROUGH_ALIAS(ObjectName, AttributeName, Alias) \
	UFUNCTION(BlueprintCallable) \
	FORCEINLINE void Set##Alias(float NewVal) \
	{ \
		return ObjectName->Set##AttributeName(NewVal); \
	}

#define ATTRIBUTE_INITTER_PASSTHROUGH(ObjectName, AttributeName) \
	UFUNCTION(BlueprintCallable) \
	FORCEINLINE void Init##AttributeName(float NewVal) \
	{ \
		return ObjectName->Init##AttributeName(NewVal); \
	}

#define ATTRIBUTE_INITTER_PASSTHROUGH_ALIAS(ObjectName, AttributeName, Alias) \
	UFUNCTION(BlueprintCallable) \
	FORCEINLINE void Init##Alias(float NewVal) \
	{ \
		return ObjectName->Init##AttributeName(NewVal); \
	}

#define ATTRIBUTE_PASSTHROUGH(ObjectName, AttributeName) \
	ATTRIBUTE_GETTER_PASSTHROUGH(ObjectName, AttributeName) \
	ATTRIBUTE_SETTER_PASSTHROUGH(ObjectName, AttributeName) \
	ATTRIBUTE_INITTER_PASSTHROUGH(ObjectName, AttributeName)

#define ATTRIBUTE_PASSTHROUGH_ALIAS(ObjectName, AttributeName, Alias) \
	ATTRIBUTE_GETTER_PASSTHROUGH_ALIAS(ObjectName, AttributeName, Alias) \
	ATTRIBUTE_SETTER_PASSTHROUGH_ALIAS(ObjectName, AttributeName, Alias) \
	ATTRIBUTE_INITTER_PASSTHROUGH_ALIAS(ObjectName, AttributeName, Alias)
