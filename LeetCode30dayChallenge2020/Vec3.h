/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Vec2.h																				  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once
#include "ChiliMath.h"
#include "Vec2.h"


class Vec3
{
public:
	Vec3() {}
	Vec3(float x, float y, float z)
		:
		x(x),
		y(y),
		z(z)
	{}
	Vec3(const Vec3& vect)
		:
		Vec3(vect.x, vect.y, vect.z)
	{}
	float LenSq() const
	{
		return sq(*this);
	}
	float Len() const
	{
		return (float)sqrt(LenSq());
	}
	Vec3& Normalize()
	{
		const float length = (float)Len();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}
	Vec3	GetNormalized() const
	{
		Vec3 norm = *this;
		norm.Normalize();
		return norm;
	}
	Vec3	operator-() const
	{
		return Vec3(-x, -y, -z);
	}
	Vec3& operator=(const Vec3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
	Vec3& operator+=(const Vec3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	Vec3& operator-=(const Vec3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	float operator*(const Vec3& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	Vec3 operator%(const Vec3& rhs) const
	{
		return 	{ this->y * rhs.z - this->z * rhs.y,
					this->z * rhs.x - this->x * rhs.z,
					this->x * rhs.y - this->y * rhs.x
		};
	}
	Vec3	operator+(const Vec3& rhs) const
	{
		return Vec3(*this) += rhs;
	}
	Vec3	operator-(const Vec3& rhs) const
	{
		return Vec3(*this) -= rhs;
	}
	Vec3& operator*=(const float& rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}
	Vec3	operator*(const float& rhs) const
	{
		return Vec3(*this) *= rhs;
	}
	Vec3& operator/=(const float& rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}
	Vec3 operator/(const float& rhs) const
	{
		return Vec3(*this) /= rhs;
	}
	bool operator==(const Vec3& rhs) const
	{
		return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z);
	}
	bool operator!=(const Vec3& rhs) const
	{
		return !(*this == rhs);
	}
	Vec3 InterpolateTo(const Vec3& dest, float alpha) const
	{
		/*return {
			x + (dest.x - x) * alpha,
			y + (dest.y - y) * alpha,
			z + (dest.z - z) * alpha
		};*/
		return *this + (dest - *this) * alpha;
	}
public:
	float x;
	float y;
	float z;
};

