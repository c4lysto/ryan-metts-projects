#ifndef MODEL_H
#define MODEL_H

#include <vector>
using std::vector;

class DirectXCore;

class Model
{
private:
	void* m_pVertices;
	unsigned int m_unNumVertices;
	unsigned int m_unVertexStride;
	vector<unsigned int> m_vIndices;

public:
	Model(void);
	~Model(void);

	void Render(DirectXCore* pCore);

	void* GetVertices() const {return m_pVertices;}
	const vector<unsigned int>& GetIndices() const {return m_vIndices;}
	unsigned int GetNumVertices() const {return m_unNumVertices;}
	unsigned int GetNumIndices() const {return m_vIndices.size();}
	unsigned int GetVertexStride() const {return m_unVertexStride;}

	void CreateBoxVertClr(DirectXCore* pCore);
	void CreateBoxVertNormUV(DirectXCore* pCore);
};

#endif