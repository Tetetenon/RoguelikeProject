//=======================================================================================
//
//	  ���b�V�� �N���X
//
//=======================================================================================
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <stdio.h>
#include "define.h"

#include "Mesh.h"
#include "Graphics.h"

#define INIT_PIECESPD	3.0f	// �j�Џ���
#define TIME_EXPLOSION	60		// �j�Е\���t���[��

//---------------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------------
CMesh::CMesh()
{
	m_pD3DMesh = NULL;
	m_dwNumMaterial = 0;
	m_pMaterial = NULL;
	m_ppTexture = NULL;
	m_pAttr = NULL;
	m_dwAttr = 0;
	m_vBBox = D3DXVECTOR3(0, 0, 0);
	m_vCenter = D3DXVECTOR3(0, 0, 0);
	m_fRadius = 0.0f;

	m_pBBox = NULL;
	m_pBSphere = NULL;
	m_cvBColor.r = 0.0f;
	m_cvBColor.g = 1.0f;
	m_cvBColor.b = 0.0f;
	m_cvBColor.a = 0.3f;
}

//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CMesh::~CMesh()
{
	Finalize();
}

//---------------------------------------------------------------------------------------
// ���b�V��������
//---------------------------------------------------------------------------------------
bool CMesh::Initialize(LPCTSTR pszFName, bool bReverse)
{
	TCHAR			szMsg[MAX_PATH + 32];
	TCHAR			szDir[_MAX_DIR];
	TCHAR			szCurrentDir[_MAX_PATH];

	LPD3DXBUFFER	pD3DXMtrlBuffer = NULL;

	// �t�H���_���𒊏o
	_tsplitpath(pszFName, NULL, szDir, NULL, NULL);

	// �w�t�@�C�����烁�b�V���f�[�^��ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(pszFName, D3DXMESH_SYSTEMMEM, CGraphics::GetDevice(),
		NULL, &pD3DXMtrlBuffer, NULL, &m_dwNumMaterial, &m_pD3DMesh))) 
	{
		_stprintf(szMsg, _T("X�t�@�C��(%s)�̓ǂݍ��݂Ɏ��s���܂����B"), pszFName);
		MessageBox(NULL, szMsg, NULL, MB_OK);
		return false;
	}
	// �J�����g�f�B���N�g����ύX
	if (szDir[0]) {
		GetCurrentDirectory(_MAX_PATH, szCurrentDir);
		SetCurrentDirectory(szDir);
	}

	// �}�e���A���ǂݍ���
	D3DXMATERIAL* pD3DMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMaterial = new D3DMATERIAL9[m_dwNumMaterial];
	m_ppTexture = new LPDIRECT3DTEXTURE9[m_dwNumMaterial];
	for (DWORD i = 0; i < m_dwNumMaterial; i++)
	{ 
		m_pMaterial[i] = pD3DMaterials[i].MatD3D;
		m_pMaterial[i].Ambient = m_pMaterial[i].Diffuse;
		m_ppTexture[i] = NULL;
		if (pD3DMaterials[i].pTextureFilename && pD3DMaterials[i].pTextureFilename[0])
		{
			// �e�N�X�`���t�@�C����ǂݍ���
			if (FAILED(D3DXCreateTextureFromFileA(CGraphics::GetDevice(),
				pD3DMaterials[i].pTextureFilename, &m_ppTexture[i]))) {
				_stprintf(szMsg, _T("�e�N�X�`��(%hs)�̓ǂݍ��݂Ɏ��s���܂����B"),
					pD3DMaterials[i].pTextureFilename);
				MessageBox(NULL, szMsg, NULL, MB_OK);
			}
		}
	}

	// �����e�[�u���𐶐����邽�߂̍œK��
	LPD3DXMESH pMeshWk;
	HRESULT hr = m_pD3DMesh->Optimize(D3DXMESHOPT_ATTRSORT,
		NULL, NULL, NULL, NULL, &pMeshWk);
	if (SUCCEEDED(hr))
	{
		m_pD3DMesh->Release();
		m_pD3DMesh = pMeshWk;
	} 
	else
	{
		SAFE_RELEASE(pD3DXMtrlBuffer);
		return false;
	}

	// �����e�[�u���擾
	m_dwAttr = 0;
	m_pD3DMesh->GetAttributeTable(NULL, &m_dwAttr);
	m_pAttr = new D3DXATTRIBUTERANGE[m_dwAttr];
	m_pD3DMesh->GetAttributeTable(m_pAttr, &m_dwAttr);

	// ���_��MVERTEX�ƈقȂ�ꍇ�A����
	DWORD dwFVF = m_pD3DMesh->GetFVF();
	if (dwFVF != FVF_MVERTEX) 
	{
		LPD3DXMESH pMeshTmp = m_pD3DMesh;
		pMeshTmp->CloneMeshFVF(pMeshTmp->GetOptions(),
			FVF_MVERTEX, CGraphics::GetDevice(), &m_pD3DMesh);
		SAFE_RELEASE(pMeshTmp);
		if (!(dwFVF & D3DFVF_NORMAL)) 
		{
			D3DXComputeNormals(m_pD3DMesh, NULL);
		}	// �@����������Βǉ�
	}

	// ���_�o�b�t�@���璸�_�����擾
	DWORD dwVtx = m_pD3DMesh->GetNumVertices();
	MVERTEX* pVtx = new MVERTEX[dwVtx];
	LPVOID pSrc = NULL;
	m_pD3DMesh->LockVertexBuffer(0, &pSrc);

	if (bReverse)
	{
		D3DXMATRIX rev;
		D3DXMatrixRotationY(&rev, D3DXToRadian(180));
		D3DXVECTOR3 v;
		MVERTEX* p = (MVERTEX*)pSrc;
		for (DWORD i = 0; i < dwVtx; ++i, ++p) 
		{
			v = p->pos;
			D3DXVec3TransformCoord(&v, &v, &rev);
			p->pos = v;
			v = p->normal;
			D3DXVec3TransformNormal(&v, &v, &rev);
			p->normal = v;
		}
	}

	CopyMemory(pVtx, pSrc, sizeof(MVERTEX) * dwVtx);
	m_pD3DMesh->UnlockVertexBuffer();

	// ���E�{�b�N�X�擾
	D3DXVECTOR3 vMin, vMax;
	vMin = vMax = pVtx[0].pos;
	for (DWORD i = 1; i < dwVtx; ++i) 
	{
		if (vMin.x > pVtx[i].pos.x)
			vMin.x = pVtx[i].pos.x;
		if (vMin.y > pVtx[i].pos.y)
			vMin.y = pVtx[i].pos.y;
		if (vMin.z > pVtx[i].pos.z)
			vMin.z = pVtx[i].pos.z;
		if (vMax.x < pVtx[i].pos.x)
			vMax.x = pVtx[i].pos.x;
		if (vMax.y < pVtx[i].pos.y)
			vMax.y = pVtx[i].pos.y;
		if (vMax.z < pVtx[i].pos.z)
			vMax.z = pVtx[i].pos.z;
	}
	m_vCenter = (vMax + vMin) / 2.0f;
	m_vBBox = (vMax - vMin) / 2.0f;
	// ���E���擾
	m_fRadius = 0.0f;
	for (DWORD i = 0; i < dwVtx; ++i) 
	{
		float dx = pVtx[i].pos.x - m_vCenter.x;
		float dy = pVtx[i].pos.y - m_vCenter.y;
		float dz = pVtx[i].pos.z - m_vCenter.z;
		float fLen = sqrtf(dx * dx + dy * dy + dz * dz);
		if (m_fRadius < fLen) {
			m_fRadius = fLen;
		}
	}
	// ���E�\���p���b�V������
	D3DXCreateBox(CGraphics::GetDevice(),
		m_vBBox.x * 2.0f, m_vBBox.y * 2.0f, m_vBBox.z * 2.0f,
		&m_pBBox, NULL);
	D3DXCreateSphere(CGraphics::GetDevice(),
		m_fRadius, 16, 8, &m_pBSphere, NULL);

	// �C���f�b�N�X�o�b�t�@����C���f�b�N�X�����擾

	// ���_�z��A�C���f�b�N�X�z������
	delete[] pVtx;

	// �J�����g�f�B���N�g�������ɖ߂�
	if (szDir[0])
		SetCurrentDirectory(szCurrentDir);

	pD3DXMtrlBuffer->Release();

	return true;
}

