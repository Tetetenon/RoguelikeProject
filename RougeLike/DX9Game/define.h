//=======================================================================================
//
//	  �萔��`�A�}�N����`
//
//=======================================================================================

#ifndef _H_DEFINE
#define _H_DEFINE

#pragma once

#include <d3d9.h>
#include <d3dx9.h>

//-------- �}�N��-----
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)			if(x){ x->Release(); x=NULL; }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)			if(x){ delete x; x=NULL; }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if(x){ delete[] x; x=NULL; }
#endif

// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D2 (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2)

//1�O���b�h�̃T�C�Y
#define GRIDSIZE 3.0f

//��ʃT�C�Y
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

//�~����
#define PI 3.14159265359f

//
#define MASS_SIZE 3

//�G���[�l
#define ERROR_NUM -99

// �R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3	vtx;	//���_���W
	D3DXVECTOR3	nor;	//�@���x�N�g��
	D3DCOLOR	diffuse;	//���ˌ�
	D3DXVECTOR2	tex;	//�e�N�X�`�����W
}VERTEX_3D;


//����
enum Direction
{
	Forword = 0,
	Right,
	Back,
	Left,
	MaxDirection
};

//�A�C�e���R�}���h
enum
{
	COMMAND_USE = 0,	//�g��
	COMMAND_EQUIPMENT,	//����
	COMMAND_RELINQUISH,	//�̂Ă�
	COMMAND_MAX
};

//�����R�}���h
enum
{
	EQUIPMENT_COMMAD_BACK = 0,
	EQUIPMENT_COMMAND_MAX
};

//�A�C�e���̖��O
enum ITEMNAME
{
	ITEM_APPLE	= 1,	//�ь�
	ITEM_HERB,			//��
	ITEM_SWORD,			//��
	ITEM_SHIELD,		//��
	ITEM_MAX
};

//�����ł���ő�Z��
#define TRICK_NUM_MAX 4

//�Z�̖��O
enum TRICKNAME
{
	TRICK_NAME_1 = 0,	//�Z�P
	TRICK_NAME_2,
	TRICK_NAME_3,
	TRICK_NAME_4,
	TRICK_NAME_MAX
};

//�}�b�v�f�[�^��Ɏ����I�u�W�F�N�g�̒ʂ��ԍ�
enum ObjectNumber
{
	OBJ_NUM_ITEM	=	0,			//�A�C�e��
	OBJ_NUM_PLAYER	=   1,			//�v���C���[			:	    0��
	OBJ_NUM_PARTY	=   2,			//�p�[�e�B�[			:  1�`  3��
	OBJ_NUM_ENEMY	=   5,			//�G�l�~�[				:  4�`��
	OBJ_NUM_MAX
};

//�A�C�e���̌��ʃW������
enum ITEMEFFECT
{
	EFFECT_NON = 0,				//�������ʂȂ�
	EFFECT_RECOVERY,			//��
	EFFECT_EQUIPMENT_ATTACK,	//�����A�C�e��(�U�����\)
	EFFECT_EQUIPMENT_DEFENCE,	//�����A�C�e��(�h����\)
	EFFECT_MAX			
};

//�Z�̌��ʃW������
enum TRICKEFFECT
{
	TRICK_EFFECT_ATTACK = 0,	//�U��
	TRICK_EFFECT_STATES_UP,		//�X�e�[�^�X�̋����A�㉻
	TRICK_EFFECT_RECOVERY,		//��
	TRICK_EFFECT_MAX
};

//�Z�̌��ʔ͈�
enum TRICKRANGE
{
	TRICK_RANGE_FRONT = 0,	//�O���ɍU��
	TRICK_RANGE_ME,			//���g
	TRICK_RANGE_ALL,		//�����S��
	TRICK_RANGE_WIDE,		//�O���R�}�X
	TRICK_RANGE_MAX			//
};

//�\������X�e�[�^�X��`
enum STATES
{
	STATES_FONT_ATTACK = 0,	//��������
	STATES_FONT_DEFENCE,		//�ڂ�����
	STATES_FONT_EXP,			//��������
	STATES_FONT_MAX
};

//�����ƕ����̌���
#define FontClearance	10.0f

//�����T�C�Y
#define FontScale		45.0f

//�Ń_���[�W
#define PoisonDamage 5

//���N��ԗ�
enum UNIT_STATE
{
	UNIT_STATE_HEALTH = 0,		//���N���̂��̂ł���B
	UNIT_STATE_POISON,			//��
	UNIT_STATE_CONFUSION,		//�����������Ă���!
	UNIT_STATE_WINCE,			//�Ђ��
	UNIT_STATE_PARALYSIS,		//���
	UNIT_STATE_SLEEP,			//����
	UNIT_STATE_NO_MONEY,		//����
	UNIT_STATE_MAX
};


#endif

//=======================================================================================
//	End of File
//=======================================================================================