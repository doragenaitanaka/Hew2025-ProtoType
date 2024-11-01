#pragma once
#include<iostream>
#include<vector>
#include"../../Library/Code/self/10_Object/Object.h"
#include"../../Library/Code/self/12_BackGround/BackGround.h"
#include<algorithm>

// define定義
#define	STAGE_X	(10)		// ヨコのマス数
#define	STAGE_Y	(20)		// タテのマス数
#define	BLOCK_SIZE	(22)	// 1マスのサイズ
#define	NEXTBLOCK_MAX	(2)	// Nextを何個表示させるか

// テトリミノの状態
enum TetriminoState
{
	EMPTY,		// 空
	LANDED,		// テトリミノが着地している
	FALLING,	// テトリミノが落下中
	COMPLETE,	// テトリミノが揃った
	GAMEOVER,	// もうテトリミノが置けない状態、ゲームオーバー
};

// テトリミノの形状
enum TetriminoShape
{
	I_MINO,	// I字テトリミノ
	O_MINO,	// O字テトリミノ
	S_MINO,	// S字テトリミノ
	Z_MINO,	// Z字テトリミノ
	J_MINO,	// J字テトリミノ
	L_MINO,	// L字テトリミノ
	T_MINO,	// T字テトリミノ

	SHAPE_NUM= T_MINO,	// 最大値
	SHAPE_MAX,			// テトリミノの数

	SHAPE_NULL = 99,	// 何もないときの色
};

// ブロックに持っていてほしい情報
struct BlockStatus
{
	TetriminoState	minoState;	// 状態
	TetriminoShape	minoShape;	// 形状
};

// テトリミノの向き
enum TetriminoDirection
{
	DEFAULT,		// 出現時の向き
	D_0 = DEFAULT,	// 0度回転
	D_90,			// 90度回転
	D_180,			// 180度回転
	D_270,			// 270度回転

	Direction_MAX,
};

// テトリミノ
struct TetriminoStatus
{
	TetriminoShape	type;
	TetriminoDirection	direction;
};

/**	@brief 	テトリミノの生成を行う関数
*	@param	BlockStatus**	_pp_blockData		テトリミノの状態が格納された配列
*	@param	std::vector<int>& _tetriminoList	落とすテトリミノのリスト
*	@param	int& _currentArray	今何番目のミノを落とすのか
*	@date	2024/06/27
*/
TetriminoShape	CreateTetrimino(BlockStatus** _pp_blockData, std::vector<int>& _tetriminoList, int& _currentArray);

/**	@brief 	Nextブロックの生成を行う関数
*	@param	TetriminoShape**	_pp_nextBlockData		Nextの形状が格納された配列
*	@param	std::vector<int>& _tetriminoList	落とすテトリミノのリスト
*	@param	int& _nextBlockArray	どのnextを表示させるのか
*	@date	2024/09/19
*/
void	CreateNextTetrimino(TetriminoShape** _pp_nextBlockData, std::vector<int>& _tetriminoList, int& _nextBlockArray);

/**	@brief 	テトリミノが落ちたか調べる関数
*	@param	BlockStatus** _pp_blockData	テトリミノの状態が格納された配列
*	@return	bool	isFall	true:落ちた
*	@date	2024/06/27
*/
bool	GetTetriminoIsFall(BlockStatus** _pp_blockData);

/**	@brief 	テトリミノが回転できる状態か調べる関数
*	@param	int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4]		テトリミノの形状データ4次元配列
*	@param	TetriminoState**	_pp_data	テトリミノの状態が格納された配列
*	@param	TetriminoStatus	_currentStatus			現在のテトリミノの状態
*	@param	int  _newDirc	次の向き
*	@param	int	_baseX	基準点x
*	@param	int	_baseY	基準点y
*	@return	bool	isRotate	true:回転できる
*	@date	2024/06/27
*/
bool	GetTetriminoIsRotate(int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4], BlockStatus** _pp_data, TetriminoStatus	_currentStatus, int  _newDirc, int	_baseX, int	_baseY);

/**	@brief 	テトリミノを着地させる関数
*	@param	BlockStatus** _pp_blockData	テトリミノの状態が格納された配列
*	@param	TetriminoStatus _currentStatus
*	@date	2024/06/27
*/
void	LandTetrimino(BlockStatus** _pp_blockData, TetriminoStatus _currentStatus);

/**	@brief 	テトリミノを落下させる関数
*	@param	BlockStatus** _pp_blockData	テトリミノの状態が格納された配列
*	@date	2024/06/27
*/
void	FallTetrimino(BlockStatus** _pp_blockData);

/**	@brief 	各ブロックの色を設定する作業
*	@param		BlockStatus** _pp_blockData			ブロックのデータ配列
*	@param		Object** _pp_blocks					ブロック
*	@date	2024/09/15
*/
void	SetBlockColor(BlockStatus** pp_blockData, Object** _pp_blocks);

/**	@brief 	Nextブロックの色を設定する作業
*	@param		TetriminoShape* _p_nextBlocksShape	Nextブロックの形
*	@param		Object** _pp_NextBlocks				Nextブロック
*	@date	2024/09/19
*/
void	SetNextBlockColor(TetriminoShape** _pp_nextBlocksShape, Object** _pp_NextBlocks);

/**	@brief 	ゲームオーバーかどうか確認する関数
*	@param		BlockStatus** _pp_blockData			ブロックのデータ配列
*	@param		TetriminoState& _gameState			現在のゲームの状態
*	@date	2024/09/15
*/
void	CheckGameover(BlockStatus** _pp_blockData, TetriminoState& _gameState);


/**	@brief 	揃ったブロックを消す関数
*	@param		BlockStatus** _pp_blockData			ブロックのデータ配列
*	@param		TetriminoState& _gameState			現在のゲームの状態
*   @return     int completeNum                     揃った列数
*	@date	2024/09/15
*/
int	DeleteCompleteBlocks(BlockStatus** _pp_blockData, TetriminoState& _gameState);

/**	@brief	ブロックが揃っているか確認
*	@param		BlockStatus** _pp_blockData			ブロックのデータ配列
*	@param		TetriminoState& _gameState			現在のゲームの状態
*	@date	2024/09/15
*/
void	CheckCompleteBlocks(BlockStatus** _pp_blockData, TetriminoState& _gameState);

/**	@brief	スコアの描画
*	@param		unsigned int& _score					スコア
*	@param		BackGround&	_p_scoreBoard	スコア表示用オブジェクト
*	@date	2024/09/15
*/
void	DrawScore(unsigned int& _score, BackGround& _p_scoreBoard);

///**	@brief	テトリミノを回転させる関数
//*	@param	int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4]		テトリミノの形状データ4次元配列
//*	@param		BlockStatus** _pp_blockData			ブロックのデータ配列
//*	@param	TetriminoStatus& _currentTetrimino		現在のミノのステータス
//*	@date	2024/09/15
//*/
//void RotateTetrimino(int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4], BlockStatus** _pp_blockData, TetriminoStatus& _currentTetrimino);