//---------------------------------------------------------------------------------------
// ���b�V�����
//---------------------------------------------------------------------------------------
void CMesh::Finalize()
{
	SAFE_DELETE_ARRAY(m_pAttr);

	SAFE_RELEASE(m_pBSphere);
	SAFE_RELEASE(m_pBBox);

	// �e�N�X�`�� �I�u�W�F�N�g�����
	if (m_ppTexture) {
		for (DWORD i = 0; i < m_dwNumMaterial; i++) {
			SAFE_RELEASE(m_ppTexture[i]);
		}
		SAFE_DELETE_ARRAY(m_ppTexture);
	}
	SAFE_DELETE_ARRAY(m_pMaterial);

	SAFE_RELEASE(m_pD3DMesh);	// ���b�V�� �I�u�W�F�N�g�����
}

//---------------------------------------------------------------------------------------
// ���b�V���`��
//---------------------------------------------------------------------------------------
void CMesh::Draw(D3DXMATRIX& world)
{

	DrawNoAlpha(world);
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DrawAlpha(world);
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

// �s���������`��
void CMesh::DrawNoAlpha(D3DXMATRIX& world)
{
	// ���[���h �}�g���b�N�X�ݒ�
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &world);

	for (DWORD i = 0; i < m_dwAttr; i++) {
		DWORD dwID = m_pAttr[i].AttribId;
		if (m_pMaterial[dwID].Diffuse.a < 1.0f) {
			continue;
		}
		CGraphics::GetDevice()->SetMaterial(&m_pMaterial[dwID]);
		CGraphics::GetDevice()->SetTexture(0, m_ppTexture[dwID]);	// �e�N�X�`����ݒ�
		m_pD3DMesh->DrawSubset(dwID);								// �`������s
	}
}

