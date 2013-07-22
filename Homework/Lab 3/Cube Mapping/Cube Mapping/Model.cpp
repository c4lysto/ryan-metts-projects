#include "Model.h"
#include "DirectXCore.h"
#include "VertexDeclarations.h"
using namespace VertexDecl;

Model::Model(void)
{
	m_pVertices = nullptr;
	m_unNumVertices = m_unVertexStride = 0;
}

Model::~Model(void)
{
	if(m_pVertices)
		delete[] m_pVertices;
}

void Model::Render(DirectXCore* pCore)
{

}

void Model::CreateBoxVertClr(DirectXCore* pCore)
{
	m_vIndices.clear();
	SAFE_DELETE(m_pVertices);

	m_unNumVertices = 8;
	m_unVertexStride = sizeof(VertClr);

	VertClr* vertices = new VertClr[m_unNumVertices];
	m_pVertices = vertices;

	// Front Top Left - 0
	vertices[0].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[0].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	// Front Top Right - 1
	vertices[1].position = XMFLOAT3(1.0f, 1.0f, -1.0f);
	vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	// Front Bottom Right - 2
	vertices[2].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[2].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	// Front Bottom Left - 3
	vertices[3].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	vertices[3].color = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);


	// Back Top Left - 4
	vertices[4].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vertices[4].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	// Back Top Right - 5
	vertices[5].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[5].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	// Back Bottom Right - 6
	vertices[6].position = XMFLOAT3(1.0f, -1.0f, 1.0f);
	vertices[6].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	// Back Bottom Left - 7
	vertices[7].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[7].color = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);

	unsigned int indices[] = 
	{
		0, 1, 2,
		0, 2, 3,

		1, 5, 6,
		1, 6, 2,

		5, 4, 7,
		5, 7, 6,

		4, 0, 3,
		4, 3, 7,

		4, 5, 1,
		4, 1, 0,

		3, 2, 6,
		3, 6, 7
	};

	m_vIndices.resize(ARRAYSIZE(indices));

	memcpy(m_vIndices.data(), indices, m_vIndices.size() * sizeof(unsigned int));
}

void Model::CreateBoxVertNormUV(DirectXCore* pCore)
{
	m_vIndices.clear();
	
	if(m_pVertices)
		delete[] m_pVertices;

	m_unNumVertices = 24;
	m_unVertexStride = sizeof(VertNormUV);

	VertNormUV* vertices = new VertNormUV[m_unNumVertices];
	m_pVertices = vertices;

#pragma region Front Face
	// Top Left - 0
	vertices[0].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[0].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertices[0].uv = XMFLOAT2(0.0f, 0.0f);

	// Top Right - 1
	vertices[1].position = XMFLOAT3(1.0f, 1.0f, -1.0f);
	vertices[1].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertices[1].uv = XMFLOAT2(1.0f, 0.0f);

	// Bottom Right - 2
	vertices[2].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[2].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertices[2].uv = XMFLOAT2(1.0f, 1.0f);

	// Bottom Left - 3
	vertices[3].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	vertices[3].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertices[3].uv = XMFLOAT2(0.0f, 1.0f);
#pragma endregion

#pragma region Right Face
	// Top Left - 4
	vertices[4].position = XMFLOAT3(1.0f, 1.0f, -1.0f);
	vertices[4].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertices[4].uv = XMFLOAT2(0.0f, 0.0f);

	// Top Right - 5
	vertices[5].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[5].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertices[5].uv = XMFLOAT2(1.0f, 0.0f);

	// Bottom Right - 6
	vertices[6].position = XMFLOAT3(1.0f, -1.0f, 1.0f);
	vertices[6].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertices[6].uv = XMFLOAT2(1.0f, 1.0f);

	// Bottom Left - 7
	vertices[7].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[7].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vertices[7].uv = XMFLOAT2(0.0f, 1.0f);
#pragma endregion

#pragma region Back Face
	// Top Left - 8
	vertices[8].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[8].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertices[8].uv = XMFLOAT2(0.0f, 0.0f);

	// Top Right - 9
	vertices[9].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vertices[9].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertices[9].uv = XMFLOAT2(1.0f, 0.0f);

	// Bottom Right - 10
	vertices[10].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[10].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertices[10].uv = XMFLOAT2(1.0f, 1.0f);

	// Bottom Left - 11
	vertices[11].position = XMFLOAT3(1.0f, -1.0f, 1.0f);
	vertices[11].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertices[11].uv = XMFLOAT2(0.0f, 1.0f);
#pragma endregion

#pragma region Left Face
	// Top Left - 12
	vertices[12].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vertices[12].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	vertices[12].uv = XMFLOAT2(0.0f, 0.0f);

	// Top Right - 13
	vertices[13].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[13].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	vertices[13].uv = XMFLOAT2(1.0f, 0.0f);

	// Bottom Right - 14
	vertices[14].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	vertices[14].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	vertices[14].uv = XMFLOAT2(1.0f, 1.0f);

	// Bottom Left - 15
	vertices[15].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[15].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	vertices[15].uv = XMFLOAT2(0.0f, 1.0f);
#pragma endregion

#pragma region Top Face
	// Top Left - 16
	vertices[16].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vertices[16].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertices[16].uv = XMFLOAT2(0.0f, 0.0f);

	// Top Right - 17
	vertices[17].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[17].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertices[17].uv = XMFLOAT2(1.0f, 0.0f);

	// Bottom Right - 18
	vertices[18].position = XMFLOAT3(1.0f, 1.0f, -1.0f);
	vertices[18].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertices[18].uv = XMFLOAT2(1.0f, 1.0f);

	// Bottom Left - 19
	vertices[19].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[19].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertices[19].uv = XMFLOAT2(0.0f, 1.0f);
#pragma endregion

#pragma region Bottom Face
	// Top Left - 20
	vertices[20].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	vertices[20].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
	vertices[20].uv = XMFLOAT2(0.0f, 0.0f);

	// Top Right - 21
	vertices[21].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[21].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
	vertices[21].uv = XMFLOAT2(1.0f, 0.0f);

	// Bottom Right - 22
	vertices[22].position = XMFLOAT3(1.0f, -1.0f, 1.0f);
	vertices[22].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
	vertices[22].uv = XMFLOAT2(1.0f, 1.0f);

	// Bottom Left - 23
	vertices[23].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[23].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
	vertices[23].uv = XMFLOAT2(0.0f, 1.0f);
#pragma endregion


	unsigned int indices[] = 
	{
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23
	};

	m_vIndices.resize(ARRAYSIZE(indices));

	memcpy(m_vIndices.data(), indices, m_vIndices.size() * sizeof(unsigned int));
}