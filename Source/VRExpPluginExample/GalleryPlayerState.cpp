// Fill out your copyright notice in the Description page of Project Settings.


#include "GalleryPlayerState.h"

AGalleryPlayerState::AGalleryPlayerState()
{

}

void AGalleryPlayerState::AddArtwork(UTexture2D* Artwork)
{
    Artworks.Enqueue(Artwork);
}

UTexture2D* AGalleryPlayerState::GetArtwork()
{
    if (SelectedArtworkIndex >= Artworks.GetCount())
    {
        return nullptr;
    }

    return Artworks.Get(SelectedArtworkIndex);
}

int AGalleryPlayerState::GetSelectedArtworkIndex() const
{
    return SelectedArtworkIndex;
}

void AGalleryPlayerState::SetSelectedArtworkIndex(int Index)
{
    SelectedArtworkIndex = Index;
}
