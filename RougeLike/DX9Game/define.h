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


//�����R�}���h
enum
{
	EQUIPMENT_COMMAD_BACK = 0,
	EQUIPMENT_COMMAND_MAX
};

//�����ł���ő�Z��
#define TRICK_NUM_MAX 4

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

//�A�C�e���R�}���h
enum
{
	COMMAND_USE = 0,	//�g��
	COMMAND_EQUIPMENT,	//����
	COMMAND_RELINQUISH,	//�̂Ă�
	COMMAND_MAX
};
//�����ƕ����̌���
#define FontClearance	10.0f

//�����T�C�Y
#define FontScale		45.0f

//
#define RIKU_TAKAHASHI	(0)

//�W���C�X�e�B�b�N�̍��X�e�B�b�N�����͂��ꂽ�Ƃ͂񂾂񂷂�l
const float JoyMoveCap = 0.5f;
//�{�^���̓��͂̃C���^�[�o�[���^�C��
const float ButtonIntervalTime = 10.0f;

#define DebugMode (false)

#endif

//=======================================================================================
//	End of File
//=======================================================================================