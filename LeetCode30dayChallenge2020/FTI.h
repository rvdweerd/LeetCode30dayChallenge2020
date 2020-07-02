#pragma once
#include "Vec3.h"
#include <utility>
#include <cassert>

namespace FTI
{
	struct coord
	{
		float x, y, z;
	};
	template <typename T> int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}
	/*std::pair<Vec3, Vec3> TrianglesIntersect_(coord v1_0, coord v1_1, coord v1_2, coord v2_0, coord v2_1, coord v2_2)
	{
		return TrianglesIntersect_(
			Vec3(v1_0.x, v1_0.x, v1_0.z),
			Vec3(v1_1.x, v1_1.x, v1_1.z), 
			Vec3(v1_2.x, v1_2.x, v1_2.z), 
			Vec3(v2_0.x, v2_0.x, v2_0.z), 
			Vec3(v2_1.x, v2_1.x, v2_1.z), 
			Vec3(v2_2.x, v2_1.x, v2_2.z) );
	}*/
	std::pair<Vec3, Vec3> TrianglesIntersect_(Vec3 v1_0, Vec3 v1_1, Vec3 v1_2, Vec3 v2_0, Vec3 v2_1, Vec3 v2_2)
	{
		// Plane equation for Plane2
		Vec3 N2 = (v2_1 - v2_0) % (v2_2 - v2_0);
		//N2 /= N2.Len();
		float d2 = -N2 * v2_0;

		// Plane equation for Plane1
		Vec3 N1 = (v1_1 - v1_0) % (v1_2 - v1_0);
		//N1 /= N1.Len();
		float d1 = -N1 * v1_0;

		// signed distances from T1 vertices to Plane2
		float d_v1_0 = N2 * v1_0 + d2;
		float d_v1_1 = N2 * v1_1 + d2;
		float d_v1_2 = N2 * v1_2 + d2;

		// Test: triangle 1 is coplanar
		//assert(!(d_v1_0 == 0 && d_v1_1 == 0 && d_v1_2 == 0));
		if ((d_v1_0 == 0 && d_v1_1 == 0 && d_v1_2 == 0)) return { { 0,0,0 }, { 0,0,0 } };

		// Test: triangle 1 is not fully on 1 side of P2
		bool NoT1VertexOnPlane2 = (d_v1_0 != 0 && d_v1_1 != 0 && d_v1_2 != 0);
		bool T1DistancesHaveSameSign = (d_v1_0 > 0 && d_v1_1 > 0 && d_v1_2 > 0) || (d_v1_0 < 0 && d_v1_1 < 0 && d_v1_2 < 0);
		//assert(!(NoT1VertexOnPlane2 && T1DistancesHaveSameSign));
		if (NoT1VertexOnPlane2 && T1DistancesHaveSameSign) return { { 0,0,0 }, { 0,0,0 } };

		// Ensure that v1_1 is solitary (two other vertices are on other side of T2)
		if (sgn(d_v1_0) == sgn(d_v1_1))
		{
			std::swap(d_v1_1, d_v1_2);
			//std::swap(v1_0, v1_2); NEED TO IMPLEMENT MOVE CONSTRUCTOR FOR Vec3 FOR THIS TO WORK
			Vec3 tmp = v1_1;
			v1_1 = v1_2;
			v1_2 = tmp;

			// Plane equation for Plane2
			N2 = (v2_1 - v2_0) % (v2_2 - v2_0);
			//N2 /= N2.Len();
			d2 = -N2 * v2_0;
			// Plane equation for Plane1
			N1 = (v1_1 - v1_0) % (v1_2 - v1_0);
			//N1 /= N1.Len();
			d1 = -N1 * v1_0;
			// signed distances from T1 vertices to Plane2
			//d_v1_0 = N2 * v1_0 + d2;
			//d_v1_1 = N2 * v1_1 + d2;
			//d_v1_2 = N2 * v1_2 + d2;
		}
		else if (sgn(d_v1_2) == sgn(d_v1_1))
		{
			std::swap(d_v1_1, d_v1_0);
			Vec3 tmp = v1_0;
			v1_0 = v1_1;
			v1_1 = tmp;

			// Plane equation for Plane2
			N2 = (v2_1 - v2_0) % (v2_2 - v2_0);
			//N2 /= N2.Len();
			d2 = -N2 * v2_0;
			// Plane equation for Plane1
			N1 = (v1_1 - v1_0) % (v1_2 - v1_0);
			//N1 /= N1.Len();
			d1 = -N1 * v1_0;
			// signed distances from T1 vertices to Plane2
			d_v1_0 = N2 * v1_0 + d2;
			d_v1_1 = N2 * v1_1 + d2;
			d_v1_2 = N2 * v1_2 + d2;
		}

		// Intersection line L = O + t*D (O = any point on line, D = direction), this represents the nullspace Ax=0)
		Vec3 D = N1 % N2;
		D /= D.Len();
		// Particular point on line (Ax=b, particular solution)
		// Find largest entry of D
		Vec3 O;
		if (abs(D.x) >= abs(D.y) && abs(D.x) >= abs(D.z)) // D.x largest component
		{
			float a = N1.y, b = N1.z;
			float c = N2.y, d = N2.z;
			float det = 1 / (a * d - b * c);
			float O_y = det * (d * (-d1) - b * (-d2));
			float O_z = det * (-c * (-d1) + a * (-d2));
			O = { 0,O_y,O_z };
		}
		else if (abs(D.y) >= abs(D.x) && abs(D.y) >= abs(D.z)) // D.y largest component
		{
			float a = N1.x, b = N1.z;
			float c = N2.x, d = N2.z;
			float det = 1 / (a * d - b * c);
			float O_x = det * (d * (-d1) - b * (-d2));
			float O_z = det * (-c * (-d1) + a * (-d2));
			O = { O_x,0,O_z };
		}
		else // D.z largest component
		{
			float a = N1.x, b = N1.y;
			float c = N2.x, d = N2.y;
			float det = 1 / (a * d - b * c);
			float O_x = det * (d * (-d1) - b * (-d2));
			float O_y = det * (-c * (-d1) + a * (-d2));
			O = { O_x,O_y,0 };
		}
		assert(N1 * (O + D * 20) + d1 < 0.0001f);
		assert(N2 * (O + D * 10) + d2 < 0.0001f);

		// Project vertices of T1 onto Intersection Line L
		Vec3 p_v1_0 = D * (D * (v1_0 - O)) / (D * D) + O;
		Vec3 p_v1_1 = D * (D * (v1_1 - O)) / (D * D) + O;
		Vec3 p_v1_2 = D * (D * (v1_2 - O)) / (D * D) + O;

		// Interpolation to find t1
		//float S = abs((p_v1_1 - p_v1_0).Len());
		float a = abs((p_v1_0 - v1_0).Len());
		float b = abs((p_v1_1 - v1_1).Len());
		float p = a / (b + a);
		//Vec3 t1 = p_v1_1 + (p_v1_0 - p_v1_1) * p;
		//Vec3 t1 = p_v1_0 + (p_v1_1 - p_v1_0) * p;
		//Vec3 t1 = p_v1_0 + (p_v1_1 - p_v1_0) * p;
		Vec3 t1 = p_v1_0 + (p_v1_1 - p_v1_0) * (d_v1_0 / (d_v1_0 - d_v1_1));

		// Interpolation to find t2
		//S = abs((p_v1_1 - p_v1_2).Len());
		a = abs((p_v1_2 - v1_2).Len());
		b = abs((p_v1_1 - v1_1).Len());
		p = a / (b + a);

		//Vec3 t2 = p_v1_2 + (p_v1_1 - p_v1_2) * p;
		//Vec3 t2 = p_v1_2 + (p_v1_1 - p_v1_2) * p ;
		Vec3 t2 = p_v1_2 + (p_v1_1 - p_v1_2) * (d_v1_2 / (d_v1_2 - d_v1_1));
		return {t1,t2};
	}
}