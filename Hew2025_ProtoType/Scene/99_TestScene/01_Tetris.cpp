#include"01_Tetris.h"

/**	@brief 	�e�g���~�m�̐������s���֐�
*	@param	BlockStatus**	_pp_blockData		�e�g���~�m�̏�Ԃ��i�[���ꂽ�z��
*	@param	std::vector<int>& _tetriminoList	���Ƃ��e�g���~�m�̃��X�g
*	@param	int& _currentArray	�����Ԗڂ̃~�m�𗎂Ƃ��̂�
*	@date	2024/06/27
*/
TetriminoShape	CreateTetrimino(BlockStatus** _pp_blockData, std::vector<int>& _tetriminoList,int&  _currentArray)
{
    TetriminoShape shapeType = (TetriminoShape)_tetriminoList[_currentArray];

    switch (shapeType)
    {
    case I_MINO:
        _pp_blockData[4][19].minoState = TetriminoState::FALLING;
        _pp_blockData[5][19].minoState = TetriminoState::FALLING;
        _pp_blockData[6][19].minoState = TetriminoState::FALLING;
        _pp_blockData[7][19].minoState = TetriminoState::FALLING;

        _pp_blockData[4][19].minoShape = shapeType;
        _pp_blockData[5][19].minoShape = shapeType;
        _pp_blockData[6][19].minoShape = shapeType;
        _pp_blockData[7][19].minoShape = shapeType;
        break;              
    case O_MINO:            
        _pp_blockData[5][20].minoState = TetriminoState::FALLING;
        _pp_blockData[6][20].minoState = TetriminoState::FALLING;
        _pp_blockData[5][19].minoState = TetriminoState::FALLING;
        _pp_blockData[6][19].minoState = TetriminoState::FALLING;

        _pp_blockData[5][20].minoShape = shapeType;
        _pp_blockData[6][20].minoShape = shapeType;
        _pp_blockData[5][19].minoShape = shapeType;
        _pp_blockData[6][19].minoShape = shapeType;
        break;
    case S_MINO:            
        _pp_blockData[4][19].minoState = TetriminoState::FALLING;
        _pp_blockData[5][19].minoState = TetriminoState::FALLING;
        _pp_blockData[5][20].minoState = TetriminoState::FALLING;
        _pp_blockData[6][20].minoState = TetriminoState::FALLING;

        _pp_blockData[4][19].minoShape = shapeType;
        _pp_blockData[5][19].minoShape = shapeType;
        _pp_blockData[5][20].minoShape = shapeType;
        _pp_blockData[6][20].minoShape = shapeType;
        break;              
    case Z_MINO:            
        _pp_blockData[4][20].minoState = TetriminoState::FALLING;
        _pp_blockData[5][20].minoState = TetriminoState::FALLING;
        _pp_blockData[5][19].minoState = TetriminoState::FALLING;
        _pp_blockData[6][19].minoState = TetriminoState::FALLING;

        _pp_blockData[4][20].minoShape = shapeType;
        _pp_blockData[5][20].minoShape = shapeType;
        _pp_blockData[5][19].minoShape = shapeType;
        _pp_blockData[6][19].minoShape = shapeType;
        break;              
    case J_MINO:            
        _pp_blockData[4][20].minoState = TetriminoState::FALLING;
        _pp_blockData[4][19].minoState = TetriminoState::FALLING;
        _pp_blockData[5][19].minoState = TetriminoState::FALLING;
        _pp_blockData[6][19].minoState = TetriminoState::FALLING;

        _pp_blockData[4][20].minoShape = shapeType;
        _pp_blockData[4][19].minoShape = shapeType;
        _pp_blockData[5][19].minoShape = shapeType;
        _pp_blockData[6][19].minoShape = shapeType;
        break;              
    case L_MINO:            
        _pp_blockData[4][19].minoState = TetriminoState::FALLING;
        _pp_blockData[5][19].minoState = TetriminoState::FALLING;
        _pp_blockData[6][19].minoState = TetriminoState::FALLING;
        _pp_blockData[6][20].minoState = TetriminoState::FALLING;

        _pp_blockData[4][19].minoShape = shapeType;
        _pp_blockData[5][19].minoShape = shapeType;
        _pp_blockData[6][19].minoShape = shapeType;
        _pp_blockData[6][20].minoShape = shapeType;
        break;              
    case T_MINO:            
        _pp_blockData[4][19].minoState = TetriminoState::FALLING;
        _pp_blockData[5][19].minoState = TetriminoState::FALLING;
        _pp_blockData[6][19].minoState = TetriminoState::FALLING;
        _pp_blockData[5][20].minoState = TetriminoState::FALLING;

        _pp_blockData[4][19].minoShape = shapeType;
        _pp_blockData[5][19].minoShape = shapeType;
        _pp_blockData[6][19].minoShape = shapeType;
        _pp_blockData[5][20].minoShape = shapeType;
    default:
        break;
    }
    
    // �v�f��i�߂�
    if (_currentArray == TetriminoShape::SHAPE_MAX * 2 - 1) { _currentArray = 0; }
    else { _currentArray++; }

    // 1���ڂ��I������Ƃ�1���ڂ���בւ�����
    if (_currentArray == TetriminoShape::SHAPE_MAX)
    { 
         for (int i = 0; i < TetriminoShape::SHAPE_MAX; i++)
        {
            int j = rand() % (i + 1);
            std::swap(_tetriminoList[i], _tetriminoList[j]);
        }
    } 
    // 2���ڂ��I������Ƃ�2���ڂ���בւ�����
    if (_currentArray == 0)
    {
        for (int i = TetriminoShape::SHAPE_MAX; i < TetriminoShape::SHAPE_MAX * 2; i++)
        {
            int j = (rand() % (i + 1 - TetriminoShape::SHAPE_MAX)) + TetriminoShape::SHAPE_MAX;
            std::swap(_tetriminoList[i], _tetriminoList[j]);
        }
    }
    return  shapeType;
}

