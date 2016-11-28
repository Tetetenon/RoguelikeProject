#include "Fade.h"
#include "TextureManager.h"

int		CFade::m_nFadeTime;		//�t�F�[�h�C���A�A�E�g�̎��Ԃ��i�[����
int		CFade::m_nFadeState;		//�t�F�[�h�A�E�g�A�t�F�[�h�C���A���Ȃ���ݒ肷��B

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CFade::CFade(void)
{
	//�`��t���O������
	m_nFadeState = FADEMODE_NON;

	//�`�掞�ԏ�����
	m_nFadeTime = 0;

	//�e�N�X�`���̐ݒ�
	m_nTextureID = TEXTURE_IN_THE_WALL;
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CFade::~CFade(void)
{
}

//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CFade::Update()
{
	//�����A�t�F�[�h�̏�Ԃ��������Ȃ��ꍇ�A�������I������
	if(m_nFadeState == FADEMODE_NON)
		return;

	//�t�F�[�h�̒l
	int nAlphaNum = 0;
	//���݂̃t�F�[�h��Ԃɉ����ď�����ύX
	switch(m_nFadeState)
	{
		//�t�F�[�h�C�����[�h
	case FADEMODE_IN:
		//�����A�`��c�莞�Ԃ��N�����Ă���ꍇ�A���̐������炷
		if(m_nFadeTime <= 255)
		{
			m_nFadeTime += (FADETIME / 80);
		}
		nAlphaNum = 255 - m_nFadeTime;
			break;
		//�t�F�[�h�A�E�g���[�h
	case FADEMODE_OUT:
		//�����A�`��c�莞�Ԃ��c���Ă���΁A���̎��Ԃ����炷
		if(m_nFadeTime <= 255)
		{
			m_nFadeTime += (FADETIME / 60);
		}
		nAlphaNum = m_nFadeTime;
		break;
	}
	//���_�J���[�̐ݒ�
	m_aVertex[0].col = D3DCOLOR_RGBA(255,255,255,nAlphaNum);
	m_aVertex[1].col = D3DCOLOR_RGBA(255,255,255,nAlphaNum);
	m_aVertex[2].col = D3DCOLOR_RGBA(255,255,255,nAlphaNum);
	m_aVertex[3].col = D3DCOLOR_RGBA(255,255,255,nAlphaNum);
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CFade::Draw(void)
{
	//�����A�t�F�[�h�̏�Ԃ��������Ȃ��ꍇ�A�������I������
	if(m_nFadeState == FADEMODE_NON)
		return;
	//�e�̕`����s��
	C2DTexture::Draw();
}

//---------------------------------------------------------------------------------------
//�t���O�𗧂Ă�
//---------------------------------------------------------------------------------------
void CFade::ChangeState(int ChangeState)
{
	//�t�F�[�h������悤�Ƀt���O�𗧂Ă�
	m_nFadeState = ChangeState;
	//�t�F�[�h�܂ł̎��Ԃ�ݒ肷��
	m_nFadeTime = 0;

}