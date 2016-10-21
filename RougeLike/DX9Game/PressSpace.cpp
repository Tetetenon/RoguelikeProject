#include "PressSpace.h"
#include "TextureManager.h"

//�_�Ŏ���
#define FLASHTIME 30

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CPressSpace::CPressSpace(void)
{
	//�g�p����e�N�X�`��ID�̐ݒ�
	m_nTextureID = TEXTURE_PRESS_SPACE;

	//�`��t���O�̏�����
	m_bAlphaSwitch = true;

	//�`�掞�Ԃ̏�����
	m_nFlashTimer = 0;
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CPressSpace::~CPressSpace(void)
{
}


//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CPressSpace::Update()
{
	//�e�N�X�`���̃A���t�@�l���t���O�̏�Ԃ���A���Z���Z����
	if(m_bAlphaSwitch)
	{
		//���݂̓_�Ŏ��Ԃ����Z
		m_nFlashTimer += 3;

		//���E�l����
		if(m_nFlashTimer >= 255)
			m_nFlashTimer = 255;
	}
	else
	{
		m_nFlashTimer -= 3;

		//���E�l����
		if(m_nFlashTimer <= 0)
			m_nFlashTimer = 0;
	}

	//���_�J���[�̐ݒ�
	m_aVertex[0].col = D3DCOLOR_RGBA(255,255,255,m_nFlashTimer);
	m_aVertex[1].col = D3DCOLOR_RGBA(255,255,255,m_nFlashTimer);
	m_aVertex[2].col = D3DCOLOR_RGBA(255,255,255,m_nFlashTimer);
	m_aVertex[3].col = D3DCOLOR_RGBA(255,255,255,m_nFlashTimer);

	//���E�l�ɂȂ����ꍇ�A�t���O�𔽓]
	if(m_nFlashTimer >= 255 || m_nFlashTimer <= 0)
	{
		//�t���O�𔽓]�����A���E�l�𒴂��Ȃ��悤�ɂ���
		m_bAlphaSwitch = !m_bAlphaSwitch;
	}
}