/**	@brief 	Next�u���b�N�̐������s���֐�
*	@param	TetriminoShape**	_pp_nextBlockData		Next�̌`�󂪊i�[���ꂽ�z��
*	@param	std::vector<int>& _tetriminoList	���Ƃ��e�g���~�m�̃��X�g
*	@param	int& _nextBlockArray	�ǂ�next��\��������̂�
*	@date	2024/09/19
*/
void	CreateNextTetrimino(TetriminoShape** _pp_nextBlockData, std::vector<int>& _tetriminoList, int& _nextBlockArray)
{
    // ��x�\�������Z�b�g����
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < STAGE_Y; y++)
        {
            _pp_nextBlockData[x][y] = TetriminoShape::SHAPE_NULL;
        }
    }

    // �w����\��������
    for (int i = 0; i < 1; i++)
    {
        TetriminoShape shape = (TetriminoShape)_tetriminoList[_nextBlockArray + i];
        int nextY = i * 4;  // �\�����n�߂�ʒu

        // �u���b�N�̕\��
        switch (shape)
        {
        case I_MINO:
            _pp_nextBlockData[nextY + 0][2] = shape;
            _pp_nextBlockData[nextY + 1][2] = shape;
            _pp_nextBlockData[nextY + 2][2] = shape;
            _pp_nextBlockData[nextY + 3][2] = shape;
            break;
        case O_MINO:
            _pp_nextBlockData[nextY + 1][1] = shape;
            _pp_nextBlockData[nextY + 2][1] = shape;
            _pp_nextBlockData[nextY + 1][2] = shape;
            _pp_nextBlockData[nextY + 2][2] = shape;
            break;
        case S_MINO:
            _pp_nextBlockData[nextY + 0][2] = shape;
            _pp_nextBlockData[nextY + 1][2] = shape;
            _pp_nextBlockData[nextY + 1][3] = shape;
            _pp_nextBlockData[nextY + 2][3] = shape;
            break;
        case Z_MINO:
            _pp_nextBlockData[nextY + 1][2] = shape;
            _pp_nextBlockData[nextY + 2][2] = shape;
            _pp_nextBlockData[nextY + 0][3] = shape;
            _pp_nextBlockData[nextY + 1][3] = shape;
            break;
        case J_MINO:
            _pp_nextBlockData[nextY + 0][2] = shape;
            _pp_nextBlockData[nextY + 1][2] = shape;
            _pp_nextBlockData[nextY + 2][2] = shape;
            _pp_nextBlockData[nextY + 0][3] = shape;
            break;
        case L_MINO:
            _pp_nextBlockData[nextY + 0][2] = shape;
            _pp_nextBlockData[nextY + 1][2] = shape;
            _pp_nextBlockData[nextY + 2][2] = shape;
            _pp_nextBlockData[nextY + 2][3] = shape;
            break;
        case T_MINO:
            _pp_nextBlockData[nextY + 0][2] = shape;
            _pp_nextBlockData[nextY + 1][2] = shape;
            _pp_nextBlockData[nextY + 2][2] = shape;
            _pp_nextBlockData[nextY + 1][3] = shape;
        default:
            break;
        }
    }
    _nextBlockArray++;
    if (_nextBlockArray >= TetriminoShape::SHAPE_MAX * 2)
    {
        _nextBlockArray = 0;
    }
}

