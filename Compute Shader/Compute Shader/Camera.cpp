#include "Camera.h"
#include "DirectXCore.h"
#include "GameObject.h"

#define TRANSLATION_SPEED 5.0f

#define ROTATION_SPEED PI
#define MOUSE_ROTATION_SPEED PI * 0.1f

void Camera::Initialize(DirectXCore* pCore,/*Renderer* renderer, */float fFOV, float fNearClip, float fFarClip)
{
	//m_pRenderer = renderer;
	m_pCore = pCore;
	m_bDirty = true;

	//m_fFOV = fFOV;
	m_fNearClip = fNearClip;
	m_fFarClip = fFarClip;

	m_fFOV = fFOV;

	//m_frFrustum.Build(fFOV, fNearClip, fFarClip, 
	//	m_pRenderer->GetScreenWidth() / (float)m_pRenderer->GetScreenHeight(), m_mWorldMatrix);

	m_mProjectionMatrix.MakePerspective(m_fFOV, 
			pCore->GetScreenWidth() / (float)pCore->GetScreenHeight(), fNearClip, fFarClip);

	D3D11_BUFFER_DESC shaderBuffDesc;
	ZeroMemory(&shaderBuffDesc, sizeof(D3D11_BUFFER_DESC));
	shaderBuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	shaderBuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	shaderBuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	shaderBuffDesc.ByteWidth = sizeof(ShaderCameraBuffer);

	if(FAILED(m_pCore->GetDevice()->CreateBuffer(&shaderBuffDesc, 0, &m_pCameraConstBuffer.p)))
		MessageBox(NULL, L"Failed to create Camera Constant Buffer" , L"", MB_OK | MB_ICONERROR);

	shaderBuffDesc.ByteWidth = sizeof(ShaderObjectBuffer);

	if(FAILED(m_pCore->GetDevice()->CreateBuffer(&shaderBuffDesc, 0, &m_pObjectConstBuffer.p)))
		MessageBox(NULL, L"Failed to create Object Constant Buffer" , L"", MB_OK | MB_ICONERROR);

	m_mWorldMatrix *= XMMatrixTranslation(0.0f, 0.0f, -10.0f);
	
	m_pCore->GetContext()->VSSetConstantBuffers(CAMERA_CONST_BUFF_REGISTER, 1, &m_pCameraConstBuffer.p);
	m_pCore->GetContext()->VSSetConstantBuffers(OBJECT_CONST_BUFF_REGISTER, 1, &m_pObjectConstBuffer.p);
}

void Camera::ResetCamera()
{
	m_mWorldMatrix.make_identity();
	m_bDirty = true;
}

void Camera::ReorientCamera()
{
	m_mWorldMatrix.make_identity_3x3();
	m_bDirty = true;
}

void Camera::UpdateMatrices()
{
	if(m_bDirty)
	{
		m_mViewMatrix = MatrixInverse(m_mWorldMatrix);

		m_ShaderCameraBuffer.m_mViewProjectionMatrix = m_mViewMatrix * m_mProjectionMatrix;
		m_ShaderCameraBuffer.m_mInvViewProjMatrix = MatrixInverse(m_ShaderCameraBuffer.m_mViewProjectionMatrix);
		m_ShaderCameraBuffer.m_CameraPos = m_mWorldMatrix.position;

		D3D11_MAPPED_SUBRESOURCE cameraSubresource;

		m_pCore->GetContext()->Map(m_pCameraConstBuffer.p, 0, D3D11_MAP_WRITE_DISCARD, 0, &cameraSubresource);
			memcpy(cameraSubresource.pData, &m_ShaderCameraBuffer, sizeof(ShaderCameraBuffer));
		m_pCore->GetContext()->Unmap(m_pCameraConstBuffer.p, 0);

		//m_vPrevPos = m_mWorldMatrix.position;
	
		//m_frFrustum.Build(m_fFOV, m_fNearClip, m_fFarClip, 
			//m_pRenderer->GetScreenWidth() / (float)m_pRenderer->GetScreenHeight(), m_mWorldMatrix);

		m_bDirty = false;
	}
}

void Camera::SetMVPAndWorldMatrices(GameObject* pObject)
{
	if(pObject)
	{
		m_ShaderObjectBuffer.m_mMVPMatrix = pObject->GetMatrix() * m_ShaderCameraBuffer.m_mViewProjectionMatrix;
		m_ShaderObjectBuffer.m_mWorldMatrix = pObject->GetMatrix();

		D3D11_MAPPED_SUBRESOURCE objectSubresource;

		m_pCore->GetContext()->Map(m_pObjectConstBuffer.p, 0, D3D11_MAP_WRITE_DISCARD, 0, &objectSubresource);
			memcpy(objectSubresource.pData, &m_ShaderObjectBuffer, sizeof(ShaderObjectBuffer));
		m_pCore->GetContext()->Unmap(m_pObjectConstBuffer.p, 0);
	}
}

