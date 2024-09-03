// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class DARKFRONTIER_API FLinq
{
	
public:

	template <typename TElement>
	static TElement Aggregate(TArray<TElement> Source, TFunction<TElement (TElement, TElement)> Func)
	{
		TElement Ret = Source[0];
		
		for(TElement Current : Skip<TElement>(Source, 1))
		{
			Ret = Func(Ret, Current);
		}

		return Ret;
	}

	template <typename TElement, typename TAccumulate>
	static TAccumulate Aggregate(TArray<TElement> Source, TAccumulate Initial, TFunction<TAccumulate (TAccumulate, TElement)> Func)
	{
		TAccumulate Ret = Initial;

		for(TElement Current : Source)
		{
			Ret = Func(Ret, Current);
		}

		return Ret;
	}

	template <typename TElement, typename TAccumulate, typename TResult>
	static TResult Aggregate(TArray<TElement> Source, TAccumulate Initial, TFunction<TAccumulate (TAccumulate, TElement)> Func, TFunction<TResult (TAccumulate)> Selector)
	{
		TAccumulate Accumulate = Initial;

		for(TElement Current : Source)
		{
			Accumulate = Func(Accumulate, Current);
		}

		return Selector(Accumulate);
	}

	template <typename TElement>
	static bool All(TArray<TElement> Source, TFunction<bool (TElement)> Predicate)
	{
		for(TElement Current : Source)
		{
			if(!Predicate(Current))
			{
				return false;
			}
		}

		return true;
	}

	template <typename TElement>
	static bool Any(TArray<TElement> Source, TFunction<bool (TElement)> Predicate)
	{
		for(TElement Current : Source)
		{
			if(Predicate(Current))
			{
				return true;
			}
		}

		return false;
	}

	template <typename TElement, typename TResult>
	static TArray<TResult*> Cast(TArray<TElement*> Source)
	{
		TArray<TResult*> Ret;
		
		for(TElement* Current : Source)
		{
			Ret.Add(::Cast<TResult>(Current));
		}
		
		return Ret;
	}

	template <typename TElement>
	static bool Contains(TArray<TElement> Source, TElement Element, TFunction<bool (TElement, TElement)> Comparer)
	{
		return Source.ContainsByPredicate([&](TElement Current) { return Comparer(Current, Element); });
	}

	template <typename TElement>
	static TArray<TElement> Distinct(TArray<TElement> Source)
	{
		TArray<TElement> Ret;

		for(TElement Current : Source)
		{
			Ret.AddUnique(Current);
		}

		return Ret;
	}

	template <typename TElement>
	static TArray<TElement> Distinct(TArray<TElement> Source, TFunction<bool (TElement, TElement)> Comparer)
	{
		TArray<TElement> Ret;

		for(TElement Current : Source)
		{
			if(!Ret.ContainsByPredicate([&](TElement Element) { return Comparer(Current, Element); }))
			{
				Ret.Add(Current);
			}
		}

		return Ret;
	}

	template <typename TElement, typename TKey>
	static TArray<TKey> DistinctBy(TArray<TElement> Source, TFunction<TKey (TElement)> Selector)
	{
		TArray<TKey> Ret;

		for(TElement Current : Source)
		{
			if(!Ret.ContainsByPredicate([&](TKey Key) { return Selector(Current) == Key; }))
			{
				Ret.Add(Selector(Current));
			}
		}

		return Ret;
	}

	template <typename TElement, typename TKey>
	static TArray<TKey> DistinctBy(TArray<TElement> Source, TFunction<TKey (TElement)> Selector, TFunction<bool (TKey, TKey)> Comparer)
	{
		TArray<TKey> Ret;

		for(TElement Current : Source)
		{
			if(!Ret.ContainsByPredicate([&](TKey Key) { return Comparer(Selector(Current), Key); }))
			{
				Ret.Add(Selector(Current));
			}
		}

		return Ret;
	}

	template <typename TElement>
	static TElement ElementAtOrDefault(TArray<TElement> Source, int32 Index)
	{
		if(Index >= 0 && Index < Source.Num())
		{
			return Source[Index];
		}

		return TElement();
	}
	
	template <typename TElement>
	static TElement ElementAtOrDefault(TArray<TElement> Source, int32 Index, TElement Default)
	{
		if(Index >= 0 && Index < Source.Num())
		{
			return Source[Index];
		}

		return Default;
	}

	template <typename TElement>
	static TArray<TElement> Except(TArray<TElement> First, TArray<TElement> Second)
	{
		return Where<TElement>(Distinct<TElement>(First), [&](TElement Element) { return !Second.Contains(Element); });
	}

	template <typename TElement>
	static TArray<TElement> Except(TArray<TElement> First, TArray<TElement> Second, TFunction<bool (TElement, TElement)> Comparer)
	{
		return Where<TElement>(Distinct<TElement>(First), [&](TElement Element) { return !Contains(Second, Element, Comparer); });
	}

	template <typename TElement, typename TKey>
	static TArray<TKey> ExceptBy(TArray<TElement> First, TArray<TElement> Second, TFunction<TKey (TElement)> Selector)
	{
		TArray<TKey> FirstKey = Select<TElement, TKey>(First, Selector);
		TArray<TKey> SecondKey = Select<TElement, TKey>(Second, Selector);
		return Except<TKey>(FirstKey, SecondKey);
	}

	template <typename TElement, typename TKey>
	static TArray<TKey> ExceptBy(TArray<TElement> First, TArray<TElement> Second, TFunction<TKey (TElement)> Selector, TFunction<bool (TKey, TKey)> Comparer)
	{
		TArray<TKey> FirstKey = Select<TElement, TKey>(First, Selector);
		TArray<TKey> SecondKey = Select<TElement, TKey>(Second, Selector);
		return Except<TKey>(FirstKey, SecondKey, Comparer);
	}

	template <typename TElement>
	static TElement FirstOrDefault(TArray<TElement> Source)
	{
		return Source.Num() == 0 ? TElement() : Source[0];
	}
	
	template <typename TElement>
	static TElement FirstOrDefault(TArray<TElement> Source, TElement Default)
	{
		return Source.Num() == 0 ? Default : Source[0];
	}

	template <typename TElement>
	static TElement FirstOrDefault(TArray<TElement> Source, TFunction<bool (TElement)> Predicate)
	{
		TElement* Ptr = Source.FindByPredicate(Predicate);
		return Ptr == nullptr ? TElement() : *Ptr;
	}

	template <typename TElement>
	static TElement FirstOrDefault(TArray<TElement> Source, TFunction<bool (TElement)> Predicate, TElement Default)
	{
		TElement* Ptr = Source.FindByPredicate(Predicate);
		return Ptr == nullptr ? Default : *Ptr;
	}

	template <typename TElement>
	static TArray<TElement> Intersect(TArray<TElement> First, TArray<TElement> Second)
	{
		return Where<TElement>(Distinct<TElement>(First), [&](TElement Element) { return Second.Contains(Element); });
	}

	template <typename TElement>
	static TArray<TElement> Intersect(TArray<TElement> First, TArray<TElement> Second, TFunction<bool (TElement, TElement)> Comparer)
	{
		return Where<TElement>(Distinct<TElement>(First), [&](TElement Element) { return Contains(Second, Element, Comparer); });
	}

	template <typename TElement, typename TKey>
	static TArray<TKey> IntersectBy(TArray<TElement> First, TArray<TElement> Second, TFunction<TKey (TElement)> Selector)
	{
		TArray<TKey> FirstKey = Select<TElement, TKey>(First, Selector);
		TArray<TKey> SecondKey = Select<TElement, TKey>(Second, Selector);
		return Intersect<TKey>(FirstKey, SecondKey);
	}

	template <typename TElement, typename TKey>
	static TArray<TKey> IntersectBy(TArray<TElement> First, TArray<TElement> Second, TFunction<TKey (TElement)> Selector, TFunction<bool (TKey, TKey)> Comparer)
	{
		TArray<TKey> FirstKey = Select<TElement, TKey>(First, Selector);
		TArray<TKey> SecondKey = Select<TElement, TKey>(Second, Selector);
		return Intersect<TKey>(FirstKey, SecondKey, Comparer);
	}

	template <typename TElement>
	static TElement LastOrDefault(TArray<TElement> Source)
	{
		return Source.Num() == 0 ? TElement() : Source.Last();
	}

	template <typename TElement>
	static TElement LastOrDefault(TArray<TElement> Source, TElement Default)
	{
		return Source.Num() == 0 ? Default : Source.Last();
	}

	template <typename TElement>
	static TElement LastOrDefault(TArray<TElement> Source, TFunction<bool (TElement)> Predicate)
	{
		int32 Index = Source.FindLastByPredicate(Predicate);
		return Index == INDEX_NONE ? TElement() : Source[Index];
	}

	template <typename TElement>
	static TElement LastOrDefault(TArray<TElement> Source, TFunction<bool (TElement)> Predicate, TElement Default)
	{
		int32 Index = Source.FindLastByPredicate(Predicate);
		return Index == INDEX_NONE ? Default : Source[Index];
	}

	template <typename TElement, typename TResult>
	static TArray<TResult*> OfType(TArray<TElement*> Source)
	{
		return Where<TResult*>(Cast<TElement, TResult>(Source), [](TResult* Result) { return Result != nullptr; });
	}

	// TODO Order

	template <typename TElement>
	static TArray<TElement> Reverse(TArray<TElement> Source)
	{
		TArray<TElement> Ret;

		for(int32 Index = Source.Num() - 1; Index >= 0; --Index)
		{
			Ret.Add(Source[Index]);
		}

		return Ret;
	}

	template <typename TElement, typename TResult>
	static TArray<TResult> Select(TArray<TElement> Source, TFunction<TResult (TElement)> Selector)
	{
		TArray<TResult> Ret;

		for(TElement Current : Source)
		{
			Ret.Add(Selector(Current));
		}

		return Ret;
	}

	template <typename TElement, typename TResult>
	static TArray<TResult> Select(TArray<TElement> Source, TFunction<TResult (TElement, int32)> Selector)
	{
		TArray<TResult> Ret;

		int32 Index = 0;
		for(TElement Current : Source)
		{
			Ret.Add(Selector(Current, Index));
			++Index;
		}

		return Ret;
	}

	// TODO SelectMany

	template <typename TElement>
	static TArray<TElement> Skip(TArray<TElement> Source, const int32 Count)
	{
		TArray<TElement> Ret;
		
		for(int32 Index = Count; Index < Source.Num(); ++Index)
		{
			Ret.Add(Source[Index]);
		}

		return Ret;
	}

	template <typename TElement>
	static TArray<TElement> SkipLast(TArray<TElement> Source, const int32 Count)
	{
		TArray<TElement> Ret;

		for(int32 Index = 0; Index < Source.Num() - Count; ++Index)
		{
			Ret.Add(Source[Index]);
		}

		return Ret;
	}

	template <typename TElement>
	static TArray<TElement> Where(TArray<TElement> Source, TFunction<bool (TElement)> Predicate)
	{
		TArray<TElement> Ret;

		for(TElement Current : Source)
		{
			if(Predicate(Current))
			{
				Ret.Add(Current);
			}
		}

		return Ret;
	}

	template <typename TElement>
	static TArray<TElement> Where(TArray<TElement> Source, TFunction<bool (TElement, int32)> Predicate)
	{
		TArray<TElement> Ret;

		int32 Index = 0;
		for(TElement Current : Source)
		{
			if(Predicate(Current, Index))
			{
				Ret.Add(Current);
			}

			++Index;
		}

		return Ret;
	}

};
