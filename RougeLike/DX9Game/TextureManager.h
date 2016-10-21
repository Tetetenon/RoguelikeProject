#pragma once

#include "define.h"

enum TEXTURENUM
{
	TEXTURE_WINDOW	= 0,		//�E�C���h�E
	TEXTURE_WINDOW_ALPHA,		//�E�B���h�E(������)
	TEXTURE_SELECT_WINDOW,		//�I�𒆃E�C���h�E
	TEXTURE_FLOOR,				//��
	TEXTURE_WALL,				//��
	TEXTURE_IN_THE_WALL,		//�ǂ̒�
	TEXTURE_TITLE,				//�^�C�g��
	TEXTURE_RESULT,				//���U���g
	TEXTURE_PRESS_SPACE,		//�v���X�X�y�[�X
	TEXTURE_CIRCLE_P,			//�v���C���[�T�[�N��
	TEXTURE_CIRCLE_E,			//�G�l�~�[�T�[�N��
	TEXTURE_CIRCLE_F,			//�p�[�e�B�[(�F�R)�T�[�N��
	TEXTURE_CIRCLE_I,			//�A�C�e���T�[�N��
	TEXTURE_MENU_WINDOW,		//���j���[�E�B���h�E
	TEXTURE_OPERATION,			//��������e�N�X�`��
	TEXTURE_RED_TEXTURE,		//�Ԃ��e�N�X�`��
	TEXTURE_WHITE_TEXTURE,		//�����e�N�X�`��

	TEXTURE_BLUE_TEXTURE,		//���e�N�X�`��
	TEXTURE_ORANGE_TEXTURE,		//�I�����W�e�N�X�`��
	TEXTURE_PURPLE_TEXTURE,		//���e�N�X�`��

	TEXTURE_PARTICLE1,			//�p�[�e�B�N���e�N�X�`��
	TEXTURE_PARTICLE2,			//�p�[�e�B�N���e�N�X�`��
	TEXTURE_LEVELUP,			//���x���A�b�v�e�N�X�`��
	
	//-----�X�e�[�^�X�֘A-----
	TEXTURE_HP_BAR,				//HP�o�[�p�e�N�X�`��
	TEXTURE_RED_HOOD,			//�X�e�[�^�X�p�Ԃ�����摜
	TEXTURE_RED_HOOD_PARALYSIS,	//�X�e�[�^�X�p�Ԃ�����摜(���)
	TEXTURE_RED_HOOD_SLEEP,		//�X�e�[�^�X�p�Ԃ�����摜(����)
	TEXTURE_RED_HOOD_POISON,	//�X�e�[�^�X�p�Ԃ�����摜(��)
	TEXTURE_RED_HOOD_CONFUSION,	//�X�e�[�^�X�p�Ԃ�����摜(����)
	TEXTURE_ATTACK,				//��������
	TEXTURE_DEFENCE,			//�ڂ�����
	TEXTURE_EXP,				//��������

	//-----���l-----
	TEXTURE_0,		//0
	TEXTURE_1,		//1
	TEXTURE_2,		//2
	TEXTURE_3,		//3
	TEXTURE_4,		//4
	TEXTURE_5,		//5
	TEXTURE_6,		//6
	TEXTURE_7,		//7
	TEXTURE_8,		//8
	TEXTURE_9,		//9
	TEXTURE_MAX
};

class CTextureManager
{
private:
	static LPDIRECT3DTEXTURE9	m_TextureData[TEXTURE_MAX];	//�S�e�N�X�`���f�[�^�ۑ��p
	static bool					m_TextureLoad[TEXTURE_MAX];	//�S�e�N�X�`���̓ǂݍ��݊����t���O
public:
	CTextureManager(void);									//�R���X�g���N�^
	~CTextureManager(void);									//�f�X�g���N�^

	static void LoadTexture(void);							//�e�N�X�`���̃��[�h

	static void ReleaseTexture(void);						//�e�N�X�`���f�[�^�̊J��

	static LPDIRECT3DTEXTURE9*	GetTexture(int nNumber);	//�w�肳�ꂽ�e�N�X�`���ԍ��̃f�[�^��n��
};

