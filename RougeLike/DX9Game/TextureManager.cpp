#include "TextureManager.h"
#include "Graphics.h"

#include <tchar.h>


LPDIRECT3DTEXTURE9	CTextureManager::m_TextureData[TEXTURE_MAX];			//�e�N�X�`���f�[�^�i�[�p
bool				CTextureManager::m_TextureLoad[TEXTURE_MAX] = {false};	//�e�N�X�`���ǂݍ��݃t���O


//�g�p�e�N�X�`��
#define TEXTURE_PATH_WINDOW			_T("../data/texture/Window.png")		//�E�B���h�E
#define TEXTURE_PATH_WINDOW_ALPHA	_T("../data/texture/Window_A.png")		//�������E�B���h�E
#define TEXTURE_PATH_SELECT_WINDOW	_T("../data/texture/Window2.png")		//�I�𒆃E�B���h�E
#define TEXTURE_PATH_FLOOR			_T("../data/Texture/Floor.png")			//��
#define TEXTURE_PATH_WALL			_T("../data/Texture/Wall.png")			//�J�x

#define TEXTURE_PATH_TITLE			_T("../data/texture/Title.png")			//�^�C�g��
#define TEXTURE_PATH_RESULT			_T("../data/texture/Result.png")		//���U���g
#define TEXTURE_PATH_GAMECLEAR		_T("../data/texture/GameClear.png")		//�Q�[���N���A

#define TEXTURE_PATH_PRESS_SPACE	_T("../data/texture/PressSpace.png")	//�v���X�X�y�[�X
#define TEXTURE_PATH_CIRCLE_P		_T("../data/texture/Circle_P.png")		//�v���C���[���j�b�g�T�[�N��
#define TEXTURE_PATH_CIRCLE_E		_T("../data/texture/Circle_E.png")		//�G�l�~�[���j�b�g�T�[�N��
#define TEXTURE_PATH_CIRCLE_F		_T("../data/texture/Circle_F.png")		//�F�R���j�b�g�T�[�N��
#define TEXTURE_PATH_CIRCLE_I		_T("../data/texture/Circle_I.png")		//�A�C�e���T�[�N��
#define TEXTURE_PATH_MENIUWINDOW	_T("../data/texture/Menu_Window.png")	//���j���[�E�B���h�E
#define TEXTURE_PATH_OPERATION		_T("../data/texture/Operation.png")		//��������e�N�X�`��
#define TEXTURE_PATH_RED_TEXTURE	_T("../data/texture/RedTexture.png")	//�ԐF�e�N�X�`��
#define TEXTURE_PATH_WHITE_TEXTURE	_T("../data/texture/WhiteTexture.png")	//���F�e�N�X�`��

#define TEXTURE_PATH_HP				_T("../data/texture/GreenTexture.png")	//�ΐF�e�N�X�`��
#define TEXTURE_PATH_PURPLE_TEXTURE	_T("../data/texture/PurpleTexture.png")	//���F�e�N�X�`��
#define TEXTURE_PATH_BLUE_TEXTURE	_T("../data/texture/BlueTexture.png")	//�F�e�N�X�`��
#define TEXTURE_PATH_ORANGE_TEXTURE	_T("../data/texture/OrangeTexture.png")	//��F�e�N�X�`��

#define TEXTURE_PATH_PARTICLE		_T("../data/texture/ParticleWhite.png")	//�p�[�e�B�N���e�N�X�`���P
#define TEXTURE_PATH_PARTICLE2		_T("../data/texture/flare07.bmp")		//�p�[�e�B�N���e�N�X�`���Q
#define TEXTURE_PATH_LEVELUP		_T("../data/texture/LevelUp.png")		//�p�[�e�B�N���e�N�X�`���Q

#define TEXTURE_PATH_RED_HOOD		_T("../data/texture/RedHood.png")		//�X�e�[�^�X��ʗp�Ԃ�����
#define TEXTURE_PATH_RED_HOOD_PO	_T("../data/texture/Poison.png")		//�X�e�[�^�X�p�ŏ��
#define TEXTURE_PATH_RED_HOOD_PA	_T("../data/texture/Paralysis.png")		//�X�e�[�^�X�p���
#define TEXTURE_PATH_RED_HOOD_SL	_T("../data/texture/Sleep.png")			//�X�e�[�^�X�p����
#define TEXTURE_PATH_RED_HOOD_CO	_T("../data/texture/Confusion.png")		//�X�e�[�^�X�p����
#define TEXTURE_PATH_ATTACK			_T("../data/texture/Attack.png")		//�X�e�[�^�X�p�U���̓e�N�X�`��
#define TEXTURE_PATH_DEFENCE		_T("../data/texture/Defence.png")		//�X�e�[�^�X�p�h��̓e�N�X�`��
#define TEXTURE_PATH_EXP			_T("../data/texture/Exp.png")			//�X�e�[�^�X�p�o���l�e�N�X�`��


//-----����-----
#define TEXTURE_PATH_0	_T("../data/texture/0.png")							//�����e�N�X�`��
#define TEXTURE_PATH_1	_T("../data/texture/1.png")							//�����e�N�X�`��
#define TEXTURE_PATH_2	_T("../data/texture/2.png")							//�����e�N�X�`��
#define TEXTURE_PATH_3	_T("../data/texture/3.png")							//�����e�N�X�`��
#define TEXTURE_PATH_4	_T("../data/texture/4.png")							//�����e�N�X�`��
#define TEXTURE_PATH_5	_T("../data/texture/5.png")							//�����e�N�X�`��
#define TEXTURE_PATH_6	_T("../data/texture/6.png")							//�����e�N�X�`��
#define TEXTURE_PATH_7	_T("../data/texture/7.png")							//�����e�N�X�`��
#define TEXTURE_PATH_8	_T("../data/texture/8.png")							//�����e�N�X�`��
#define TEXTURE_PATH_9	_T("../data/texture/9.png")							//�����e�N�X�`��

//-----�A���t�@�x�b�g-----
#define TEXTURE_PATH_F	_T("../data/texture/F.png")							//�A���t�@�x�b�g�e�N�X�`��


//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CTextureManager::CTextureManager(void)
{
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CTextureManager::~CTextureManager(void)
{
}


//---------------------------------------------------------------------------------------
//�e�N�X�`���f�[�^�̓ǂݍ���
//---------------------------------------------------------------------------------------
void CTextureManager::LoadTexture()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//���f���f�[�^�̏�����
	ReleaseTexture();

	
	//�E�C���h�E
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_WINDOW])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_WINDOW,&m_TextureData[TEXTURE_WINDOW]);
	}

	//�E�C���h�E(������)
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_WINDOW_ALPHA])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_WINDOW_ALPHA,&m_TextureData[TEXTURE_WINDOW_ALPHA]);
	}

	//�Z���N�g�E�C���h�E
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_SELECT_WINDOW])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_SELECT_WINDOW,&m_TextureData[TEXTURE_SELECT_WINDOW]);
	}

	//��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_FLOOR])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_FLOOR,&m_TextureData[TEXTURE_FLOOR]);
	}

	//��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_WALL])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_WALL,&m_TextureData[TEXTURE_WALL]);
	}

	//�^�C�g��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_TITLE])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_TITLE,&m_TextureData[TEXTURE_TITLE]);
	}

	//���U���g
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_RESULT])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RESULT,&m_TextureData[TEXTURE_RESULT]);
	}

	//�Q�[���N���A
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_GAMECLEAR])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_GAMECLEAR,&m_TextureData[TEXTURE_GAMECLEAR]);
	}

	//�v���X�X�y�[�X
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_PRESS_SPACE])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_PRESS_SPACE,&m_TextureData[TEXTURE_PRESS_SPACE]);
	}

	//�v���C���[�T�[�N��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_CIRCLE_P])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_CIRCLE_P,&m_TextureData[TEXTURE_CIRCLE_P]);
	}

	//�G�l�~�[�T�[�N��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_CIRCLE_E])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_CIRCLE_E,&m_TextureData[TEXTURE_CIRCLE_E]);
	}

	//�F�R�T�[�N��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_CIRCLE_F])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_CIRCLE_F,&m_TextureData[TEXTURE_CIRCLE_F]);
	}
	
	//�A�C�e���T�[�N��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_CIRCLE_I])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_CIRCLE_I,&m_TextureData[TEXTURE_CIRCLE_I]);
	}

	//���j���[�E�B���h�E
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_MENU_WINDOW])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_MENIUWINDOW,&m_TextureData[TEXTURE_MENU_WINDOW]);
	}

	//�������
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_OPERATION])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_OPERATION,&m_TextureData[TEXTURE_OPERATION]);
	}

	//�Ԃ��e�N�X�`��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_RED_TEXTURE])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RED_TEXTURE,&m_TextureData[TEXTURE_RED_TEXTURE]);
	}
	
	//�����e�N�X�`��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_WHITE_TEXTURE])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_WHITE_TEXTURE,&m_TextureData[TEXTURE_WHITE_TEXTURE]);
	}
	//���e�N�X�`��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_BLUE_TEXTURE])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_BLUE_TEXTURE,&m_TextureData[TEXTURE_BLUE_TEXTURE]);
	}
	//��e�N�X�`��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_ORANGE_TEXTURE])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_ORANGE_TEXTURE,&m_TextureData[TEXTURE_ORANGE_TEXTURE]);
	}
	//���e�N�X�`��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_PURPLE_TEXTURE])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_PURPLE_TEXTURE,&m_TextureData[TEXTURE_PURPLE_TEXTURE]);
	}

	//�p�[�e�B�N���e�N�X�`��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_PARTICLE1])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_PARTICLE,&m_TextureData[TEXTURE_PARTICLE1]);
	}

	//�p�[�e�B�N���e�N�X�`���Q
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_PARTICLE2])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_PARTICLE2,&m_TextureData[TEXTURE_PARTICLE2]);
	}

	//���x���A�b�v�e�N�X�`��
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_LEVELUP])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_LEVELUP,&m_TextureData[TEXTURE_LEVELUP]);
	}

	//�Ԃ�����
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_RED_HOOD])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RED_HOOD,&m_TextureData[TEXTURE_RED_HOOD]);
	}

	//�Ԃ�����(��)
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_RED_HOOD_POISON])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RED_HOOD_PO,&m_TextureData[TEXTURE_RED_HOOD_POISON]);
	}

	//�Ԃ�����(���)
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_RED_HOOD_PARALYSIS])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RED_HOOD_PA,&m_TextureData[TEXTURE_RED_HOOD_PARALYSIS]);
	}

	//�Ԃ�����(����)
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_RED_HOOD_SLEEP])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RED_HOOD_SL,&m_TextureData[TEXTURE_RED_HOOD_SLEEP]);
	}

	//�Ԃ�����(����)
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_RED_HOOD_CONFUSION])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_RED_HOOD_CO,&m_TextureData[TEXTURE_RED_HOOD_CONFUSION]);
	}

	//HP�o�[
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_HP_BAR])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_HP,&m_TextureData[TEXTURE_HP_BAR]);
	}

	//��������
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_ATTACK])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_ATTACK,&m_TextureData[TEXTURE_ATTACK]);
	}

	//�ڂ�����
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_DEFENCE])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_DEFENCE,&m_TextureData[TEXTURE_DEFENCE]);
	}

	//��������
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_EXP])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_EXP,&m_TextureData[TEXTURE_EXP]);
	}

	//���l
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_0])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_0,&m_TextureData[TEXTURE_0]);
	}

	//���l
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_1])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_1,&m_TextureData[TEXTURE_1]);
	}

	//���l
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_2])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_2,&m_TextureData[TEXTURE_2]);
	}

	//���l
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_3])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_3,&m_TextureData[TEXTURE_3]);
	}

	//���l
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_4])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_4,&m_TextureData[TEXTURE_4]);
	}

	//���l
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_5])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_5,&m_TextureData[TEXTURE_5]);
	}

	//���l
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_6])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_6,&m_TextureData[TEXTURE_6]);
	}

	//���l
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_7])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_7,&m_TextureData[TEXTURE_7]);
	}

	//���l
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_8])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_8,&m_TextureData[TEXTURE_8]);
	}

	//���l
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_9])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_9,&m_TextureData[TEXTURE_9]);
	}

	//�A���t�@�x�b�g
	//�e�N�X�`���̓ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if(!m_TextureLoad[TEXTURE_F])
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,TEXTURE_PATH_F,&m_TextureData[TEXTURE_F]);
	}
	
}

//---------------------------------------------------------------------------------------
//�S�Ẵ��b�V���f�[�^���폜����
//---------------------------------------------------------------------------------------
void CTextureManager::ReleaseTexture()
{
	//�e�N�X�`���f�[�^�����݂���΁A�폜���s��
	for(int i = 0;i < TEXTURE_MAX;i++)
	{
		//�e�N�X�`���f�[�^���ǂݍ��܂�Ă���
		if(m_TextureLoad[i])
		{
			//�e�N�X�`���̊J��
			SAFE_RELEASE(m_TextureData[i]);

			//�e�N�X�`���ǂݍ��݃t���O�|��
			m_TextureLoad[i] = false;
		}
	}
}
//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�e�N�X�`���f�[�^��n��
//---------------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9* CTextureManager::GetTexture(int nNumber)
{
	return &m_TextureData[nNumber];
}