/**	@brief 	�e�g���~�m�������������ׂ�֐�
*	@param	BlockStatus** _pp_blockData	�e�g���~�m�̏�Ԃ��i�[���ꂽ�z��
*	@return	bool	isFall	true:������
*	@date	2024/06/27
*/
bool	GetTetriminoIsFall(BlockStatus** _pp_blockData)
{
    // ���Ƃ��邩���ׂ�
    bool    isFall = true;  //true:������
    for (int x = 0; x < STAGE_X; x++)
    {
        for (int y = 0; y < STAGE_Y + 3; y++)
        {
            //���Ƃ���u���b�N && ( ��ԉ��ɂ��� || 1�}�X���Ƀu���b�N������ )
            if (_pp_blockData[x][y].minoState == TetriminoState::FALLING && (y == TetriminoState::EMPTY || _pp_blockData[x][y - 1].minoState == TetriminoState::LANDED))
            {
                isFall = false;             // �����Ȃ�
                break;
            }
        }
        if (!isFall) { break; }
    }
    return  isFall;
}

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
bool	GetTetriminoIsRotate(int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4], BlockStatus** _pp_data, TetriminoStatus	_currentStatus, int  _newDirc, int	_baseX, int	_baseY)
{
    bool    isRotate = true;
    for (int tx = 0; tx < 4; tx++)
    {
        for (int ty = 0; ty < 4; ty++)
        {
            if (_tetriminoData[_currentStatus.type][_newDirc][ty][tx] == TetriminoState::FALLING &&
                // �X�e�[�W����͂ݏo��Ƃ�
                (   _baseX + tx > STAGE_X - 1 ||                                                  
                    _baseY + ty > STAGE_Y - 1 ||
                    _baseX + tx < 0 ||
                    _baseY + ty < 0 ||
                    _pp_data[_baseX + tx][_baseY + ty].minoState == TetriminoState::LANDED       // ���Ƀu���b�N������
                )
            )
            {
                isRotate = false;  // ��]�ł��Ȃ�
                break;
            }
        }
        if (!isRotate) { break; }
    }
    return  isRotate;
}

/**	@brief 	�e�g���~�m�𒅒n������֐�
*	@param	BlockStatus** _pp_blockData	�e�g���~�m�̏�Ԃ��i�[���ꂽ�z��
*	@param	TetriminoStatus _currentStatus
*	@date	2024/06/27
*/
void	LandTetrimino(BlockStatus** _pp_blockData, TetriminoStatus _currentStatus)
{
    //���n��ɕύX
    for (int x = 0; x < STAGE_X; x++)
    {
        for (int y = 0; y < STAGE_Y + 3; y++)
        {
            if (_pp_blockData[x][y].minoState == TetriminoState::FALLING)
            {
                _pp_blockData[x][y].minoState = TetriminoState::LANDED;
                _pp_blockData[x][y].minoShape = _currentStatus.type;
            }
        }
    }
}

/**	@brief 	�e�g���~�m�𗎉�������֐�
*	@param	BlockStatus** _pp_blockData	�e�g���~�m�̏�Ԃ��i�[���ꂽ�z��
*	@date	2024/06/27
*/
void	FallTetrimino(BlockStatus** _pp_blockData)
{
    // �ꎞ�I�ɍX�V�����ڂ�
    BlockStatus temp[STAGE_X][STAGE_Y + 3] = {};
    for (int x = 0; x < STAGE_X; x++)
    {
        for (int y = 0; y < STAGE_Y + 3; y++)
        {
            // �������̃I�u�W�F�N�g��1�i������
            if (_pp_blockData[x][y].minoState == TetriminoState::FALLING)
            {
                temp[x][y - 1].minoState = TetriminoState::FALLING;
                temp[x][y - 1].minoShape = _pp_blockData[x][y].minoShape;
            }
            // ����ȊO���R�s�[
            else if (_pp_blockData[x][y].minoState == TetriminoState::LANDED)
            {
                temp[x][y].minoState = TetriminoState::LANDED;
                temp[x][y].minoShape = _pp_blockData[x][y].minoShape;
            }
        }
    }
    // �X�V�������f�[�^�ɃR�s�[
    for (int x = 0; x < STAGE_X; x++)
    {
        for (int y = 0; y < STAGE_Y + 3; y++)
        {
            _pp_blockData[x][y].minoState = temp[x][y].minoState;
            _pp_blockData[x][y].minoShape = temp[x][y].minoShape;
        }
    }
}

