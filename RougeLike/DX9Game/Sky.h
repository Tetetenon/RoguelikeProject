// スカイドーム クラス定義

#pragma once

#include "MeshObj.h"
#include "Camera.h"

class CSky : public CMeshObj
{
private:
	//変数
	static CMesh	m_mesh;
	static CCamera*	m_pCamera;
	static CSky*	m_pSky;		//シングルトン

	//関数
	CSky(CGameScene* pScene);
	~CSky(void);
public:
	static void Create(CGameScene* pScene);	//空オブジェクトの作成
	static void Delete();	//空オブジェクトの削除

	static CSky* GetPointer();	//オブジェクトのポインタを渡す

	void Init();		// 初期化
	void Update();		// 更新
	void Draw();		// 描画
	void DrawAlpha();	// 半透明描画
	void Fin();			// 解放
	void PostUpdate();			// 更新後処理
	void PreDraw();				// 描画前処理
};