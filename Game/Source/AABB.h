//
//  AABB.h
//  Asteroids
//
//  Created by Alexander Sukharev on 18.06.13.
//  Copyright (c) 2013 Alexander Sukharev. All rights reserved.
//

#ifndef _AABB_HPP
#define _AABB_HPP

#include "Vector.h"

class cdAABB
{
public:
    Vector<float> _P, _E; // pos and size
    float _R;

    cdAABB();
    cdAABB(float *vertices, int count, int vertexSize, Vector<float> scale);
	~cdAABB();

    const bool OverlapsAABB(const cdAABB &aabb) const;
//    const BOOL OverlapsOBB(const cdOBB &obb) const;
    const bool OverlapsSphere(const cdAABB &aabb) const;
//    const BOOL OverlapsLineSegment( const mVector &mid,
//                                   const mVector &dir,
//                                   const Scalar hl) const;
};

#endif /* defined(_AABB_HPP) */