/**	@brief 	�e�u���b�N�̐F��ݒ肷����
*	@param		BlockStatus** _pp_blockData			�u���b�N�̃f�[�^�z��
*	@param		Object** _pp_blocks					�u���b�N
*	@date	2024/09/15
*/
void	SetBlockColor(BlockStatus** _pp_blockData, Object** _pp_blocks)
{
    //for (int x = 0; x < STAGE_X; x++)
    //{
    //    for (int y = 0; y < STAGE_Y; y++)
    //    {
    //        switch (_pp_blockData[x][y].minoState)
    //        {
    //        case EMPTY:
    //            _pp_blocks[x][y].SetColor({ 0.0f, 0.8f, 0.9f,  0.2f });
    //            break;
    //        case LANDED:
    //            _pp_blocks[x][y].SetColor({ 0.9f, 0.7f, 0.0f, 1.0f });
    //            break;
    //        case FALLING:
    //            _pp_blocks[x][y].SetColor({ 0.0f, 0.9f, 0.0f, 1.0f });
    //            break;
    //        case COMPLETE:
    //            _pp_blocks[x][y].SetColor({ 0.9f, 1.0f, 0.0f, 1.0f });
    //            break;
    //        case GAMEOVER:
    //            _pp_blocks[x][y].SetColor({ 0.9f, 0.0f, 0.0f, 1.0f });
    //            break;
    //        default:
    //            break;
    //        }
    //    }
    //}

    // �F��t����
    for (int x = 0; x < STAGE_X; x++)
    {
        for (int y = 0; y < STAGE_Y; y++)
        {
            // �u���b�N���̂̐F
            switch (_pp_blockData[x][y].minoShape)
            {
                // ���F
            case I_MINO:
                _pp_blocks[x][y].SetColor({ 0.0f, 0.8f, 0.9f, 1.0f });
                break;
                // ���F
            case O_MINO:
                _pp_blocks[x][y].SetColor({ 0.9f, 0.7f, 0.0f, 1.0f });
                break;
                // �ΐF
            case S_MINO:
                _pp_blocks[x][y].SetColor({ 0.0f, 0.9f, 0.0f, 1.0f });
                break;
                // �ԐF
            case Z_MINO:
                _pp_blocks[x][y].SetColor({ 0.9f, 0.0f, 0.0f, 1.0f });
                break;
                // �F
            case J_MINO:
                _pp_blocks[x][y].SetColor({ 0.1f, 0.3f, 0.9f, 1.0f });
                break;
                // ��F
            case L_MINO:
                _pp_blocks[x][y].SetColor({ 0.9f, 0.4f, 0.0f, 1.0f });
                break;
                // ���F
            case T_MINO:
                _pp_blocks[x][y].SetColor({ 0.7f, 0.3f, 0.8f, 1.0f });
                break;
            default:
                _pp_blocks[x][y].SetColor({ 1.0f, 1.0f, 1.0f, 0.2f });
                break;
            }

            // �u���b�N�̏��
            switch (_pp_blockData[x][y].minoState)
            {
            case	TetriminoState::EMPTY:// ��
                _pp_blocks[x][y].SetColor({ 1.0f, 1.0f, 1.0f, 0.4f });
                break;
                //case	TetriminoState::LANDED:// ���n���Ă���e�g���~�m
                //	_pp_blocks[x][y].SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
                //	break;
                //case	TetriminoState::FALLING:// �����Ă��Ă���e�g���~�m
                //	_pp_blocks[x][y].SetColor({ 1.0f, 0.8f, 0.8f, 1.0f });
                //	break;
            case	TetriminoState::COMPLETE:// �������e�g���~�m
                _pp_blocks[x][y].SetColor({ 0.4f, 0.4f, 1.0f, 1.0f });
                break;
            case	TetriminoState::GAMEOVER:// �Q�[���I�[�o�[��
                _pp_blocks[x][y].SetColor({ 1.0f, 2.0f, 2.0f, 1.0f });
                break;
            default:
                break;
            }
        }
    }
}

