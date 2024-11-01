#pragma once
#include<iostream>
#include<vector>
#include"../../Library/Code/self/10_Object/Object.h"
#include"../../Library/Code/self/12_BackGround/BackGround.h"
#include<algorithm>

// define��`
#define	STAGE_X	(10)		// ���R�̃}�X��
#define	STAGE_Y	(20)		// �^�e�̃}�X��
#define	BLOCK_SIZE	(22)	// 1�}�X�̃T�C�Y
#define	NEXTBLOCK_MAX	(2)	// Next�����\�������邩

// �e�g���~�m�̏��
enum TetriminoState
{
	EMPTY,		// ��
	LANDED,		// �e�g���~�m�����n���Ă���
	FALLING,	// �e�g���~�m��������
	COMPLETE,	// �e�g���~�m��������
	GAMEOVER,	// �����e�g���~�m���u���Ȃ���ԁA�Q�[���I�[�o�[
};

// �e�g���~�m�̌`��
enum TetriminoShape
{
	I_MINO,	// I���e�g���~�m
	O_MINO,	// O���e�g���~�m
	S_MINO,	// S���e�g���~�m
	Z_MINO,	// Z���e�g���~�m
	J_MINO,	// J���e�g���~�m
	L_MINO,	// L���e�g���~�m
	T_MINO,	// T���e�g���~�m

	SHAPE_NUM= T_MINO,	// �ő�l
	SHAPE_MAX,			// �e�g���~�m�̐�

	SHAPE_NULL = 99,	// �����Ȃ��Ƃ��̐F
};

// �u���b�N�Ɏ����Ă��Ăق������
struct BlockStatus
{
	TetriminoState	minoState;	// ���
	TetriminoShape	minoShape;	// �`��
};

// �e�g���~�m�̌���
enum TetriminoDirection
{
	DEFAULT,		// �o�����̌���
	D_0 = DEFAULT,	// 0�x��]
	D_90,			// 90�x��]
	D_180,			// 180�x��]
	D_270,			// 270�x��]

	Direction_MAX,
};

// �e�g���~�m
struct TetriminoStatus
{
	TetriminoShape	type;
	TetriminoDirection	direction;
};

/**	@brief 	�e�g���~�m�̐������s���֐�
*	@param	BlockStatus**	_pp_blockData		�e�g���~�m�̏�Ԃ��i�[���ꂽ�z��
*	@param	std::vector<int>& _tetriminoList	���Ƃ��e�g���~�m�̃��X�g
*	@param	int& _currentArray	�����Ԗڂ̃~�m�𗎂Ƃ��̂�
*	@date	2024/06/27
*/
TetriminoShape	CreateTetrimino(BlockStatus** _pp_blockData, std::vector<int>& _tetriminoList, int& _currentArray);

/**	@brief 	Next�u���b�N�̐������s���֐�
*	@param	TetriminoShape**	_pp_nextBlockData		Next�̌`�󂪊i�[���ꂽ�z��
*	@param	std::vector<int>& _tetriminoList	���Ƃ��e�g���~�m�̃��X�g
*	@param	int& _nextBlockArray	�ǂ�next��\��������̂�
*	@date	2024/09/19
*/
void	CreateNextTetrimino(TetriminoShape** _pp_nextBlockData, std::vector<int>& _tetriminoList, int& _nextBlockArray);

/**	@brief 	�e�g���~�m�������������ׂ�֐�
*	@param	BlockStatus** _pp_blockData	�e�g���~�m�̏�Ԃ��i�[���ꂽ�z��
*	@return	bool	isFall	true:������
*	@date	2024/06/27
*/
bool	GetTetriminoIsFall(BlockStatus** _pp_blockData);

