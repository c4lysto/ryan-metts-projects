#ifndef DIRECTXCORE_H
#define DIRECTXCORE_H

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <DirectXMath.h>
using namespace DirectX;

#include <atlbase.h>

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(rel) if(rel) rel->Release(); rel = nullptr;
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(del) if(del) delete del; del = nullptr;
#endif

#define PI 3.14159265359f

#define FLT_EPSILON     1.192092896e-07F

#define DEG_TO_RAD(deg) ((deg) * PI / 180.0f)

#define RAD_TO_DEG(rad) ((rad) * 180.0f / PI)

#ifndef max
	#define max(a,b)	(((a) > (b) ? (a) : (b)))
#endif

#ifndef min
	#define min(a,b)	(((a) < (b) ? (a) : (b)))
#endif

#include "RenderTarget.h"

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

enum RasterizerStateEnum {RS_FILL_MODE, RS_CULL_MODE, RS_FRONT_CCW, RS_DEPTH_BIAS,
						RS_SLOPE_SCALED_DEPTH_BIAS, RS_DEPTH_BIAS_CLAMP, RS_DEPTH_CLIP_ENABLE,
						RS_SCISSOR_ENABLE, RS_MULTISAMPLE_ENABLE, RS_ANTIALIASED_LINE_ENABLE};

class DirectXCore
{
private:
	CComPtr<ID3D11Device> m_pDevice;
	CComPtr<IDXGISwapChain> m_pSwapChain;
	CComPtr<ID3D11DeviceContext> m_pContext;
	CComPtr<ID3D11DepthStencilView> m_pDepthStencil;
	ID3D11RenderTargetView* m_pTargetViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	CComPtr<ID3D11DepthStencilState> m_pDepthStencilState;
	CComPtr<ID3D11RasterizerState> m_pRasterizerState;
	D3D11_RASTERIZER_DESC m_RasterizerDesc;
	RenderTarget	m_rtBackBuffer;
	D3D11_VIEWPORT m_Viewport;

#ifdef _DEBUG
	IDXGIDebug* m_pDebugger;
#endif

	unsigned int m_unScreenWidth, m_unScreenHeight;

public:
	bool Initialize(HWND hWnd, unsigned short usWidth, unsigned short usHeight, bool bWindowed);

	ID3D11Device* GetDevice() const {return m_pDevice;}
	IDXGISwapChain* GetSwapChain() const {return m_pSwapChain;}
	ID3D11DeviceContext* GetContext() const {return m_pContext;}
	D3D11_VIEWPORT GetViewport() const {return m_Viewport;}

	unsigned int GetScreenWidth() const {return m_unScreenWidth;}
	unsigned int GetScreenHeight() const {return m_unScreenHeight;}

	void ChangeRasterizerState(RasterizerStateEnum eState, ...);
	void CommitRasterizerChanges();

	void Clear(RenderTarget* const* pTargets = nullptr, unsigned int unNumTargets = 1,  
		UINT unClearFlags = D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, float fClearDepth = 1.0f, 
		UINT8 unClearStencil = 0, XMFLOAT4 color = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));

	void Present(UINT syncInterval = DXGI_SWAP_EFFECT_DISCARD, UINT flags = 0);

	DirectXCore(void);
	~DirectXCore(void);
};

#endif