void Camera::SetMVPAndWorldMatrices(const Matrix4f& matrix)
{
	m_ShaderObjectBuffer.m_mMVPMatrix = matrix * m_ShaderCameraBuffer.m_mViewProjectionMatrix;
	m_ShaderObjectBuffer.m_mWorldMatrix = matrix;

	D3D11_MAPPED_SUBRESOURCE objectSubresource;

	m_pCore->GetContext()->Map(m_pObjectConstBuffer.p, 0, D3D11_MAP_WRITE_DISCARD, 0, &objectSubresource);
		memcpy(objectSubresource.pData, &m_ShaderObjectBuffer, sizeof(ShaderObjectBuffer));
	m_pCore->GetContext()->Unmap(m_pObjectConstBuffer.p, 0);
}

void Camera::MoveForward(double fElapsedTime)
{
	m_mWorldMatrix.MoveForward(fElapsedTime * TRANSLATION_SPEED);

	m_bDirty = true;
}

void Camera::MoveBackward(double fElapsedTime)
{
	m_mWorldMatrix.MoveBackward(fElapsedTime * TRANSLATION_SPEED);

	m_bDirty = true;
}

void Camera::MoveLeft(double fElapsedTime)
{
	m_mWorldMatrix.MoveLeft(fElapsedTime * TRANSLATION_SPEED);

	m_bDirty = true;
}

void Camera::MoveRight(double fElapsedTime)
{
	m_mWorldMatrix.MoveRight(fElapsedTime * TRANSLATION_SPEED);

	m_bDirty = true;
}

void Camera::MoveUp(double fElapsedTime)
{
	m_mWorldMatrix.MoveUp(fElapsedTime * TRANSLATION_SPEED);

	m_bDirty = true;
}

void Camera::MoveDown(double fElapsedTime)
{
	m_mWorldMatrix.MoveDown(fElapsedTime * TRANSLATION_SPEED);

	m_bDirty = true;
}

void Camera::RotateLeft(double fElapsedTime)
{
	m_mWorldMatrix.Rotate_LocalY_Radians(-ROTATION_SPEED * fElapsedTime);

	m_bDirty = true;
}

void Camera::RotateRight(double fElapsedTime)
{
	m_mWorldMatrix.Rotate_LocalY_Radians(ROTATION_SPEED * fElapsedTime);

	m_bDirty = true;
}

void Camera::RotateUp(double fElapsedTime)
{
	m_mWorldMatrix.Rotate_LocalX_Radians(-ROTATION_SPEED * fElapsedTime);

	m_bDirty = true;
}

void Camera::RotateDown(double fElapsedTime)
{
	m_mWorldMatrix.Rotate_LocalX_Radians(ROTATION_SPEED * fElapsedTime);

	m_bDirty = true;
}

void Camera::RotateCameraMouseMovement(POINT movement, double fElapsedTime)
{
	if(movement.x)
	{
		Vec3f tmpPos = m_mWorldMatrix.position;

		m_mWorldMatrix.position.zero_out();

		float fDotProduct = m_mWorldMatrix.yAxis.dot_product(Vec3f(0.0f, 1.0f, 0.0f));
		//XMStoreFloat(&fDotProduct, XMVector3Dot(m_mWorldMatrix.toXMMatrix().r[1], XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)));

		if(fDotProduct > 0.0f)
			m_mWorldMatrix.Rotate_GlobalY_Radians(-movement.x * (float)fElapsedTime * 0.5f);
		else
			m_mWorldMatrix.Rotate_GlobalY_Radians(-movement.x * (float)fElapsedTime * 0.5f);

		m_mWorldMatrix.position = tmpPos;

		m_bDirty = true;
	}

	if(movement.y)
	{
		m_mWorldMatrix.Rotate_LocalX_Radians(-movement.y * (float)fElapsedTime * 0.5f);

		m_bDirty = true;
	}
}

// depth is a 0-1 value
Vec3f Camera::Unproject(POINT screenPos)
{
	const D3D11_VIEWPORT& viewport = m_pCore->GetViewport();

	Vec3f unprojectedPoint = XMVector3Unproject(XMVectorSet(screenPos.x, screenPos.y, 0, 0), viewport.TopLeftX, viewport.TopLeftY,
		viewport.Width, viewport.Height, viewport.MinDepth, viewport.MaxDepth, m_mProjectionMatrix.toXMMatrix(), m_mViewMatrix.toXMMatrix(), XMMatrixIdentity());

	return unprojectedPoint - m_mWorldMatrix.position;
}

/*float Camera::GetAspectRatio() const
{ 
	return m_pRenderer->GetScreenWidth() / (float)m_pRenderer->GetScreenHeight(); 
}*/