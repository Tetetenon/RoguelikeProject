#include "Operation.h"
#include "TextureManager.h"


//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
COperation::COperation(void)
{
	//�g�p����e�N�X�`��ID�̐ݒ�
	m_nTextureID = TEXTURE_OPERATION;

	//�ʒu���̐ݒ�
	m_aVertex[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f , 365.0f ,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f , 365.0f ,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f ,SCREEN_HEIGHT - 5.0f ,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f ,SCREEN_HEIGHT - 5.0f ,0.0f);
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
COperation::~COperation(void)
{
}
