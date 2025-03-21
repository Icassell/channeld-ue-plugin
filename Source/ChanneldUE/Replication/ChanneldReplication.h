#pragma once
#include "CoreMinimal.h"
#include "ChannelDataInterfaces.h"
#include "ChanneldTypes.h"
#include "UObject/SoftObjectPtr.h"

class FChanneldReplicatorBase;

typedef TFunction<FChanneldReplicatorBase*(UObject*)> FReplicatorCreateFunc;

struct FReplicatorStateInProto
{
	uint32 FieldIndex;
	const UClass* TargetClass;
	FString TargetClassPathName;
	FName TargetClassPathFName;
	bool bIsInMap;
	FReplicatorStateInProto(uint32 InIndex, const UClass* InClass, const FString* InPathName, bool InIsInMap)
		: FieldIndex(InIndex)
		, TargetClass(InClass)
		, TargetClassPathName(InPathName ? *InPathName : TEXT(""))
		, TargetClassPathFName(InPathName ? FName(*InPathName) : FName(NAME_None))
		, bIsInMap(InIsInMap){}
};

namespace ChanneldReplication
{
	extern TMap<const UClass*, const FReplicatorCreateFunc> ReplicatorRegistry;
	extern TMap<const FString, const FReplicatorCreateFunc> BPReplicatorRegistry;
	CHANNELDUE_API void RegisterReplicator(const UClass* TargetClass, const FReplicatorCreateFunc& Func, bool bOverride = true, bool bIsInMap = true);
	CHANNELDUE_API void RegisterReplicator(const FString& PathName, const FReplicatorCreateFunc& Func, bool bOverride = true, bool bIsInMap = true);
	CHANNELDUE_API TArray<FChanneldReplicatorBase*> FindAndCreateReplicators(UObject* ReplicatedObj);
	
	extern TArray<FReplicatorStateInProto> ReplicatorStatesInProto;
	extern TMap<const UClass*, FReplicatorStateInProto> ReplicatorTargetClassToStateInProto;
	CHANNELDUE_API FReplicatorStateInProto* FindReplicatorStateInProto(const UClass* TargetClass);

	extern TMap<const FName, IChannelDataProcessor*> ChannelDataProcessorRegistry;
	CHANNELDUE_API void RegisterChannelDataProcessor(const FName& MessageFullName, IChannelDataProcessor* Processor);
	FORCEINLINE CHANNELDUE_API IChannelDataProcessor* FindChannelDataProcessor(const FName& MessageFullName)
	{
		return ChannelDataProcessorRegistry.FindRef(MessageFullName);
	}

	uint32 GetUnrealObjectType(const UObject* Obj);
}

#define REGISTER_REPLICATOR_BASE(ReplicatorClass, TargetClass, bOverride, bIsInMap) \
	ChanneldReplication::RegisterReplicator(TargetClass::StaticClass(), [](UObject* InTargetObj){ return new ReplicatorClass(CastChecked<TargetClass>(InTargetObj)); }, bOverride, bIsInMap)

#define REGISTER_REPLICATOR_SINGLETON(ReplicatorClass, TargetClass) \
	REGISTER_REPLICATOR_BASE(ReplicatorClass, TargetClass, true, false)

#define REGISTER_REPLICATOR(ReplicatorClass, TargetClass) \
	REGISTER_REPLICATOR_BASE(ReplicatorClass, TargetClass, true, true)

#define REGISTER_REPLICATOR_BP_BASE(ReplicatorClass, BlueprintPathName, bOverride, bIsInMap) \
	ChanneldReplication::RegisterReplicator(BlueprintPathName, [](UObject* InTargetObj){ return new ReplicatorClass(InTargetObj, BlueprintPathName); }, bOverride, bIsInMap)

#define REGISTER_REPLICATOR_BP_SINGLETON(ReplicatorClass, BlueprintPathName) \
	REGISTER_REPLICATOR_BP_BASE(ReplicatorClass, BlueprintPathName, true, false)

#define REGISTER_REPLICATOR_BP(ReplicatorClass, BlueprintPathName) \
	REGISTER_REPLICATOR_BP_BASE(ReplicatorClass, BlueprintPathName, true, true)
