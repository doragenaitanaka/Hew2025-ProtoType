#pragma once
//D3D�������ɕK�v�Ȃ�
#pragma comment(lib,"d3d11.lib")
#include <d3d11_1.h>

class CD3D11_Device
{
public:
	/**	@brief 	�R���X�g���N�^
	*	@date 2024/03/29
	*/
	CD3D11_Device();
	/**	@brief 	�f�X�g���N�^
	*	@date 2024/03/29
	*/
	~CD3D11_Device();
	/**	@brief 	�O���t�B�b�N�f�o�C�X�̏�����
	*	@return HRESULT
	*	@date 2024/03/29
	*/
	HRESULT    Create(void);
	/**	@brief 	�������
	*	@date 2024/03/29
	*/
	void    Release();
public:
	ID3D11Device* m_pDevice;                        //Direct3D�f�o�C�X
	ID3D11DeviceContext* m_pImmediateContext;       //�f�o�C�X�R���e�L�X�g
};
