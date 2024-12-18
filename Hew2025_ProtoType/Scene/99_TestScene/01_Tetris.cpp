#include"01_Tetris.h"

/**	@brief 	テトリミノの生成を行う関数
*	@param	BlockStatus**	_pp_blockData		テトリミノの状態が格納された配列
*	@param	std::vector<int>& _tetriminoList	落とすテトリミノのリスト
*	@param	int& _currentArray	今何番目のミノを落とすのか
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
    
    // 要素を進める
    if (_currentArray == TetriminoShape::SHAPE_MAX * 2 - 1) { _currentArray = 0; }
    else { _currentArray++; }

    // 1順目が終わったとき1順目を並べ替え直す
    if (_currentArray == TetriminoShape::SHAPE_MAX)
    { 
         for (int i = 0; i < TetriminoShape::SHAPE_MAX; i++)
        {
            int j = rand() % (i + 1);
            std::swap(_tetriminoList[i], _tetriminoList[j]);
        }
    } 
    // 2順目が終わったとき2順目を並べ替え直す
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

/**	@brief 	Nextブロックの生成を行う関数
*	@param	TetriminoShape**	_pp_nextBlockData		Nextの形状が格納された配列
*	@param	std::vector<int>& _tetriminoList	落とすテトリミノのリスト
*	@param	int& _nextBlockArray	どのnextを表示させるのか
*	@date	2024/09/19
*/
void	CreateNextTetrimino(TetriminoShape** _pp_nextBlockData, std::vector<int>& _tetriminoList, int& _nextBlockArray)
{
    // 一度表示をリセットする
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < STAGE_Y; y++)
        {
            _pp_nextBlockData[x][y] = TetriminoShape::SHAPE_NULL;
        }
    }

    // 指定個数表示させる
    for (int i = 0; i < 1; i++)
    {
        TetriminoShape shape = (TetriminoShape)_tetriminoList[_nextBlockArray + i];
        int nextY = i * 4;  // 表示を始める位置

        // ブロックの表示
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

/**	@brief 	テトリミノが落ちたか調べる関数
*	@param	BlockStatus** _pp_blockData	テトリミノの状態が格納された配列
*	@return	bool	isFall	true:落ちた
*	@date	2024/06/27
*/
bool	GetTetriminoIsFall(BlockStatus** _pp_blockData)
{
    // 落とせるか調べる
    bool    isFall = true;  //true:落ちる
    for (int x = 0; x < STAGE_X; x++)
    {
        for (int y = 0; y < STAGE_Y + 3; y++)
        {
            //落とせるブロック && ( 一番下にある || 1マス下にブロックがある )
            if (_pp_blockData[x][y].minoState == TetriminoState::FALLING && (y == TetriminoState::EMPTY || _pp_blockData[x][y - 1].minoState == TetriminoState::LANDED))
            {
                isFall = false;             // 落ちない
                break;
            }
        }
        if (!isFall) { break; }
    }
    return  isFall;
}

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
bool	GetTetriminoIsRotate(int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4], BlockStatus** _pp_data, TetriminoStatus	_currentStatus, int  _newDirc, int	_baseX, int	_baseY)
{
    bool    isRotate = true;
    for (int tx = 0; tx < 4; tx++)
    {
        for (int ty = 0; ty < 4; ty++)
        {
            if (_tetriminoData[_currentStatus.type][_newDirc][ty][tx] == TetriminoState::FALLING &&
                // ステージからはみ出るとき
                (   _baseX + tx > STAGE_X - 1 ||                                                  
                    _baseY + ty > STAGE_Y - 1 ||
                    _baseX + tx < 0 ||
                    _baseY + ty < 0 ||
                    _pp_data[_baseX + tx][_baseY + ty].minoState == TetriminoState::LANDED       // 既にブロックがある
                )
            )
            {
                isRotate = false;  // 回転できない
                break;
            }
        }
        if (!isRotate) { break; }
    }
    return  isRotate;
}

