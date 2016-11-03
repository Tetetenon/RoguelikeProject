#include "StatesCharacter.h"
#include "TextureManager.h"
#include "Unit.h"

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CStatesCharacter::CStatesCharacter(void)
{
	//�g�p����e�N�X�`��ID�̐ݒ�
	m_nTextureID = TEXTURE_RED_HOOD;

	//�ʒu���̐ݒ�
	m_aVertex[0].pos = D3DXVECTOR3( 10.0f, 50.0f,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(125.0f, 50.0f,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3( 10.0f,165.0f,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(125.0f,165.0f,0.0f);
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CStatesCharacter::~CStatesCharacter(void)
{
}

//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CStatesCharacter::Update(int nState)
{
	//���������ԃX�e�[�g�̒l�ɉ����A�e�N�X�`����ύX����
	switch(nState)
	{
		//���
	case UNIT_STATE_PARALYSIS:
		//�g�p����e�N�X�`��ID�̐ݒ�
		m_nTextureID = TEXTURE_RED_HOOD_PARALYSIS;
		break;
		//����
	case UNIT_STATE_CONFUSION:
		//�g�p����e�N�X�`��ID�̐ݒ�
		m_nTextureID = TEXTURE_RED_HOOD_CONFUSION;
		break;
		//��
	case UNIT_STATE_POISON:
		//�g�p����e�N�X�`��ID�̐ݒ�
		m_nTextureID = TEXTURE_RED_HOOD_POISON;
		break;
		//����
	case UNIT_STATE_SLEEP:
		//�g�p����e�N�X�`��ID�̐ݒ�
		m_nTextureID = TEXTURE_RED_HOOD_SLEEP;
		break;
	default:
		//�g�p����e�N�X�`��ID�̐ݒ�
		m_nTextureID = TEXTURE_RED_HOOD;
		break;
	}
}
