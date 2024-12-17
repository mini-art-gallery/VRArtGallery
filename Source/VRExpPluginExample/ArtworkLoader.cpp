// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtworkLoader.h"
#include "GalleryPlayerState.h"
#include "GameFramework/PlayerController.h"

void AArtworkLoader::LoadArtwork() {
    FString test = OpenFileDialog();
    UTexture2D* tex = LoadTextureFromFile(test);

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        AGalleryPlayerState* PlayerState = PlayerController->GetPlayerState<AGalleryPlayerState>();
        if (PlayerState)
        {
            PlayerState->AddArtwork(tex);
        }
    }
}

FString AArtworkLoader::OpenFileDialog()
{
    // Ensure the platform module is available
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        // Setup the file dialog filters (e.g., PNG files)
        const FString FileTypes = TEXT("PNG Files|.png|JPEG Files|.jpg|All Files|.");

        // Variable to hold the selected file path
        TArray<FString> SelectedFile;

        // Open the file dialog
        bool bOpened = DesktopPlatform->OpenFileDialog(
            nullptr,                            // Parent window handle (null means no parent)
            TEXT("Select a PNG file"),          // Dialog title
            TEXT(""),                           // Initial directory (empty means default directory)
            TEXT(""),                           // Default file name (optional)
            TEXT(""),                          // Filter for allowed file types
            EFileDialogFlags::None,             // Flags (use None unless you want additional behavior)
            SelectedFile                        // The path of the selected file
        );

        // Return the file path if a file was selected, else return empty
        if (bOpened && !SelectedFile.IsEmpty() && !SelectedFile[0].IsEmpty())
        {
            return SelectedFile[0];
        }
    }

    return FString(); // Return an empty string if no file was selected
}

UTexture2D* AArtworkLoader::LoadTextureFromFile(const FString& FilePath)
{
    // Try to load the texture using the ImageUtils helper function
    UTexture2D* Texture = FImageUtils::ImportFileAsTexture2D(FilePath);
    return Texture;
}


void AArtworkLoader::CreateArtPiece(UTexture2D* ArtTexture) {
    if (ArtTexture)
    {       
        UWorld* World = GetWorld();
        FVector SpawnLocation = FVector(0, 0, 400);

        // Get the current world
        if (World)
        {
            // Set up spawn parameters
            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

            // Spawn the ArtPieceActor at the specified location
            AArtPiece* NewArtPiece = World->SpawnActor<AArtPiece>(AArtPiece::StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnParams);

            if (NewArtPiece)
            {
                // Set the texture for the spawned art piece
                NewArtPiece->SetArtTexture(ArtTexture);
            }
        }
    }
}