/**	@brief 	テトリミノを着地させる関数
*	@param	BlockStatus** _pp_blockData	テトリミノの状態が格納された配列
*	@param	TetriminoStatus _currentStatus
*	@date	2024/06/27
*/
void	LandTetrimino(BlockStatus** _pp_blockData, TetriminoStatus _currentStatus)
{
    //着地後に変更
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

/**	@brief 	テトリミノを落下させる関数
*	@param	BlockStatus** _pp_blockData	テトリミノの状態が格納された配列
*	@date	2024/06/27
*/
void	FallTetrimino(BlockStatus** _pp_blockData)
{
    // 一時的に更新情報を移す
    BlockStatus temp[STAGE_X][STAGE_Y + 3] = {};
    for (int x = 0; x < STAGE_X; x++)
    {
        for (int y = 0; y < STAGE_Y + 3; y++)
        {
            // 落下中のオブジェクトを1段下げる
            if (_pp_blockData[x][y].minoState == TetriminoState::FALLING)
            {
                temp[x][y - 1].minoState = TetriminoState::FALLING;
                temp[x][y - 1].minoShape = _pp_blockData[x][y].minoShape;
            }
            // それ以外もコピー
            else if (_pp_blockData[x][y].minoState == TetriminoState::LANDED)
            {
                temp[x][y].minoState = TetriminoState::LANDED;
                temp[x][y].minoShape = _pp_blockData[x][y].minoShape;
            }
        }
    }
    // 更新情報を元データにコピー
    for (int x = 0; x < STAGE_X; x++)
    {
        for (int y = 0; y < STAGE_Y + 3; y++)
        {
            _pp_blockData[x][y].minoState = temp[x][y].minoState;
            _pp_blockData[x][y].minoShape = temp[x][y].minoShape;
        }
    }
}

/**	@brief 	各ブロックの色を設定する作業
*	@param		BlockStatus** _pp_blockData			ブロックのデータ配列
*	@param		Object** _pp_blocks					ブロック
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

    // 色を付ける
    for (int x = 0; x < STAGE_X; x++)
    {
        for (int y = 0; y < STAGE_Y; y++)
        {
            // ブロック自体の色
            switch (_pp_blockData[x][y].minoShape)
            {
                // 水色
            case I_MINO:
                _pp_blocks[x][y].SetColor({ 0.0f, 0.8f, 0.9f, 1.0f });
                break;
                // 黄色
            case O_MINO:
                _pp_blocks[x][y].SetColor({ 0.9f, 0.7f, 0.0f, 1.0f });
                break;
                // 緑色
            case S_MINO:
                _pp_blocks[x][y].SetColor({ 0.0f, 0.9f, 0.0f, 1.0f });
                break;
                // 赤色
            case Z_MINO:
                _pp_blocks[x][y].SetColor({ 0.9f, 0.0f, 0.0f, 1.0f });
                break;
                // 青色
            case J_MINO:
                _pp_blocks[x][y].SetColor({ 0.1f, 0.3f, 0.9f, 1.0f });
                break;
                // 橙色
            case L_MINO:
                _pp_blocks[x][y].SetColor({ 0.9f, 0.4f, 0.0f, 1.0f });
                break;
                // 紫色
            case T_MINO:
                _pp_blocks[x][y].SetColor({ 0.7f, 0.3f, 0.8f, 1.0f });
                break;
            default:
                _pp_blocks[x][y].SetColor({ 1.0f, 1.0f, 1.0f, 0.2f });
                break;
            }

            // ブロックの状態
            switch (_pp_blockData[x][y].minoState)
            {
            case	TetriminoState::EMPTY:// 空白
                _pp_blocks[x][y].SetColor({ 1.0f, 1.0f, 1.0f, 0.4f });
                break;
                //case	TetriminoState::LANDED:// 着地しているテトリミノ
                //	_pp_blocks[x][y].SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
                //	break;
                //case	TetriminoState::FALLING:// 落ちてきているテトリミノ
                //	_pp_blocks[x][y].SetColor({ 1.0f, 0.8f, 0.8f, 1.0f });
                //	break;
            case	TetriminoState::COMPLETE:// 揃ったテトリミノ
                _pp_blocks[x][y].SetColor({ 0.4f, 0.4f, 1.0f, 1.0f });
                break;
            case	TetriminoState::GAMEOVER:// ゲームオーバー時
                _pp_blocks[x][y].SetColor({ 1.0f, 2.0f, 2.0f, 1.0f });
                break;
            default:
                break;
            }
        }
    }
}

/**	@brief 	Nextブロックの色を設定する作業
*	@param		TetriminoShape* _p_nextBlocksShape	Nextブロックの形
*	@param		Object** _pp_NextBlocks				Nextブロック
*	@date	2024/09/19
*/
void	SetNextBlockColor(TetriminoShape** _pp_nextBlocksShape, Object** _pp_NextBlocks)
{
    // 色を付ける
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < STAGE_Y; y++)
        {
            switch (_pp_nextBlocksShape[x][y])
            {
                // 水色
            case I_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.0f, 0.8f, 0.9f, 1.0f });
                break;
                // 黄色
            case O_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.9f, 0.7f, 0.0f, 1.0f });
                break;
                // 緑色
            case S_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.0f, 0.9f, 0.0f, 1.0f });
                break;
                // 赤色
            case Z_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.9f, 0.0f, 0.0f, 1.0f });
                break;
                // 青色
            case J_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.1f, 0.3f, 0.9f, 1.0f });
                break;
                // 橙色
            case L_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.9f, 0.4f, 0.0f, 1.0f });
                break;
                // 紫色
            case T_MINO:
                _pp_NextBlocks[x][y].SetColor({ 0.7f, 0.3f, 0.8f, 1.0f });
                break;
                // 存在しない(透明)
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

