// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GalleryPlayerState.generated.h"

template<typename T, int Size>
class TFixedRingBuffer
{
    static_assert(Size > 0, "Ring buffer size must be greater than zero.");

public:
    TFixedRingBuffer()
        : Head(0), Tail(0), Count(0)
    {
    }

    FORCEINLINE bool IsEmpty() const
    {
        return Count == 0;
    }

    FORCEINLINE bool IsFull() const
    {
        return Count == Size;
    }

    FORCEINLINE int Num() const
    {
        return Count;
    }

    void Enqueue(const T& Element)
    {
        Storage[Head] = Element;
        Head = (Head + 1) % Size;
        ++Count;
    }

    void Enqueue(T&& Element)
    {
        Storage[Head] = MoveTemp(Element);
        Head = (Head + 1) % Size;
        ++Count;
        return true;
    }

    bool Dequeue(T& OutElement)
    {
        if (IsEmpty())
        {
            return false;
        }

        OutElement = Storage[Tail];
        Tail = (Tail + 1) % Size;
        --Count;
        return true;
    }

    T Get(int Index)
    {
        verify(Index < Size);
        check(Index < Count);

        return Storage[Index];
    }

    int GetCount() const
    {
        return Count;
    }

private:
    T Storage[Size];
    int Head;
    int Tail;
    int Count;
};

/**
 * 
 */
UCLASS()
class VREXPPLUGINEXAMPLE_API AGalleryPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    AGalleryPlayerState();

    UFUNCTION(BlueprintCallable, Category = "Gallery")
    void AddArtwork(UTexture2D* Artwork);
    UFUNCTION(BlueprintCallable, Category = "Gallery")
    UTexture2D* GetArtwork();
    UFUNCTION(BlueprintCallable, Category = "Gallery")
    int GetSelectedArtworkIndex() const;
    UFUNCTION(BlueprintCallable, Category = "Gallery")
    void SetSelectedArtworkIndex(int Index);

private:
    TFixedRingBuffer<UTexture2D*, 9> Artworks;
    int SelectedArtworkIndex = 0;
};
