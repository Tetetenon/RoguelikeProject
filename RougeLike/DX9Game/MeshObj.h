//���b�V���I�u�W�F�N�g��`
#pragma once
#include "Mesh.h"
#include "C3DObj.h"

class CMeshObj :
	public C3DObj
{
protected:
	CMesh*	m_pMesh;				//���b�V���f�[�^�|�C���^
	int		m_nMeshNumber;			//�g�p���郁�b�V���f�[�^�̔ԍ�
public:
	CMeshObj(CGameScene* pScene);
	CMeshObj();
	virtual ~CMeshObj(void);

	virtual void Init();	//������
	virtual void Fin();		//�I������
	virtual void Update();	//�X�V
	virtual void Draw();	//�`�揈��
	virtual void DrawAlpha();	//�`�揈��

	void SetMesh (CMesh *pMesh){m_pMesh = pMesh;}
	CMesh* GetMesh(){return m_pMesh;}
	
	DWORD GetPieceCount();
	void GetInitPiece(PIECE* pPiece);
};

