#pragma once
//�p�[�e�B�N��
#include "C3DObj.h"

class CCamera;
class CParticleManager;

//�p�[�e�B�N���̃p�^�[��
enum ParticlePattern
{
	PARTICLE_PATTERN_DELETE = 0,
	PARTICLE_PATTERN_IMPACT,
	PARTICLE_PATTERN_MAX
};

enum EParticleCoord
{
	eCartesian = 0,				// �������W�n(x,y,z)
	eSpherical,					// �����W�n(r,��,��)
	eCylindrical,				// �~�����W�n(r,h,��)

	eMaxParticleCoord
};

struct TParticleParam
{
	int				TextureNumber;		//�g�p����e�N�X�`���ԍ�
	ESynthetic		synthetic;			// �`����@
	EParticleCoord	coord;				// ���W�n
	float			fDuration;			// ��������
	UINT			uMaxParticles;		// �ő�p�[�e�B�N����
	bool			bLooping;			// �J��Ԃ�
	float			fGravity;			// �d�͉����x
	float			fStartSpeed;		// ����
	float			fStartSpeed2;		// ����2
	float			fStartSize;			// �����T�C�Y
	float			fStartSize2;		// �����T�C�Y2
	float			fStartRotation;		// �����p�x
	float			fStartRotation2;	// �����p�x2
	D3DCOLOR		cStartColor;		// �����J���[
	D3DCOLOR		cStartColor2;		// �����J���[2
	float			fStartLifetime;		// ����
	float			fStartLifetime2;	// ����2
	UINT			uRate;				// 1�b������̃p�[�e�B�N��������
	float			fCornAngle;			// �R�[���p�x
	float			fRadius;			// ���a(180:�����A360:��)
	bool			bColorOverLifetime;	// �������ԂŐF��ύX(�����J���[�������ɂȂ�)
	D3DCOLOR		cOverLifetime[2];	// [0]:�J�n�F�A[1]:�I���F
	bool			bSizeOverLifetime;	// �������ԂŃT�C�Y��ύX(�����T�C�Y�������ɂȂ�)
	float			fOverLifetime[2];	// [0]:�J�n�T�C�Y�A[1]:�I���T�C�Y
};

class CParticle:
	public C3DObj
{
private:
	CParticleManager* m_pParticlemanager;

	TParticleParam		m_pp;
	float				m_fTime;			// �p�[�e�B�N����������
	float				m_fRate;			// �p�[�e�B�N�����������[�N
	UINT				m_uParticles;		// �c��p�[�e�B�N����	

	float				m_fLifeTime;		//��������

	int					m_nID;				//�p�[�e�B�N����ӂ̔ԍ�
	bool				m_bDeleteFlg;		//�폜�t���O
	struct TGrain 
	{
		TGrain*		m_pBack;
		TGrain*		m_pNext;
		D3DXVECTOR3	m_pos;
		D3DXVECTOR3	m_startPos;
		D3DXVECTOR3	m_velocity;
		D3DXVECTOR3	m_accel;
		float		m_size;
		float		m_startSize;
		float		m_angle;
		D3DCOLOR	m_color;
		D3DCOLOR	m_startColor;
		float		m_lifetime;
		float		m_startLifetime;
	};

	TGrain*		m_pGrain;
	TGrain*		m_pUse;
	TGrain*		m_pUnused;
	UINT		m_uUse;

	struct TVertex 
	{
		D3DVECTOR	m_pos;
		D3DVECTOR	m_normal;
		D3DCOLOR	m_diffuse;
		float		m_u, m_v;
	};

	TVertex*	m_pVertex;
	WORD*		m_pIndex;
public:
	CParticle(CGameScene* pScene);							//�R���X�g���N�^
	CParticle(CGameScene* pScene, TParticleParam* ppp);		//�R���X�g���N�^
	virtual ~CParticle(void);							//�f�X�g���N�^

	virtual void PostInit(void);						//��������̏���
	void Delete(TGrain* p);								//�폜
	TGrain* New(void);									//����
	virtual void Update(void);							//�X�V
	virtual void Draw(void);							//�`��
	virtual void DrawAlpha(void);						//�������`��
	virtual void Fin(void);								//�I������
	void DrawLast(void);								
	void SetParam(TParticleParam& pp);					//�p�����[�^�[�ݒ�
	void GetDefaultParam(TParticleParam& pp);			//�f�t�H���g�p�����[�^�[�ݒ�

	static void Generation(C3DObj* pGenetator,int Pattern);		//���g�̐���

	void SetParmData_Delete(D3DXMATRIX world);					//�p�����[�^�[�f�[�^��ݒ肷��i���Łj
	
	//�폜�t���O�̏�Ԃ��擾
	bool GetDeleteFlg() { return m_bDeleteFlg; }
};