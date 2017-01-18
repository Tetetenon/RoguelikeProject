//=======================================================================================
//
//	  ���b�V�� �N���X��`
//
//=======================================================================================
#pragma once
#include <windows.h>		// Windows�v���O�����ɂ͂����t����
#include <tchar.h>			// �ėp�e�L�X�g �}�b�s���O
#include <d3d9.h>			// DirectX Graphics �֘A�̃w�b�_
#include <d3dx9.h>			// DirectX Graphics �֘A�̃w�b�_

// ���_�t�H�[�}�b�g
struct MVERTEX
{
	D3DVECTOR	pos;		// ���_���W
	D3DVECTOR	normal;		// �@���x�N�g��
	float		u, v;		// �e�N�X�`�����W
};
#define FVF_MVERTEX	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

// �j��
struct PIECE
{
	MVERTEX			v[3];	// �O�p�`�̍��W(�d�S�����_)
	D3DXMATRIX		world;	// ���[���h�ϊ�
	D3DXVECTOR3		speed;	// ���x
	D3DXVECTOR3		accel;	// �����x
	D3DCOLORVALUE	color;	// �F
	D3DXVECTOR3		axis;	// ��]��
	float			rspeed;	// ��]���x
};

class CMesh
{
private:
	LPD3DXMESH				m_pD3DMesh;		// D3DXMesh �I�u�W�F�N�g
	DWORD					m_dwNumMaterial;// �}�e���A����
	D3DMATERIAL9*			m_pMaterial;	// �}�e���A��
	LPDIRECT3DTEXTURE9*		m_ppTexture;	// �e�N�X�`��
	LPD3DXATTRIBUTERANGE	m_pAttr;		// �����e�[�u��
	DWORD					m_dwAttr;		// ������

	D3DXVECTOR3				m_vBBox;		// ���E�{�b�N�X(�����̃T�C�Y)
	D3DXVECTOR3				m_vCenter;		// ���E��/���E�{�b�N�X���S���W
	float					m_fRadius;		// ���E��(���a)

	LPD3DXMESH				m_pBBox;		// ���E�{�b�N�X ���b�V��
	LPD3DXMESH				m_pBSphere;		// ���E�����b�V��
	D3DCOLORVALUE			m_cvBColor;		// ���E��/�{�b�N�X�F
public:
	CMesh();								// �R���X�g���N�^
	virtual ~CMesh();						// �f�X�g���N�^

	bool Initialize(LPCTSTR pszFName, bool bReverse = false);	// ���b�V��������
	void Finalize();						// ���b�V�����
	void Draw(D3DXMATRIX& world);			// ���b�V���`��
	void DrawNoAlpha(D3DXMATRIX& world);	// �s���������`��
	void DrawAlpha(D3DXMATRIX& world);		// �����������`��
	D3DXVECTOR3& GetBBox() {return m_vBBox;}
	D3DXVECTOR3& GetCenter() {return m_vCenter;}
	float GetRadius() {return m_fRadius;}
	void DrawAABB(D3DXMATRIX& world);		// ���E�{�b�N�X�`��
	void DrawBSphere(D3DXMATRIX& world);	// ���E���`��
	void SetBColor(D3DCOLORVALUE& cvBColor) {m_cvBColor = cvBColor;}
	void SetBColor(float r, float g, float b, float a) {m_cvBColor.r = r; m_cvBColor.g = g; m_cvBColor.b = b; m_cvBColor.a = a;}
	D3DCOLORVALUE& GetBColor() {return m_cvBColor;}
	
	void MaterialAlpha() {m_pMaterial->Diffuse.a = 0.3f;}
	void MaterialNoAlpha() {m_pMaterial->Diffuse.a = 1.0f;}
};

//=======================================================================================
//	End of File
//=======================================================================================