// Fill out your copyright notice in the Description page of Project Settings.


#include "loadTexture.h"
#include "Engine/Texture2D.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Misc/PackageName.h"
#include "AssetRegistryModule.h"
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"

loadTexture::loadTexture()
{
}

loadTexture::~loadTexture()
{
}

bool loadTexture::LoadTextureAssetFromFile(const FString& FilePath, class UTexture2D*& LoadedTexture)
{
    //IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
    //TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);

    //// 画像データを読み込む
    //TArray<uint8> RawFileData;
    //if (FFileHelper::LoadFileToArray(RawFileData, *FilePath))
    //{
    //    // 非圧縮の画像データを取得
    //   // const TArray<uint8>* UncompressedRawData = nullptr;
    //    TArray<uint8> UncompressedRawData;
    //    if (ImageWrapper.IsValid() &&
    //        ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()) &&
    //        ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedRawData)
    //        )
    //    {
    //        FString Filename = FPaths::GetBaseFilename(FilePath);
    //        int Width = ImageWrapper->GetWidth();
    //        int Height = ImageWrapper->GetHeight();

    //        //// パッケージを作成
    //        //FString PackagePath(TEXT("/Game/LoadedTexture/"));
    //        //FString AbsolutePackagePath = FPaths::ProjectContentDir() + TEXT("/LoadedTexture/");

    //        //FPackageName::RegisterMountPoint(PackagePath, AbsolutePackagePath);

    //        //PackagePath += Filename;

    //        //UPackage* Package = CreatePackage(nullptr, *PackagePath);
    //        //Package->FullyLoad();

    //        // テクスチャを作成
    //        //FName TextureName = MakeUniqueObjectName(Package, UTexture2D::StaticClass(), FName(*Filename));
    //        UTexture2D* Texture = NewObject<UTexture2D>(Package, TextureName, RF_Public | RF_Standalone);

    //        // テクスチャの設定
    //        Texture->PlatformData = new FTexturePlatformData();
    //        Texture->PlatformData->SizeX = Width;
    //        Texture->PlatformData->SizeY = Height;
    //        Texture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
    //        Texture->NeverStream = false;

            //// ピクセルデータをテクスチャに書き込む
            //FTexture2DMipMap* Mip = new FTexture2DMipMap();
            //Texture->PlatformData->Mips.Add(Mip);
            //Mip->SizeX = Width;
            //Mip->SizeY = Height;
            //Mip->BulkData.Lock(LOCK_READ_WRITE);
            //uint8* TextureData = (uint8*)Mip->BulkData.Realloc(UncompressedRawData->Num());
            //FMemory::Memcpy(TextureData, UncompressedRawData->GetData(), UncompressedRawData->Num());
            //Mip->BulkData.Unlock();

            //// テクスチャを更新
            //Texture->AddToRoot();
            //Texture->Source.Init(Width, Height, 1, 1, ETextureSourceFormat::TSF_BGRA8, UncompressedRawData->GetData());
            //Texture->UpdateResource();

            //// パッケージを保存
            //Package->MarkPackageDirty();
            //FAssetRegistryModule::AssetCreated(Texture);
            //LoadedTexture = Texture;

            //FString PackageFilename = FPackageName::LongPackageNameToFilename(PackagePath, FPackageName::GetAssetPackageExtension());
            //return UPackage::SavePackage(Package, Texture, RF_Public | RF_Standalone, *PackageFilename, GError, nullptr, true, true, SAVE_NoError);
      //  }
    //}

    return false;
}

