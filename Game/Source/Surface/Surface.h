//
//  Surface.h
//  OpenGL
//
//  Created by Alexander Sukharev on 29.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _SURFACE_H_
#define _SURFACE_H_

class Surface {

public:
	virtual ~Surface() {}

	virtual void SetVertexFlags(unsigned char flags = 0) = 0;

	virtual int GetVertexSize() = 0;
	virtual int GetVertexCount() = 0;

	virtual int GetTriangleIndexCount() = 0;
	virtual void GenerateVertices(float * vertices) const = 0;
	virtual void GenerateTriangleIndices(unsigned short * indices) const = 0;
};

#endif /* defined(_SURFACE_H_) */
