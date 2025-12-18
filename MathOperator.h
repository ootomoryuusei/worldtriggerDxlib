#pragma once
#include<DirectXMath.h>

using namespace DirectX;

//XMFLOAT2 
inline XMFLOAT2 operator+ (const XMFLOAT2& a, const XMFLOAT2& b) {
	return XMFLOAT2(a.x + b.x, a.y + b.y);
}

inline XMFLOAT2 operator -(const XMFLOAT2& a, const XMFLOAT2& b) {
	return XMFLOAT2(a.x - b.x, a.y - b.y);
}

inline XMFLOAT2 operator /(const XMFLOAT2& a, const float b) {
	return XMFLOAT2(a.x / b, a.y / b);
}

//XMFLOAT3
inline XMFLOAT3 operator +(const XMFLOAT3& a, const XMFLOAT3& b) {
	return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline XMFLOAT3 operator -(const XMFLOAT3& a, const XMFLOAT3& b) {
	return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline XMFLOAT3 operator *(const XMFLOAT3& a, const XMFLOAT3& b) {
	return XMFLOAT3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline XMFLOAT3 operator /(const XMFLOAT3& a, const XMFLOAT3& b) {
	return XMFLOAT3(a.x / b.x, a.y / b.y, a.z / b.z);
}

inline bool operator ==(const XMFLOAT3& a, const XMFLOAT3& b) {
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}

inline XMFLOAT3 operator +(const XMFLOAT3& a, const float& b) {
	return XMFLOAT3(a.x + b, a.y + b, a.z + b);
}

inline XMFLOAT3 operator -(const XMFLOAT3& a, const float& b) {
	return XMFLOAT3(a.x - b, a.y - b, a.z - b);
}

inline XMFLOAT3 operator *(const XMFLOAT3& a, const float& b) {
	return XMFLOAT3(a.x * b, a.y * b, a.z * b);
}

inline XMFLOAT3 operator /(const XMFLOAT3 & a, const float& b) {
	return XMFLOAT3(a.x / b, a.y / b, a.z / b);
}