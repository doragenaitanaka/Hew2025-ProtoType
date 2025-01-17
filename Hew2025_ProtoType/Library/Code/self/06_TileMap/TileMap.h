/**	@file	TileMap.h
*	@brief 	タイルマップの生成、管理
*	@date	2025/01/17
*	@memo	.csvで書く際は、
*           (ステージのヨコ幅(タイル数))
*           (ステージのタテ幅(タイル数))
*           (タイルの配置)
*           になるようにしてください
* 
*           [例]
*           3
*           4
*           0,0,0,0,
*           0,2,2,0,
*           1,1,1,1,
*/
#pragma once
#include"../10_Object/Object.h"
#include<vector>
#include <string>

enum class TileType 
{
    EMPTY = 0,
    FLOOR,
    SHELF,
};

class TileMap
{
public:
    TileMap();
    ~TileMap();

    /** @brief マップ生成
    *   @param std::string _stageFile
    */
    void GenerateMap(const std::string& _stageFile);

    /** @brief マップの更新
    */
    void Update();

    /** @brief マップの描画
    */
    void Draw();

    /** @brief 終了処理
    */
    void UnInit();

    /** @brief ステージの大きさ
    *   @param const float& _stageWidth ヨコのタイル数
    *   @param const float& _stageHeight タテのタイル数
    */
    static void SetStageSize(const float& _stageWidth, const float& _stageHeight);

    /** @brief タイルの大きさ
    *   @param const float& _stageWidth ヨコのタイル幅
    *   @param const float& _stageHeight タテのタイル幅
    */
    static void SetTileSize(const float& _tileWidth, const float& _tileHeight);

    /** @brief タイルの取得
    *   @return std::vector<Object*>& tiles  
    */
    std::vector<Object*>& GetTiles();

private:
    /** @brief ファイルからステージデータを読み込む
    *   @param  const std::string          _stageFile  ステージファイルのパス
    *   @param  std::vector<int>&    _stageData  ステージ情報
    *   @return bool    true: 読み込み成功
    */
    bool LoadStageFile(const std::string& _stageFile, std::vector<int>& _stageData);

    /** @brief タイルを生成する
    *   @param const int& _tileNum タイルの種類
    *   @return Object* 生成したタイル
    */
    Object* CreateTiles(const int& _tileNum);

    // タイルオブジェクト
    std::vector<Object*> tiles;

    // タイル幅
    static float tileWidth;
    static float tileHeight;

    // マップの広さ
    static float stageWidth;
    static float stageHeight;
};