/**	@brief 	ゲームオーバーかどうか確認する関数
*	@param		BlockStatus** _pp_blockData			ブロックのデータ配列
*	@param		TetriminoState& gameState			現在のゲームの状態
*	@date	2024/09/15
*/
void	CheckGameover(BlockStatus** _pp_blockData, TetriminoState& _gameState)
{
    // ゲームオーバー状態かどうかチェック
    for (int x = 0; x < STAGE_X; x++)
    {
        // 1番上の列が揃っていたら
        if (_pp_blockData[x][STAGE_Y - 1].minoState == TetriminoState::LANDED)
        {
            // テトリミノの色を変更
            for (int tx = 0; tx < STAGE_X; tx++)
            {
                for (int ty = 0; ty < STAGE_Y + 3; ty++)
                {
                    // もう置けない箇所のブロックを
                    if (_pp_blockData[tx][ty].minoState == TetriminoState::LANDED)
                    {
                        // ゲームオーバー状態に変更
                        _pp_blockData[tx][ty].minoState = TetriminoState::GAMEOVER;
                    }
                }
            }
            // ゲーム状態をゲームオーバーに変更
            _gameState = TetriminoState::GAMEOVER;
            break;
        }
    }
}

/**	@brief 	揃ったブロックを消す関数
*	@param		BlockStatus** _pp_blockData			ブロックのデータ配列
*	@param		TetriminoState& _gameState			現在のゲームの状態
*   @return     int completeNum                     揃った列数
*	@date	2024/09/15
*/
int	DeleteCompleteBlocks(BlockStatus** _pp_blockData, TetriminoState& _gameState)
{
    // 1列揃った行を探す
    int completeNum = 0;
    for (int y = 0; y < STAGE_Y + 3; y++)
    {
        if (_pp_blockData[0][y].minoState == TetriminoState::COMPLETE)
        {
            // その行を飛ばしてデータに格納
            for (int ty = y + 1; ty < STAGE_Y + 3; ty++)
            {
                for (int tx = 0; tx < STAGE_X; tx++)
                {
                    _pp_blockData[tx][ty - 1] = _pp_blockData[tx][ty];
                }
            }
            y--;    // 更新後の行を見るために飛ばした1行分引いておく
            completeNum++;
        }
    }
    _gameState = TetriminoState::EMPTY;     // 落とせるテトリミノが存在しない
    return  completeNum;                    // 揃えた列数をかえす
}