/**	@brief 	�e�g���~�m����]�ł����Ԃ����ׂ�֐�
*	@param	int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4]		�e�g���~�m�̌`��f�[�^4�����z��
*	@param	TetriminoState**	_pp_data	�e�g���~�m�̏�Ԃ��i�[���ꂽ�z��
*	@param	TetriminoStatus	_currentStatus			���݂̃e�g���~�m�̏��
*	@param	int  _newDirc	���̌���
*	@param	int	_baseX	��_x
*	@param	int	_baseY	��_y
*	@return	bool	isRotate	true:��]�ł���
*	@date	2024/06/27
*/
bool	GetTetriminoIsRotate(int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4], BlockStatus** _pp_data, TetriminoStatus	_currentStatus, int  _newDirc, int	_baseX, int	_baseY);

/**	@brief 	�e�g���~�m�𒅒n������֐�
*	@param	BlockStatus** _pp_blockData	�e�g���~�m�̏�Ԃ��i�[���ꂽ�z��
*	@param	TetriminoStatus _currentStatus
*	@date	2024/06/27
*/
void	LandTetrimino(BlockStatus** _pp_blockData, TetriminoStatus _currentStatus);

/**	@brief 	�e�g���~�m�𗎉�������֐�
*	@param	BlockStatus** _pp_blockData	�e�g���~�m�̏�Ԃ��i�[���ꂽ�z��
*	@date	2024/06/27
*/
void	FallTetrimino(BlockStatus** _pp_blockData);

/**	@brief 	�e�u���b�N�̐F��ݒ肷����
*	@param		BlockStatus** _pp_blockData			�u���b�N�̃f�[�^�z��
*	@param		Object** _pp_blocks					�u���b�N
*	@date	2024/09/15
*/
void	SetBlockColor(BlockStatus** pp_blockData, Object** _pp_blocks);

/**	@brief 	Next�u���b�N�̐F��ݒ肷����
*	@param		TetriminoShape* _p_nextBlocksShape	Next�u���b�N�̌`
*	@param		Object** _pp_NextBlocks				Next�u���b�N
*	@date	2024/09/19
*/
void	SetNextBlockColor(TetriminoShape** _pp_nextBlocksShape, Object** _pp_NextBlocks);

/**	@brief 	�Q�[���I�[�o�[���ǂ����m�F����֐�
*	@param		BlockStatus** _pp_blockData			�u���b�N�̃f�[�^�z��
*	@param		TetriminoState& _gameState			���݂̃Q�[���̏��
*	@date	2024/09/15
*/
void	CheckGameover(BlockStatus** _pp_blockData, TetriminoState& _gameState);


/**	@brief 	�������u���b�N�������֐�
*	@param		BlockStatus** _pp_blockData			�u���b�N�̃f�[�^�z��
*	@param		TetriminoState& _gameState			���݂̃Q�[���̏��
*   @return     int completeNum                     ��������
*	@date	2024/09/15
*/
int	DeleteCompleteBlocks(BlockStatus** _pp_blockData, TetriminoState& _gameState);

/**	@brief	�u���b�N�������Ă��邩�m�F
*	@param		BlockStatus** _pp_blockData			�u���b�N�̃f�[�^�z��
*	@param		TetriminoState& _gameState			���݂̃Q�[���̏��
*	@date	2024/09/15
*/
void	CheckCompleteBlocks(BlockStatus** _pp_blockData, TetriminoState& _gameState);

/**	@brief	�X�R�A�̕`��
*	@param		unsigned int& _score					�X�R�A
*	@param		BackGround&	_p_scoreBoard	�X�R�A�\���p�I�u�W�F�N�g
*	@date	2024/09/15
*/
void	DrawScore(unsigned int& _score, BackGround& _p_scoreBoard);

///**	@brief	�e�g���~�m����]������֐�
//*	@param	int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4]		�e�g���~�m�̌`��f�[�^4�����z��
//*	@param		BlockStatus** _pp_blockData			�u���b�N�̃f�[�^�z��
//*	@param	TetriminoStatus& _currentTetrimino		���݂̃~�m�̃X�e�[�^�X
//*	@date	2024/09/15
//*/
//void RotateTetrimino(int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4], BlockStatus** _pp_blockData, TetriminoStatus& _currentTetrimino);