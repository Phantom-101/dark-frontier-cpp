// Fill out your copyright notice in the Description page of Project Settings.

#include "Libraries/LinqTest.h"
#include "Libraries/Linq.h"

UValue* UValue::New(const int32 InValue)
{
	UValue* Value = NewObject<UValue>();
	Value->Value = InValue;
	return Value;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLinqTest, "DarkFrontier.Libraries.Linq", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FLinqTest::RunTest(const FString& Parameters)
{
	// Aggregate
	{
		const TArray Nums = { 1, 2, 3, 4, 5 };
		const int32 Aggregate1 = FLinq::Aggregate<int32>(Nums, [](const int32 A, const int32 B) { return A + B; });
		const FString Aggregate2 = FLinq::Aggregate<int32, FString>(Nums, "", [](const FString& Accumulate, const int32 Element) { return Accumulate + FString::FromInt(Element); });
		const int32 Aggregate3 = FLinq::Aggregate<int32, FString, int32>(Nums, "", [](const FString& Accumulate, const int32 Element) { return Accumulate + FString::FromInt(Element); }, [](const FString& Accumulate) { return FCString::Atoi(*Accumulate); });

		TestEqual(TEXT("Aggregate returns correct integer sum"), Aggregate1, 15);
		TestEqual(TEXT("Aggregate returns correct string concatenation"), Aggregate2, "12345");
		TestEqual(TEXT("Aggregate returns correct integer after string concatenation"), Aggregate3, 12345);
	}

	// All
	{
		const TArray Positives = { 1, 2, 3, 4, 5 };
		const TArray Mixed = { 1, -2, 3, -4, 5 };
		const bool All1 = FLinq::All<int32>(Positives, [](const int32 Element) { return Element > 0; });
		const bool All2 = FLinq::All<int32>(Mixed, [](const int32 Element) { return Element > 0; });

		TestEqual(TEXT("All returns true for array with no failing values"), All1, true);
		TestEqual(TEXT("All returns false for array with one or more failing values"), All2, false);
	}

	// Any
	{
		const TArray Positives = { 1, 2, 3, 4, 5 };
		const TArray Mixed = { 1, -2, 3, -4, 5 };
		const bool Any1 = FLinq::Any<int32>(Positives, [](const int32 Element) { return Element < 0; });
		const bool Any2 = FLinq::Any<int32>(Mixed, [](const int32 Element) { return Element < 0; });

		TestEqual(TEXT("Any returns false for array with no succeeding values"), Any1, false);
		TestEqual(TEXT("Any returns true for array with one or more succeeding values"), Any2, true);
	}

	// Cast, OfType
	{
		UBase* Base = NewObject<UBase>();
		UDerived* Derived = NewObject<UDerived>();

		const TArray<UBase*> BaseArray = { Base, Derived };
		const TArray<UDerived*> CastArray = FLinq::Cast<UBase, UDerived>(BaseArray);
		const TArray<UDerived*> OfTypeArray = FLinq::OfType<UBase, UDerived>(BaseArray);

		TestEqual(TEXT("Cast returns correct array"), ArraysEqual(CastArray, { nullptr, Derived }), true);
		TestEqual(TEXT("OfType returns correct array"), ArraysEqual(OfTypeArray, { Derived }), true);
	}

	// Contains
	{
		TArray<UValue*> Values;
		for(int Num = 1; Num <= 5; ++Num)
		{
			UValue* Value = NewObject<UValue>();
			Value->Value = Num;
			Values.Add(Value);
		}

		UValue* A = NewObject<UValue>();
		A->Value = 5;
		UValue* B = NewObject<UValue>();
		B->Value = 6;

		const TFunction<bool (UValue*, UValue*)> Comparer = [](const UValue* A, const UValue* B) { return A->Value == B->Value; };
		const bool Contains1 = FLinq::Contains<UValue*>(Values, A, Comparer);
		const bool Contains2 = FLinq::Contains<UValue*>(Values, B, Comparer);

		TestEqual(TEXT("Contains returns true when there exists an element that is equal when compared to input"), Contains1, true);
		TestEqual(TEXT("Contains returns false when there exists no element that is equal when comnpared to input"), Contains2, false);
	}

	// Distinct, DistinctBy
	{
		const TFunction<bool (int32, int32)> OneOff = [](const int32 A, const int32 B) { return A == B || A == B - 1 || B == A - 1; };
		const TArray Ints = { 1, 1, 2, 4 };
		TArray DistinctInts = FLinq::Distinct<int32>(Ints);
		TArray NonNeighborInts = FLinq::Distinct<int32>(Ints, OneOff);
		TArray Values = { NewObject<UValue>(), NewObject<UValue>(), NewObject<UValue>(), NewObject<UValue>() };
		Values[0]->Value = 1;
		Values[1]->Value = 1;
		Values[2]->Value = 2;
		Values[3]->Value = 4;
		const TFunction<int32 (UValue*)> Selector = [](const UValue* Value) { return Value->Value; };
		TArray DistinctValues = FLinq::DistinctBy<UValue*, int32>(Values, Selector);
		TArray NonNeighborValues = FLinq::DistinctBy<UValue*, int32>(Values, Selector, OneOff);

		TestEqual(TEXT("Distinct returns correct array"), ArraysEqual(DistinctInts, { 1, 2, 4 }), true);
		TestEqual(TEXT("Distinct with comparer returns correct array"), ArraysEqual(NonNeighborInts, { 1, 4 }), true);
		TestEqual(TEXT("DistinctBy returns correct array"), ArraysEqual(DistinctValues, { 1, 2, 4 }), true);
		TestEqual(TEXT("DistinctBy with comparer returns correct array"), ArraysEqual(NonNeighborValues, { 1, 4 }), true);
	}

	// ElementAtOrDefault
	{
		const TArray Ints = { 1 };
		constexpr int32 DefaultInt = 2;
		const TArray Values = { NewObject<UValue>() };
		Values[0]->Value = 1;
		UValue* DefaultValue = NewObject<UValue>();
		DefaultValue->Value = 2;

		const int32 Ret0 = FLinq::ElementAtOrDefault<int32>(Ints, 0);
		const int32 Ret1 = FLinq::ElementAtOrDefault<int32>(Ints, 1);
		const int32 Ret2 = FLinq::ElementAtOrDefault<int32>(Ints, 1, DefaultInt);
		const UValue* Ret3 = FLinq::ElementAtOrDefault<UValue*>(Values, 0);
		const UValue* Ret4 = FLinq::ElementAtOrDefault<UValue*>(Values, 1);
		const UValue* Ret5 = FLinq::ElementAtOrDefault<UValue*>(Values, 1, DefaultValue);

		TestEqual(TEXT("ElementAtOrDefault returns correct value when index exists"), Ret0, 1);
		TestEqual(TEXT("ElementAtOrDefault returns correct value when index does not exist"), Ret1, 0);
		TestEqual(TEXT("ElementAtOrDefault returns correct value when index does not exist"), Ret2, 2);
		TestEqual(TEXT("ElementAtOrDefault returns correct value when index exists"), Ret3 == Values[0], true);
		TestEqual(TEXT("ElementAtOrDefault returns correct value when index does not exist"), Ret4 == nullptr, true);
		TestEqual(TEXT("ElementAtOrDefault returns correct value when index does not exist"), Ret5 == DefaultValue, true);
	}

	// Except, ExceptBy
	{
		const TArray A = { 1, 2, 3, 4, 5 };
		const TArray B = { 2, 3 };
		const TArray C = { UValue::New(1), UValue::New(2), UValue::New(3), UValue::New(4), UValue::New(5) };
		const TArray D = { UValue::New(2), UValue::New(3) };
		const TFunction<bool (int32, int32)> OneOff = [](const int32 A, const int32 B) { return A == B || A == B - 1 || B == A - 1; };
		const TFunction<int32 (UValue*)> Selector = [](const UValue* Value) { return Value->Value; };
		const TArray Except0 = FLinq::Except<int32>(A, B);
		const TArray Except1 = FLinq::Except<int32>(A, B, OneOff);
		const TArray Except2 = FLinq::ExceptBy<UValue*, int32>(C, D, Selector);
		const TArray Except3 = FLinq::ExceptBy<UValue*, int32>(C, D, Selector, OneOff);

		TestEqual(TEXT("Except returns correct array"), ArraysEqual(Except0, { 1, 4, 5 }), true);
		TestEqual(TEXT("Except with comparer returns correct array"), ArraysEqual(Except1, { 5 }), true);
		TestEqual(TEXT("ExceptBy returns correct array"), ArraysEqual(Except2, { 1, 4, 5 }), true);
		TestEqual(TEXT("ExceptBy with comparer returns correct array"), ArraysEqual(Except3, { 5 }), true);
	}

	// FirstOrDefault, LastOrDefault
	{
		const TArray<int32> Empty = {};
		const TArray One = { 1, 3 };
		const TFunction<bool (int32)> TruePredicate = [](const int32 Num) { return Num == 1 || Num == 3; };
		const TFunction<bool (int32)> FalsePredicate = [](const int32 Num) { return Num == 2; };
		constexpr int32 Default = 4;
		const int32 FirstOrDefault0 = FLinq::FirstOrDefault<int32>(Empty);
		const int32 FirstOrDefault1 = FLinq::FirstOrDefault<int32>(Empty, Default);
		const int32 FirstOrDefault2 = FLinq::FirstOrDefault<int32>(One, TruePredicate);
		const int32 FirstOrDefault3 = FLinq::FirstOrDefault<int32>(One, TruePredicate, Default);
		const int32 FirstOrDefault4 = FLinq::FirstOrDefault<int32>(One, FalsePredicate);
		const int32 FirstOrDefault5 = FLinq::FirstOrDefault<int32>(One, FalsePredicate, Default);
		const int32 LastOrDefault0 = FLinq::LastOrDefault<int32>(Empty);
		const int32 LastOrDefault1 = FLinq::LastOrDefault<int32>(Empty, Default);
		const int32 LastOrDefault2 = FLinq::LastOrDefault<int32>(One, TruePredicate);
		const int32 LastOrDefault3 = FLinq::LastOrDefault<int32>(One, TruePredicate, Default);
		const int32 LastOrDefault4 = FLinq::LastOrDefault<int32>(One, FalsePredicate);
		const int32 LastOrDefault5 = FLinq::LastOrDefault<int32>(One, FalsePredicate, Default);

		TestEqual(TEXT("FirstOrDefault returns correct default"), FirstOrDefault0, 0);
		TestEqual(TEXT("FirstOrDefault returns supplied default"), FirstOrDefault1, Default);
		TestEqual(TEXT("FirstOrDefault returns found element"), FirstOrDefault2, 1);
		TestEqual(TEXT("FirstOrDefault returns found element"), FirstOrDefault3, 1);
		TestEqual(TEXT("FirstOrDefault returns correct default"), FirstOrDefault4, 0);
		TestEqual(TEXT("FirstOrDefault returns supplied default"), FirstOrDefault5, Default);
		TestEqual(TEXT("LastOrDefault returns correct default"), LastOrDefault0, 0);
		TestEqual(TEXT("LastOrDefault returns supplied default"), LastOrDefault1, Default);
		TestEqual(TEXT("LastOrDefault returns found element"), LastOrDefault2, 3);
		TestEqual(TEXT("LastOrDefault returns found element"), LastOrDefault3, 3);
		TestEqual(TEXT("LastOrDefault returns correct default"), LastOrDefault4, 0);
		TestEqual(TEXT("LastOrDefault returns supplied default"), LastOrDefault5, Default);
	}

	// Intersect, IntersectBy
	{
		const TArray A = { 1, 2, 3, 4, 5 };
		const TArray B = { 2, 3 };
		const TArray C = { UValue::New(1), UValue::New(2), UValue::New(3), UValue::New(4), UValue::New(5) };
		const TArray D = { UValue::New(2), UValue::New(3) };
		const TFunction<bool (int32, int32)> OneOff = [](const int32 A, const int32 B) { return A == B || A == B - 1 || B == A - 1; };
		const TFunction<int32 (UValue*)> Selector = [](const UValue* Value) { return Value->Value; };
		const TArray Intersect0 = FLinq::Intersect<int32>(A, B);
		const TArray Intersect1 = FLinq::Intersect<int32>(A, B, OneOff);
		const TArray Intersect2 = FLinq::IntersectBy<UValue*, int32>(C, D, Selector);
		const TArray Intersect3 = FLinq::IntersectBy<UValue*, int32>(C, D, Selector, OneOff);

		TestEqual(TEXT("Intersect returns correct array"), ArraysEqual(Intersect0, { 2, 3 }), true);
		TestEqual(TEXT("Intersect with comparer returns correct array"), ArraysEqual(Intersect1, { 1, 2, 3, 4 }), true);
		TestEqual(TEXT("IntersectBy returns correct array"), ArraysEqual(Intersect2, { 2, 3 }), true);
		TestEqual(TEXT("IntersectBy with comparer returns correct array"), ArraysEqual(Intersect3, { 1, 2, 3, 4 }), true);
	}

	// Reverse
	{
		const TArray<int32> Empty = {};
		const TArray One = { 1 };
		const TArray Multiple = { 1, 2, 3 };
		const TArray Reverse0 = FLinq::Reverse<int32>(Empty);
		const TArray Reverse1 = FLinq::Reverse<int32>(One);
		const TArray Reverse2 = FLinq::Reverse<int32>(Multiple);

		TestEqual(TEXT("Reverse returns correct empty array"), ArraysEqual(Reverse0, {}), true);
		TestEqual(TEXT("Reverse returns correct one-element array"), ArraysEqual(Reverse1, { 1 }), true);
		TestEqual(TEXT("Reverse returns correct multiple element array"), ArraysEqual(Reverse2, { 3, 2, 1 }), true);
	}
	
	// Select
	{
		const TArray Values = { UValue::New(1), UValue::New(2), UValue::New(3) };
		const TArray Select0 = FLinq::Select<UValue*, int32>(Values, [](const UValue* Value) { return Value->Value; });
		const TArray Select1 = FLinq::Select<UValue*, int32>(Values, [](const UValue* Value, const int32 Index) { return Value->Value + Index; });

		TestEqual(TEXT("Select returns correct array"), ArraysEqual(Select0, { 1, 2, 3 }), true);
		TestEqual(TEXT("Select with index returns correct array"), ArraysEqual(Select1, { 1, 3, 5 }), true);
	}

	// Skip, SkipLast
	{
		const TArray<int32> Empty = {};
		const TArray Multiple = { 1, 2, 3 };
		const TArray Skip0 = FLinq::Skip<int32>(Empty, 1);
		const TArray Skip1 = FLinq::Skip<int32>(Multiple, 1);
		const TArray SkipLast0 = FLinq::SkipLast<int32>(Empty, 1);
		const TArray SkipLast1 = FLinq::SkipLast<int32>(Multiple, 1);

		TestEqual(TEXT("Skip returns empty array"), ArraysEqual(Skip0, {}), true);
		TestEqual(TEXT("Skip returns correct array"), ArraysEqual(Skip1, { 2, 3 }), true);
		TestEqual(TEXT("SkipLast returns empty array"), ArraysEqual(SkipLast0, {}), true);
		TestEqual(TEXT("SkipLast returns correct array"), ArraysEqual(SkipLast1, { 1, 2 }), true);
	}

	// Where
	{
		const TArray Values = { UValue::New(1), UValue::New(2), UValue::New(3) };
		const TArray Where0 = FLinq::Where<UValue*>(Values, [](const UValue* Value) { return Value->Value > 1; });
		const TArray Where1 = FLinq::Where<UValue*>(Values, [](const UValue* Value, const int32 Index) { return Index < 1; });

		TestEqual(TEXT("Where returns correct array"), ArraysEqual(Where0, { Values[1], Values[2] }), true);
		TestEqual(TEXT("Where with index returns correct array"), ArraysEqual(Where1, { Values[0] }), true);
	}

	return true;
}