/**	@brief	ブロックが揃っているか確認
*	@param		BlockStatus** _pp_blockData			ブロックのデータ配列
*	@param		TetriminoState& _gameState			現在のゲームの状態
*	@date	2024/09/15
*/
void	CheckCompleteBlocks(BlockStatus** _pp_blockData, TetriminoState& _gameState)
{
    for (int y = 0; y < STAGE_Y + 3; y++)
    {
        // 1列ごとに見る
        bool isCompleted = true;
        for (int x = 0; x < STAGE_X; x++)
        {
            // 揃っていなければ
            if (_pp_blockData[x][y].minoState == TetriminoState::EMPTY)
            {
                isCompleted = false;
                break;
            }
        }

        // 揃っている列のミノ状態を変更
        if (isCompleted)
        {
            for (int x = 0; x < STAGE_X; x++)
            {
                _pp_blockData[x][y].minoState = TetriminoState::COMPLETE;
            }
            _gameState = TetriminoState::COMPLETE;     // テトリミノが1列揃った
        }
    }
}

/**	@brief	スコアの描画
*	@param		unsigned int& _score					スコア
*	@param		BackGround&	_p_scoreBoard	スコア表示用オブジェクト
*	@date	2024/09/15
*/
void	DrawScore(unsigned int& _score, BackGround& _p_scoreBoard)
{
    DirectX::XMFLOAT3 pos = _p_scoreBoard.GetPos();
    DirectX::XMFLOAT3 size = _p_scoreBoard.GetSize();

    int digit = 0;
    do
    {
        // 1桁を切り出す
        float numU = _score % (int)std::pow(10, digit + 1) / (int)std::pow(10, digit);

        // 位置と数値を設定
        _p_scoreBoard.SetTextureNumU(numU);
        _p_scoreBoard.SetPos(pos.x - size.x * digit, pos.y, pos.z);
        
        // スコアを描画
        _p_scoreBoard.Update({ 0.0f ,0.0f ,0.0f });
        _p_scoreBoard.Draw(sizeof(Vertex));
        digit++;

    } while (_score >= (int)std::pow(10, digit));

    // 位置を元に戻す
    _p_scoreBoard.SetPos(pos.x, pos.y, pos.z);
}

///**	@brief	テトリミノを回転させる関数
//*	@param	int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4]		テトリミノの形状データ4次元配列
//*	@param		BlockStatus** _pp_blockData			ブロックのデータ配列
//*	@param	TetriminoStatus& _currentTetrimino		現在のミノのステータス
//*	@date	2024/09/15
//*/
//void RotateTetrimino(int _tetriminoData[TetriminoShape::SHAPE_MAX][TetriminoDirection::Direction_MAX][4][4], BlockStatus** _pp_blockData, TetriminoStatus& _currentTetrimino)
//{
//    // 落下中を全てなくす
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
//    // 回転後のデータを書き込む
//    for (int tx = 0; tx < 4; tx++)
//    {
//        for (int ty = 0; ty < 4; ty++)
//        {
//            if (_tetriminoData[_currentTetrimino.type][tempDirc][ty][tx] == TetriminoState::FALLING)
//            {
//                _pp_blockData[baseX + tx][baseY + ty].minoState = TetriminoState::FALLING;         // 状態更新
//                _pp_blockData[baseX + tx][baseY + ty].minoShape = _currentTetrimino.type;       // 色更新
//            }
//        }
//    }
//    // 向きを更新する
//    this->p_currentMino->direction = (TetriminoDirection)tempDirc;
//
//}
