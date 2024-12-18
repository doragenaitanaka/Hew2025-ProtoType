/**	@file 	Test_Imagawa.h
*	@brief 	����p�̃e�X�g�V�[���N���X
*	@date	2024/05/21
*	@memo	�}�l�[�W���[�͐ÓI�����o�ϐ��Ȃ̂Ŏ擾�̂�
*/
#pragma once

// �C���N���[�h
#include"../00_BaseScene/BaseScene.h"
#include"../../Library/Code/self/02_SceneManager/SceneManager.h"
#include"../../Library/Code/self/10_Object/Object.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/01_CVertexShader/CVertexShader.h"
#include"../../Library/Code/self/04_DirextX_11/09_Shader/02_PixelShader/CPixelShader.h"
#include"../../Library/Code/self/04_DirextX_11/10_Sampler/CSampler.h"
#include"../../Library/Code/self/04_DirextX_11/08_InputLayout/CInputLayout.h"
#include"../../Library/Code/self/imagawa_Input/input.h"
#include<iostream>



/**	@file	Test_Imagawa.h
*	@brief 	����p�̃e�X�g�V�[���N���X
*	@date	2024/05/21
*	@memo	���N���X�̏������z�֐����p�����Ă��闠�t��(������p�������h������)�Ɍp�����������o�֐���override�w��q���g�p���Ă���
*/
class Test_Imagawa :public BaseScene
{
public:

	/**	@brief 	�R���X�g���N�^
	*	* @date 2024/05/21
	*/
	Test_Imagawa();
	/**	@brief 	�f�X�g���N�^
	*	@date 2024/05/21
	*/
	~Test_Imagawa()override;
	/**	@brief 	�V�[���S�̂̏�����
	*	@date 2024/05/21
	*/
	void	Initialize(void)override;

	/**	@brief 	�V�[���S�̂̍X�V
	*	@date 2024/05/21
	*/
	void	Update(void)override;

	/**	@brief 	�V�[���S�̂̕`��
	*	@date 2024/05/21
	*/
	void	Draw(void)override;

	/**	@brief 	�V�[���S�̂̏I������
	*	@date 2024/05/21
	*/
	void	Finalize(void)override;

	/** @brief�@�U���̏ڍאݒ�@
	*   @memo�@flame�F�U�����钷���@
	*   @memo�@power�F�U���̋���
	*/
	int flame = 0;
	float power = 0;

private:
	Input input;
	Object* p_object;

	//--------------------------------------------------------------------------
	//		�`��֘A
	//--------------------------------------------------------------------------	
	CInputLayout* p_inputLayout;		//  ���̓��C�A�E�g
	CVertexShader* p_vertexShader;		//  ���_�V�F�[�_
	CPixelShader* p_pixelShader;		//  �s�N�Z���V�F�[�_
	CSampler* p_sampler;				// �T���v���[
	ID3D11BlendState* p_brendState;		// �A���t�@�u�����f�B���O�p�X�e�[�g
};