/**	@brief 	Next�u���b�N�̐F��ݒ肷����
*	@param		TetriminoShape* _p_nextBlocksShape	Next�u���b�N�̌`
*	@param		Object** _pp_NextBlocks				Next�u���b�N
*	@date	2024/09/19
*/
void	SetNextBlockColor(TetriminoShape** _pp_nextBlocksShape, Object** _pp_NextBlocks)
{
    // �F��t����
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < STAGE_Y; y++)
        {
            switch (_pp_nextBlocksShape[x][y])
            {
                // ���F
            case I_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.0f, 0.8f, 0.9f, 1.0f });
                break;
                // ���F
            case O_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.9f, 0.7f, 0.0f, 1.0f });
                break;
                // �ΐF
            case S_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.0f, 0.9f, 0.0f, 1.0f });
                break;
                // �ԐF
            case Z_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.9f, 0.0f, 0.0f, 1.0f });
                break;
                // �F
            case J_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.1f, 0.3f, 0.9f, 1.0f });
                break;
                // ��F
            case L_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.9f, 0.4f, 0.0f, 1.0f });
                break;
                // ���F
            case T_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.7f, 0.3f, 0.8f, 1.0f });
                break;
                // ���݂��Ȃ�(����)
            case SHAPE_NULL:
                _pp_NextBlocks[x][y].SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });
                //break;
            default:
                _pp_NextBlocks[x][y].SetColor({ 1.0f, 1.0f, 1.0f, 0.2f });
                break;
            }
        }
    }
}

/**	@brief 	�Q�[���I�[�o�[���ǂ����m�F����֐�
*	@param		BlockStatus** _pp_blockData			�u���b�N�̃f�[�^�z��
*	@param		TetriminoState& gameState			���݂̃Q�[���̏��
*	@date	2024/09/15
*/
void	CheckGameover(BlockStatus** _pp_blockData, TetriminoState& _gameState)
{
    // �Q�[���I�[�o�[��Ԃ��ǂ����`�F�b�N
    for (int x = 0; x < STAGE_X; x++)
    {
        // 1�ԏ�̗񂪑����Ă�����
        if (_pp_blockData[x][STAGE_Y - 1].minoState == TetriminoState::LANDED)
        {
            // �e�g���~�m�̐F��ύX
            for (int tx = 0; tx < STAGE_X; tx++)
            {
                for (int ty = 0; ty < STAGE_Y + 3; ty++)
                {
                    // �����u���Ȃ��ӏ��̃u���b�N��
                    if (_pp_blockData[tx][ty].minoState == TetriminoState::LANDED)
                    {
                        // �Q�[���I�[�o�[��ԂɕύX
                        _pp_blockData[tx][ty].minoState = TetriminoState::GAMEOVER;
                    }
                }
            }
            // �Q�[����Ԃ��Q�[���I�[�o�[�ɕύX
            _gameState = TetriminoState::GAMEOVER;
            break;
        }
    }
}

/**	@brief 	�������u���b�N�������֐�
*	@param		BlockStatus** _pp_blockData			�u���b�N�̃f�[�^�z��
*	@param		TetriminoState& _gameState			���݂̃Q�[���̏��
*   @return     int completeNum                     ��������
*	@date	2024/09/15
*/
int	DeleteCompleteBlocks(BlockStatus** _pp_blockData, TetriminoState& _gameState)
{
    // 1�񑵂����s��T��
    int completeNum = 0;
    for (int y = 0; y < STAGE_Y + 3; y++)
    {
        if (_pp_blockData[0][y].minoState == TetriminoState::COMPLETE)
        {
            // ���̍s���΂��ăf�[�^�Ɋi�[
            for (int ty = y + 1; ty < STAGE_Y + 3; ty++)
            {
                for (int tx = 0; tx < STAGE_X; tx++)
                {
                    _pp_blockData[tx][ty - 1] = _pp_blockData[tx][ty];
                }
            }
            y--;    // �X�V��̍s�����邽�߂ɔ�΂���1�s�������Ă���
            completeNum++;
        }
    }
    _gameState = TetriminoState::EMPTY;     // ���Ƃ���e�g���~�m�����݂��Ȃ�
    return  completeNum;                    // �������񐔂�������
}

