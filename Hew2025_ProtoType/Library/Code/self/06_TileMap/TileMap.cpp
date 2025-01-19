﻿#include "TileMap.h"
#include"../SafePointers.h"
#include <iostream>
#include <fstream>
#include <sstream>

// 初期化
float TileMap::tileWidth = 100.0f;
float TileMap::tileHeight = 100.0f;

float TileMap::stageWidth = 0.0f;
float TileMap::stageHeight = 0.0f;

TileMap::TileMap() :tiles{std::vector<Object*>()}
{
}

TileMap::~TileMap()
{
    UnInit();
}

/** @brief マップ生成
*   @param std::string _stageFile   生成するマップのファイルパス
*/
void TileMap::GenerateMap(const std::string& _stageFile) 
{
    bool er;

    // ファイル読み込み
    std::vector<int> stageData;
    er = this->LoadStageFile(_stageFile, stageData);
    if (!er) { std::cerr << "ステージファイルの読み込みに失敗しました。" << std::endl; }
    
    // マップ生成
    for (int i = 0; i < TileMap::stageHeight; ++i)
    {
        for (int j = 0; j < TileMap::stageWidth; ++j)
        {
            // 左上から順に指定のタイルを生成
            int index = i * TileMap::stageWidth + j;
            //std::cout << "index:" << index << std::endl;
            Object* newTile = this->CreateTiles(stageData[index]);
            if (newTile) 
            { 
                newTile->SetPos(TileMap::tileWidth * j, TileMap::tileHeight * (-i), 0.0f);
                newTile->SetSize(TileMap::tileWidth, TileMap::tileHeight, 0.0f);
            }
            //std::cout << "j:" << j << std::endl;
        }
    }
}

/** @brief マップの更新
*/
void TileMap::Update() 
{
    for (auto& tile: this->tiles)
    {
        tile->Update();
    }
}

/** @brief マップの描画
*/
void TileMap::Draw()
{
    for (auto& tile : this->tiles)
    {
        tile->Draw();
    }
}

/** @brief 終了処理
*/
void TileMap::UnInit() 
{
    for (auto tile : tiles)
    {
        SAFE_DELETE(tile);
    }
    tiles.clear();
}

/** @brief ステージの大きさ
*   @param const float& _stageWidth ヨコのタイル数
*   @param const float& _stageHeight タテのタイル数
*/
void TileMap::SetStageSize(const float& _stageWidth, const float& _stageHeight)
{
    stageWidth = _stageWidth;
    stageHeight = _stageHeight;
}

/** @brief タイルの大きさ
*   @param const float& _stageWidth ヨコのタイル幅
*   @param const float& _stageHeight タテのタイル幅
*/
void TileMap::SetTileSize(const float& _tileWidth, const float& _tileHeight)
{
    tileWidth = _tileWidth;
    tileHeight = _tileHeight;
}

/** @brief タイルの取得
*   @return std::vector<Object*>& tiles
*/
std::vector<Object*>& TileMap::GetTiles()
{
    return this->tiles;
}

 /**
  * @brief ファイルからステージデータを読み込む
  * @param const std::string& _stageFile ステージファイルのパス
  * @param std::vector<int>& _stageData ステージ情報
  * @return 読み込み成功の場合 true を返す
  */
bool TileMap::LoadStageFile(const std::string& _stageFile, std::vector<int>& _stageData)
{
    // ファイルストリームを開く
    std::ifstream file(_stageFile);

    // ファイルが開けない場合エラーを出力し、falseを返す
    if (!file.is_open())
    {
        std::cerr << "Could not open file: " << _stageFile << std::endl;
        return false;
    }

    _stageData.clear(); // 念のためデータクリア
    std::string line;

    // 最初の1行目からステージ幅を読み込み
    if (std::getline(file, line))
    {
        TileMap::stageWidth = std::stoi(line); // 行全体を整数に変換
    }

    // 2行目からステージ高さを読み込み
    if (std::getline(file, line))
    {
        TileMap::stageHeight = std::stoi(line); // 行全体を整数に変換
    }

    // _stageData のメモリを事前に確保
    _stageData.reserve(TileMap::stageWidth * TileMap::stageHeight);
    int rowCount = 0;

    // ステージデータの読み込み
    while (std::getline(file, line) && rowCount < TileMap::stageHeight)
    {
        std::istringstream ss(line);
        std::string value;
        int colCount = 0;

        // 指定列数まで読み込み
        while (std::getline(ss, value, ',') && colCount < TileMap::stageWidth)
        {
            if (value.empty())
            {
                _stageData.push_back(0); // 値が空の場合、0を追加
            }
            else
            {
                try
                {
                    int intValue = std::stoi(value); // 文字列を整数に変換
                    _stageData.push_back(intValue);  // 変換した値を追加
                }
                // 無効な値の場合や範囲外の値の場合、0を追加
                catch (const std::exception&)
                {
                    std::cerr << "Invalid value: " << value << std::endl;
                    _stageData.push_back(0);
                }
            }
            ++colCount;
        }
        ++rowCount;
    }

    // ファイルを閉じる
    file.close();
    return true; // 読み込み成功
}

/** @brief タイルを生成する
*   @param const int& _tileNum タイルの種類   
*   @return Object* 生成したタイル
*   @memo   TileType::EMPTYの場合はnullptrを戻り値として返す
*/
Object* TileMap::CreateTiles(const int& _tileNum)
{
    Object* newObj = nullptr;

    switch (static_cast<TileType>(_tileNum))
    {
    case TileType::FLOOR:    
        newObj = new Object();
        newObj->Init(L"Asset/Tile/light wood 2.png");
        this->tiles.push_back(newObj);
        break;
    case TileType::SHELF:
        newObj = new Object();
        newObj->Init(L"Asset/Tile/dark wood 2.png");
        this->tiles.push_back(newObj);
        break;
    default:
        break;
    }

    return newObj;
}