// �����������`��
void CMesh::DrawAlpha(D3DXMATRIX& world)
{
	// ���[���h �}�g���b�N�X�ݒ�
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &world);

	for (DWORD i = 0; i < m_dwAttr; i++) {
		DWORD dwID = m_pAttr[i].AttribId;
		if (m_pMaterial[dwID].Diffuse.a >= 1.0f) {
			continue;
		}
		CGraphics::GetDevice()->SetMaterial(&m_pMaterial[dwID]);
		CGraphics::GetDevice()->SetTexture(0, m_ppTexture[dwID]);	// �e�N�X�`����ݒ�
		m_pD3DMesh->DrawSubset(dwID);								// �`������s
	}
}
// ���E�{�b�N�X�`��
void CMesh::DrawAABB(D3DXMATRIX& world)
{
	// ���S���W���ړ�
	D3DXVECTOR3 vPos;
	D3DXVec3TransformCoord(&vPos, &GetCenter(), &world);

	// ���[���h�}�g���b�N�X�ݒ�
	D3DXMATRIX mtx;
	D3DXMatrixTranslation(&mtx, vPos.x, vPos.y, vPos.z);
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->SetTransform(D3DTS_WORLD, &mtx);

	// �}�e���A���ݒ�
	pDevice->SetTexture(0, NULL);
	D3DMATERIAL9 mtrl = {{0.0f}};
	mtrl.Diffuse = m_cvBColor;
	pDevice->SetMaterial(&mtrl);

	// �`��
	m_pBBox->DrawSubset(0);
}

// ���E���`��
void CMesh::DrawBSphere(D3DXMATRIX& world)
{
	// ���S���W���ړ�
	D3DXVECTOR3 vPos;
	D3DXVec3TransformCoord(&vPos, &GetCenter(), &world);

	// ���[���h�}�g���b�N�X�ݒ�
	D3DXMATRIX mtx;
	D3DXMatrixTranslation(&mtx, vPos.x, vPos.y, vPos.z);
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->SetTransform(D3DTS_WORLD, &mtx);

	// �}�e���A���ݒ�
	pDevice->SetTexture(0, NULL);
	D3DMATERIAL9 mtrl = {{0.0f}};
	mtrl.Diffuse = m_cvBColor;
	pDevice->SetMaterial(&mtrl);

	// �`��
	m_pBSphere->DrawSubset(0);
}

//=======================================================================================
//	End of File
//=======================================================================================