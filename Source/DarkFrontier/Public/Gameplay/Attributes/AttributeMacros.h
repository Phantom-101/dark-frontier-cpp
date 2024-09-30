// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define ATTRIBUTE_GETTER_PASSTHROUGH(ObjectName, AttributeName) \
	UFUNCTION(BlueprintCallable) \
	FORCEINLINE float Get##AttributeName() \
	{ \
		return ObjectName->Get##AttributeName(); \
	}

#define ATTRIBUTE_GETTER_PASSTHROUGH_WithPrefix(ObjectName, AttributeName, Prefix) \
	UFUNCTION(BlueprintCallable) \
	FORCEINLINE float Get##Prefix##AttributeName() \
	{ \
		return ObjectName->Get##AttributeName(); \
	}

#define ATTRIBUTE_SETTER_PASSTHROUGH(ObjectName, AttributeName) \
	UFUNCTION(BlueprintCallable) \
	FORCEINLINE void Set##AttributeName(float NewVal) \
	{ \
		return ObjectName->Set##AttributeName(NewVal); \
	}

#define ATTRIBUTE_SETTER_PASSTHROUGH_WithPrefix(ObjectName, AttributeName, Prefix) \
	UFUNCTION(BlueprintCallable) \
	FORCEINLINE void Set##Prefix##AttributeName(float NewVal) \
	{ \
		return ObjectName->Set##AttributeName(NewVal); \
	}

#define ATTRIBUTE_INITTER_PASSTHROUGH(ObjectName, AttributeName) \
	UFUNCTION(BlueprintCallable) \
	FORCEINLINE void Init##AttributeName(float NewVal) \
	{ \
		return ObjectName->Init##AttributeName(NewVal); \
	}

#define ATTRIBUTE_INITTER_PASSTHROUGH_WithPrefix(ObjectName, AttributeName, Prefix) \
	UFUNCTION(BlueprintCallable) \
	FORCEINLINE void Init##Prefix##AttributeName(float NewVal) \
	{ \
		return ObjectName->Init##AttributeName(NewVal); \
	}

#define ATTRIBUTE_PASSTHROUGH(ObjectName, AttributeName) \
	ATTRIBUTE_GETTER_PASSTHROUGH(ObjectName, AttributeName) \
	ATTRIBUTE_SETTER_PASSTHROUGH(ObjectName, AttributeName) \
	ATTRIBUTE_INITTER_PASSTHROUGH(ObjectName, AttributeName)

#define ATTRIBUTE_PASSTHROUGH_WithPrefix(ObjectName, AttributeName, Prefix) \
	ATTRIBUTE_GETTER_PASSTHROUGH_WithPrefix(ObjectName, AttributeName, Prefix) \
	ATTRIBUTE_SETTER_PASSTHROUGH_WithPrefix(ObjectName, AttributeName, Prefix) \
	ATTRIBUTE_INITTER_PASSTHROUGH_WithPrefix(ObjectName, AttributeName, Prefix)
