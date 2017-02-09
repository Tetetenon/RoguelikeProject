#pragma once
#include "C2DTexture.h"

//�N���X�̒�`
class  CDamageBillBoardManager;

//�_���[�W�̐��l��\������N���X
#define POLYGON_SIZE_X 1.0f
#define POLYGON_SIZE_Y 3.0f
#define POLYGON_SIZE_Z 3.0f

//�\�����錅��
#define DrawDigit 3

//��������
#define LifeTime 60

//�|���S���p�\����
struct PolygonData
{
	D3DXMATRIX				m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_Pos;				//�ʒu���
	D3DXVECTOR3				m_Scl;				// �X�P�[��
	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuff;		//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	int						m_nTextureNumber;	//�g�p����e�N�X�`���ԍ�
	bool					m_bDrawFlg;			//�`�悷�邩�A���Ȃ���
};

//�ړ����E�l
const float MoveRimit_X = 5;
const float MoveRimit_Y = 5;
const float MoveRimit_Z = 5;

//�ړ�����
const float MoveVecX = 0.0f;
const float MoveVecY = 0.01f;
const float MoveVecZ = 0.0f;

class CDamageNotation :
	public C2DTexture
{
private:
	PolygonData m_NumPolygon[DrawDigit];	//�\������|���S���f�[�^
	D3DXVECTOR3 m_MoveVector;				//�ړ�����
	D3DXVECTOR3 m_AmountMovement;			//�ړ���
	int			m_nAlpha;					//�����x

	CDamageBillBoardManager* m_pManager;	//�}�l�[�W���[�̃|�C���^
	float		m_LifeTime;					//��������
	int			m_nID;						//�ŗLID
public:
	CDamageNotation(int Damage,D3DXVECTOR3 Pos);		//�R���X�g���N�^
	~CDamageNotation();					//�f�X�g���N�^

	void Update();						//�X�V
	void Draw();						//�`��

	float GetLifeTime()
	{
		return m_LifeTime;
	}

	HRESULT MakeVertex();				//���_���̍쐬


};

