#pragma once


#include <d3d9.h>
#include <d3dx9.h>

//�e�N�X�`���`�掞�ɕK�v�ȗv�f���܂Ƃ߂��\����
typedef struct
{
	D3DXVECTOR3 pos;    //���_���W
	float       rhw;    //�e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR    col;    //���_�J���[
	D3DXVECTOR2 tex;    //�e�N�X�`�����W
}VERTEX_2D;


//���_�t�H�[�}�b�g�i���_���W[2D]/���_�J���[�j
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)//(�ʒu��� | �J���[ | �e�N�X�`���̏��0���Ⴞ��)

//���_��
#define NUM_VERTEX  (4)

//�|���S����
#define NUM_POLYGON 2