/**	@brief	�u���b�N�������Ă��邩�m�F
*	@param		BlockStatus** _pp_blockData			�u���b�N�̃f�[�^�z��
*	@param		TetriminoState& _gameState			���݂̃Q�[���̏��
*	@date	2024/09/15
*/
void	CheckCompleteBlocks(BlockStatus** _pp_blockData, TetriminoState& _gameState)
{
    for (int y = 0; y < STAGE_Y + 3; y++)
    {
        // 1�񂲂ƂɌ���
        bool isCompleted = true;
        for (int x = 0; x < STAGE_X; x++)
        {
            // �����Ă��Ȃ����
            if (_pp_blockData[x][y].minoState == TetriminoState::EMPTY)
            {
                isCompleted = false;
                break;
            }
        }

        // �����Ă����̃~�m��Ԃ�ύX
        if (isCompleted)
        {
            for (int x = 0; x < STAGE_X; x++)
            {
                _pp_blockData[x][y].minoState = TetriminoState::COMPLETE;
            }
            _gameState = TetriminoState::COMPLETE;     // �e�g���~�m��1�񑵂���
        }
    }
}

/**	@brief	�X�R�A�̕`��
*	@param		unsigned int& _score					�X�R�A
*	@param		BackGround&	_p_scoreBoard	�X�R�A�\���p�I�u�W�F�N�g
*	@date	2024/09/15
*/
void	DrawScore(unsigned int& _score, BackGround& _p_scoreBoard)
{
    DirectX::XMFLOAT3 pos = _p_scoreBoard.GetPos();
    DirectX::XMFLOAT3 size = _p_scoreBoard.GetSize();

    int digit = 0;
    do
    {
        // 1����؂�o��
        float numU = _score % (int)std::pow(10, digit + 1) / (int)std::pow(10, digit);

        // �ʒu�Ɛ��l��ݒ�
        _p_scoreBoard.SetTextureNumU(numU);
        _p_scoreBoard.SetPos(pos.x - size.x * digit, pos.y, pos.z);
        
        // �X�R�A��`��
        _p_scoreBoard.Update({ 0.0f ,0.0f ,0.0f });
        _p_scoreBoard.Draw(sizeof(Vertex));
        digit++;

    } while (_score >= (int)std::pow(10, digit));

    // �ʒu�����ɖ߂�
    _p_scoreBoard.SetPos(pos.x, pos.y, pos.z);
}

///**	@brief	�e�g���~�m����]������֐�
//*	@param	int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4]		�e�g���~�m�̌`��f�[�^4�����z��
//*	@param		BlockStatus** _pp_blockData			�u���b�N�̃f�[�^�z��
//*	@param	TetriminoStatus& _currentTetrimino		���݂̃~�m�̃X�e�[�^�X
//*	@date	2024/09/15
//*/
//void RotateTetrimino(int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4], BlockStatus** _pp_blockData, TetriminoStatus& _currentTetrimino)
//{
//    // ��������S�ĂȂ���
//    for (int x = 0; x < STAGE_X; x++)
//    {
//        for (int y = 0; y < STAGE_Y + 3; y++)
//        {
//            if (_pp_blockData[x][y].minoState == TetriminoState::FALLING)
//            {
//                _pp_blockData[x][y].minoState = TetriminoState::EMPTY;
//                _pp_blockData[x][y].minoShape = TetriminoShape::SHAPE_NULL;
//            }
//        }
//    }
//    // ��]��̃f�[�^����������
//    for (int tx = 0; tx < 4; tx++)
//    {
//        for (int ty = 0; ty < 4; ty++)
//        {
//            if (_tetriminoData[_currentTetrimino.type][tempDirc][ty][tx] == TetriminoState::FALLING)
//            {
//                _pp_blockData[baseX + tx][baseY + ty].minoState = TetriminoState::FALLING;         // ��ԍX�V
//                _pp_blockData[baseX + tx][baseY + ty].minoShape = _currentTetrimino.type;       // �F�X�V
//            }
//        }
//    }
//    // �������X�V����
//    this->p_currentMino->direction = (TetriminoDirection)tempDirc;
//
//}