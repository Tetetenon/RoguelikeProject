#include "StatesCharacter.h"
#include "TextureManager.h"
#include "Unit.h"

//---------------------------------------------------------------------------------------
//�ÓI�����o�ϐ�
//---------------------------------------------------------------------------------------
CStatesCharacter* CStatesCharacter::m_pStatesCharacter = NULL;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CStatesCharacter::CStatesCharacter(void)
{
	//�g�p����e�N�X�`��ID�̐ݒ�
	m_nTextureID = TEXTURE_RED_HOOD;

	//�ʒu���̐ݒ�
	m_aVertex[0].pos = D3DXVECTOR3( 10.0f, 10.0f,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3( 90.0f, 10.0f,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3( 10.0f, 90.0f,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3( 90.0f, 90.0f,0.0f);
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CStatesCharacter::~CStatesCharacter(void)
{
}

//---------------------------------------------------------------------------------------
//���̂̐���
//---------------------------------------------------------------------------------------
void CStatesCharacter::Create()
{
	//���g�̊m�F
	if (!m_pStatesCharacter)
	{
		//���g���Ȃ���΍쐬
		m_pStatesCharacter = new CStatesCharacter;
	}
}
//---------------------------------------------------------------------------------------
//���̂̍폜
//---------------------------------------------------------------------------------------
void CStatesCharacter::Delete()
{
	//���g�̊m�F
	if (m_pStatesCharacter)
	{
		//���g������΍폜
		delete m_pStatesCharacter;
		m_pStatesCharacter = NULL;
	}
}
//---------------------------------------------------------------------------------------
//���̂̃|�C���^��n��
//---------------------------------------------------------------------------------------
CStatesCharacter* CStatesCharacter::GetPointer()
{
	//�O�̂��ߍ쐬
	Create();
	return m_pStatesCharacter;
}
//---------------------------------------------------------------------------------------
//�g�p����e�N�X�`������������
//---------------------------------------------------------------------------------------
void CStatesCharacter::ChangeTexture(int nState)
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
