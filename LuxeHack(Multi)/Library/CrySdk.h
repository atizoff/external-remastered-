#pragma once
#include <windows.h>
#include <cmath>
#include <d3d9.h>
#include <vector>

#ifdef _DEBUG
#define ILINE _inline
#else
#define ILINE __forceinline
#endif
enum type_zero { ZERO };
enum type_min { VMIN };
enum type_max { VMAX };
enum type_identity { IDENTITY };
typedef signed char      int8;
typedef signed short     int16;
typedef signed int		 int32;
typedef signed __int64	 int64;
typedef unsigned char	 uint8;
typedef unsigned short	 uint16;
typedef unsigned int	 uint32;
typedef unsigned __int64 uint64;
typedef float f32;
typedef double f64;
typedef unsigned int EntityId;
ILINE f32 cry_fabsf(f32 x) { return fabsf(x); }
ILINE f32 cry_isqrtf(f32 x) { return 1.f / sqrtf(x); }
ILINE f64 isqrt_tpl(f64 op) { return 1.0 / sqrt(op); }
ILINE f32 isqrt_tpl(f32 op) { return cry_isqrtf(op); }
ILINE f64 fabs_tpl(f64 op) { return fabs(op); }
ILINE f32 fabs_tpl(f32 op) { return cry_fabsf(op); }
float isqrt_safe_tpl(float op) { return 1.0 / sqrt(op + DBL_MIN); }
#define assert(expression) ((void)0)
#define FloatU32(x)		 (*( (uint32*) &(x) ))
#define FloatU32ExpMask	 (0xFF << 23)
void cry_sincos(float angle, float* pSin, float* pCos) { *pSin = (sin(angle));  *pCos = (cos(angle)); }
void sincos(float angle, float* pSin, float* pCos) { cry_sincos(angle, pSin, pCos); }
f32 fZero = 0.000f;

struct Vec3
{
public:
	FLOAT x, y, z;
	Vec3(type_zero) : x(0), y(0), z(0) {}
	Vec3() { Vec3(0.f, 0.f, 0.f); }
	Vec3(FLOAT x, FLOAT y, FLOAT z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	FLOAT length() const { return sqrt(x*x + y * y + z * z); }
	FLOAT Distance(Vec3 &VecB)
	{
		Vec3 Out = *this - VecB;
		return sqrt(Out.x*Out.x + Out.y*Out.y + Out.z*Out.z);
	}
	Vec3 PZD(Vec3 &VecB)
	{
		Vec3 Out = *this - VecB;
		return Out / sqrt(Out.x*Out.x + Out.y*Out.y + Out.z*Out.z);
	}
	VOID Set(FLOAT x, FLOAT y, FLOAT z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void Normalize()
	{
		assert(this->IsValid());
		float fInvLen = isqrt_safe_tpl(x*x + y * y + z * z);
		x *= fInvLen; y *= fInvLen; z *= fInvLen;
	}
	bool NumberValid(const float& x)
	{
		uint32 i = FloatU32(x);
		uint32 expmask = FloatU32ExpMask;
		uint32 iexp = i & expmask;
		bool invalid = (iexp == expmask);
		if (invalid)
		{
			union f32_u
			{
				uint32 uintVal;
				f32 floatVal;
			};
			f32_u u;	u.uintVal = 0x7F800001;
			float fpe = u.floatVal;
			(void)fpe;
		}
		return !invalid;
	}
	bool IsValid()
	{
		if (!NumberValid(x)) return false;
		if (!NumberValid(y)) return false;
		if (!NumberValid(z)) return false;
		return true;
	}
	Vec3& normalize()
	{
		FLOAT len2 = x * x + y * y + z * z;
		if (len2 > 1e-20f)
		{
			FLOAT rlen = (float)1.0 / sqrt(len2);
			x *= rlen; y *= rlen; z *= rlen;
		}
		else { x = 0; y = 0; z = 1; }
		return *this;
	}
	Vec3& FastNormalize()
	{
		FLOAT l = length();
		l = 1.f / l;
		this->x *= l;
		this->y *= l;
		this->z *= l;
		return *this;
	}
	Vec3 GetNormalized() const
	{
		float fInvLen = isqrt_safe_tpl(x*x + y * y + z * z);
		Vec3 out = *this;
		out.x *= fInvLen;
		out.y *= fInvLen;
		out.z *= fInvLen;
		return out;
	}
	Vec3 GetNormalizedSafe(const struct Vec3& safe) const
	{
		float fLen2 = x * x + y * y + z * z;
		if (fLen2 > 0.0f)
		{
			float fInvLen = isqrt_tpl(fLen2);
			Vec3 out;
			out.x = safe.x*fInvLen;
			out.y = safe.y*fInvLen;
			out.z = safe.z*fInvLen;
			return out;
		}
		else { return safe; }
	}
	FLOAT len2() { return x * x + y * y + z * z; }
	FLOAT len() { return sqrt(x*x + y * y + z * z); }
	Vec3 operator / (FLOAT fValue) { return Vec3(x / fValue, y / fValue, z / fValue); }
	Vec3& operator /= (FLOAT fValue)
	{
		*this = *this / fValue;
		return *this;
	}
	Vec3 operator / (FLOAT fValue) const
	{
		Vec3 vOut;
		vOut.x = this->x / fValue;
		vOut.y = this->y / fValue;
		vOut.z = this->z / fValue;
		return vOut;
	}
	BOOL operator != (Vec3 &vec) { return !(vec.x == x && vec.y == y && vec.z == z); }
	BOOL operator == (Vec3 &vec) { return (vec.x == x && vec.y == y && vec.z == z); }
	Vec3 operator /  (Vec3 &vec) const { return Vec3(vec.x / x, vec.y / y, vec.z / z); }
	Vec3 operator +  (Vec3 &vec) const { return Vec3(vec.x + x, vec.y + y, vec.z + z); }
	Vec3 operator *  (Vec3 &vec) const { return Vec3(vec.x * x, vec.y * y, vec.z * z); }
	Vec3 operator *  (FLOAT fValue) const { return Vec3(x*fValue, y*fValue, z*fValue); }
	Vec3 operator -  (Vec3 &vec) const { return Vec3(vec.x - x, vec.y - y, vec.z - z); }
	VOID CheckMin(Vec3 &other)
	{
		x = min(other.x, x);
		y = min(other.y, y);
		z = min(other.z, z);
	}
	VOID CheckMax(Vec3 &other)
	{
		x = max(other.x, x);
		y = max(other.y, y);
		z = max(other.z, z);
	}
	Vec3(f32 f) : x(f), y(f), z(f) { assert(this->IsValid()); }
};
struct Vec4 
{
	Vec4() {}
	f32 x, y, z, w;
};
struct Matrix3x3
{
	Matrix3x3(const Vec3& vx, const Vec3& vy, const Vec3& vz)
	{
		m00 = (vx.x);
		m01 = (vy.x);
		m02 = (vz.x);

		m10 = (vx.y);
		m11 = (vy.y);
		m12 = (vz.y);

		m20 = (vx.z);
		m21 = (vy.z);
		m22 = (vz.z);
	}
	Matrix3x3() { m00 = m01 = m02 = m10 = m11 = m12 = m20 = m21 = m22 = 0.f; };
	void SetRotationVDir(const Vec3& vdir)
	{
		m00 = 1;
		m01 = 0;
		m02 = 0;
		m10 = 0;
		m11 = 0;
		m12 = -vdir.z;
		m20 = 0;
		m21 = vdir.z;
		m22 = 0;
		float l = sqrt(vdir.x*vdir.x + vdir.y*vdir.y);
		if (l > 0.0001)
		{
			float xl = -vdir.x / l;
			float yl = vdir.y / l;

			m00 = (yl);
			m01 = (vdir.x);
			m02 = (xl*vdir.z);

			m10 = (xl);
			m11 = (vdir.y);
			m12 = (-vdir.z*yl);

			m20 = 0;
			m21 = (vdir.z);
			m22 = (l);
		}
	}
	Vec3 operator *(Vec3& v) { return Vec3(v.x*m00 + v.y*m01 + v.z*m02, v.x*m10 + v.y*m11 + v.z*m12, v.x*m20 + v.y*m21 + v.z*m22); }
	float m00, m01, m02;
	float m10, m11, m12;
	float m20, m21, m22;
};
struct Quat
{
public:
	Vec3 v;
	FLOAT w;
	Quat(const Matrix3x3& m)
	{
		float s, p, tr = m.m00 + m.m11 + m.m22;
		w = 1, v.x = 0, v.y = 0, v.z = 0;

		if (tr>0)
			s = (float)sqrt(tr + 1.0f), p = 0.5f / s, w = s * 0.5f, v.x = (m.m21 - m.m12)*p, v.y = (m.m02 - m.m20)*p, v.z = (m.m10 - m.m01)*p;
		else if ((m.m00 >= m.m11) && (m.m00 >= m.m22))
			s = (float)sqrt(m.m00 - m.m11 - m.m22 + 1.0f), p = 0.5f / s, w = (m.m21 - m.m12)*p, v.x = s * 0.5f, v.y = (m.m10 + m.m01)*p, v.z = (m.m20 + m.m02)*p;
		else if ((m.m11 >= m.m00) && (m.m11 >= m.m22))
			s = (float)sqrt(m.m11 - m.m22 - m.m00 + 1.0f), p = 0.5f / s, w = (m.m02 - m.m20)*p, v.x = (m.m01 + m.m10)*p, v.y = s * 0.5f, v.z = (m.m21 + m.m12)*p;
		else if ((m.m22 >= m.m00) && (m.m22 >= m.m11))
			s = (float)sqrt(m.m22 - m.m00 - m.m11 + 1.0f), p = 0.5f / s, w = (m.m10 - m.m01)*p, v.x = (m.m02 + m.m20)*p, v.y = (m.m12 + m.m21)*p, v.z = s * 0.5f;
	}
	Quat() {}
	friend float operator | (const Quat& q, const Quat& p) { return (q.v.x*p.v.x + q.v.y*p.v.y + q.v.z*p.v.z + q.w*p.w); }
	friend Quat  operator - (const Quat &q, const Quat &p)
	{
		Quat ret;
		ret.w = q.w - p.w;

		ret.v.x = q.v.x - p.v.x;
		ret.v.y = q.v.y - p.v.y;
		ret.v.z = q.v.z - p.v.z;

		return ret;
	}
	void        SetRotationVDir(const Vec3& vdir)
	{
		w = (0.70710676908493042f);
		v.x = (vdir.z*0.70710676908493042f);
		v.y = (0.0f);
		v.z = (0.0f);

		float l = sqrt(vdir.x*vdir.x + vdir.y*vdir.y);

		if (l > (0.00001))
		{
			Vec3 hv;

			hv.x = vdir.x / l;
			hv.y = vdir.y / l + 1.0f;
			hv.z = l + 1.0f;

			float r = sqrt(hv.x*hv.x + hv.y*hv.y);
			float s = sqrt(hv.z*hv.z + vdir.z*vdir.z);
			float hacos0 = 0.0;
			float hasin0 = -1.0;

			if (r > (0.00001)) { hacos0 = hv.y / r; hasin0 = -hv.x / r; }

			float hacos1 = hv.z / s;
			float hasin1 = vdir.z / s;

			w = (hacos0*hacos1);
			v.x = (hacos0*hasin1);
			v.y = (hasin0*hasin1);
			v.z = (hasin0*hacos1);
		}
	}
	static Quat CreateRotationVDir(const Vec3& vdir)
	{
		Quat q;
		q.SetRotationVDir(vdir);
		return q;
	}
	void Normalize(void)
	{
		float d = sqrt(w*w + v.x*v.x + v.y*v.y + v.z*v.z);

		w *= d;

		v.x *= d;
		v.y *= d;
		v.z *= d;
	}
	void SetNlerp(const Quat &p, const Quat &tq, float t)
	{
		Quat q = tq;

		assert(p.IsValid());
		assert(q.IsValid());

		if ((p | q) < 0)
		{
			float qx = -q.v.x;
			float qy = -q.v.y;
			float qz = -q.v.z;

			q.v.x = qx;
			q.v.y = qy;
			q.v.z = qz;
		}

		v.x = p.v.x*(1.0f - t) + q.v.x*t;
		v.y = p.v.y*(1.0f - t) + q.v.y*t;
		v.z = p.v.z*(1.0f - t) + q.v.z*t;

		w = p.w  *(1.0f - t) + q.w  *t;

		Normalize();
	}
	void SetSlerp(const Quat &tp, const Quat &tq, float t)
	{
		assert(tp.IsValid());
		Quat p, q;
		p = tp;
		q = tq;
		Quat q2;
		float cosine = (p | q);
		if (cosine < 0.0f)
		{
			float qx = -q.v.x;
			float qy = -q.v.y;
			float qz = -q.v.z;

			cosine = -cosine;

			q.v.x = qx;
			q.v.y = qy;
			q.v.z = qz;
		}
		if (cosine > 0.9999f)
		{
			SetNlerp(p, q, t);
			return;
		}
		q2.w = q.w - p.w*cosine;
		q2.v.x = q.v.x - p.v.x*cosine;
		q2.v.y = q.v.y - p.v.y*cosine;
		q2.v.z = q.v.z - p.v.z*cosine;
		float sine = sqrt(q2 | q2);
		float s, c;
		sincos(atan2(sine, cosine)*t, &s, &c);
		w = (p.w*c + q2.w*s / sine);
		v.x = (p.v.x*c + q2.v.x*s / sine);
		v.y = (p.v.y*c + q2.v.y*s / sine);
		v.z = (p.v.z*c + q2.v.z*s / sine);
	}
	static Quat CreateSlerp(const Quat &p, const Quat &tq, float t)
	{
		Quat d;
		d.SetSlerp(p, tq, t);
		return d;
	}
};
struct QuatT
{
public:
	Quat q;
	Vec3 t;
};
struct Matrix3x4
{
public:
	FLOAT m00, m01, m02, m03;
	FLOAT m10, m11, m12, m13;
	FLOAT m20, m21, m22, m23;
	Vec3 GetTranslation() { Vec3 mf; mf.x = m03; mf.y = m13; mf.z = m23; return Vec3(mf); }
	Vec3 GetTranslation_() { Vec3 mf; mf.x = m03; mf.y = m13; mf.z = m23; return mf; }
	inline Vec3 GetTranslationD3D() const { return Vec3(m03, m13, m23); }
	inline Vec3 GetColumn0() const { return Vec3(m00, m10, m20); }
	inline Vec3 GetColumn1() const { return Vec3(m01, m11, m21); }
	BOOL NumberValid(FLOAT &_x)
	{
		int i = FloatU32(_x);
		int expmask = FloatU32ExpMask;
		int iexp = i & expmask;
		bool invalid = (iexp == expmask);

		if (invalid)
		{
			int i = 0x7F800001;
			float fpe = *(float*)(&i);
		}

		return !invalid;
	}
	Matrix3x4 SetTranslation(Vec3 NewTranslation) { m03 = NewTranslation.x; m13 = NewTranslation.y; m23 = NewTranslation.z; return *this; }
	Matrix3x4() {}
	Matrix3x4(QuatT& q)
	{
		assert(q.q.IsValid());
		Vec3 v2;
		v2.x = (q.q.v.x) + (q.q.v.x);
		float xx = 1 - v2.x*q.q.v.x; float yy = v2.y*q.q.v.y; float xw = v2.x*q.q.w;
		float xy = v2.y*q.q.v.x;   float yz = v2.z*q.q.v.y; float  yw = v2.y*q.q.w;
		float xz = v2.z*q.q.v.x;   float zz = v2.z*q.q.v.z; float  zw = v2.z*q.q.w;
		m00 = float(1 - yy - zz);     m01 = float(xy - zw);     m02 = float(xz + yw);   m03 = float(q.t.x);
		m10 = float(xy + zw);      m11 = float(xx - zz);     m12 = float(yz - xw);   m13 = float(q.t.y);
		m20 = float(xz - yw);      m21 = float(yz + xw);     m22 = float(xx - yy);   m23 = float(q.t.z);
	}
	bool IsValid()
	{
		if (!NumberValid(m00)) return false;	if (!NumberValid(m01)) return false;	if (!NumberValid(m02)) return false;	if (!NumberValid(m03)) return false;
		if (!NumberValid(m10)) return false;	if (!NumberValid(m11)) return false;	if (!NumberValid(m12)) return false;	if (!NumberValid(m13)) return false;
		if (!NumberValid(m20)) return false;	if (!NumberValid(m21)) return false;	if (!NumberValid(m22)) return false;	if (!NumberValid(m23)) return false;
		return true;
	}
	friend Matrix3x4 operator * (Matrix3x4& l, Matrix3x4& r)
	{
		assert(l.IsValid());
		assert(r.IsValid());
		Matrix3x4 m = r;
		m.m00 = l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20;
		m.m10 = l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20;
		m.m20 = l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20;
		m.m01 = l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21;
		m.m11 = l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21;
		m.m21 = l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21;
		m.m02 = l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22;
		m.m12 = l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22;
		m.m22 = l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22;
		m.m03 = l.m00*r.m03 + l.m01*r.m13 + l.m02*r.m23 + l.m03;
		m.m13 = l.m10*r.m03 + l.m11*r.m13 + l.m12*r.m23 + l.m13;
		m.m23 = l.m20*r.m03 + l.m21*r.m13 + l.m22*r.m23 + l.m23;
		return m;
	}
	Vec3 operator *(Vec3& p)
	{
		Vec3 tp;
		tp.x = m00 * p.x + m01 * p.y + m02 * p.z + m03;
		tp.y = m10 * p.x + m11 * p.y + m12 * p.z + m13;
		tp.z = m20 * p.x + m21 * p.y + m22 * p.z + m23;
		return	tp;
	}
};
template<typename F> struct Matrix44_tpl 
{
	F m00, m01, m02, m03;
	F m10, m11, m12, m13;
	F m20, m21, m22, m23;
	F m30, m31, m32, m33;

	ILINE Matrix44_tpl() {};
	ILINE void SetZero() {
		m00 = 0;
		m01 = 0;
		m02 = 0;
		m03 = 0;
		m10 = 0;
		m11 = 0;
		m12 = 0;
		m13 = 0;
		m20 = 0;
		m21 = 0;
		m22 = 0;
		m23 = 0;
		m30 = 0;
		m31 = 0;
		m32 = 0;
		m33 = 0;
	}
	ILINE Matrix44_tpl(type_zero) { SetZero(); }

	ILINE void SetIdentity()
	{
		m00 = 1;
		m01 = 0;
		m02 = 0;
		m03 = 0;
		m10 = 0;
		m11 = 1;
		m12 = 0;
		m13 = 0;
		m20 = 0;
		m21 = 0;
		m22 = 1;
		m23 = 0;
		m30 = 0;
		m31 = 0;
		m32 = 0;
		m33 = 1;
	}
	ILINE Matrix44_tpl(type_identity) { SetIdentity(); }
};

#define CRY_ALIGN(bytes) __declspec(align(bytes))
typedef Matrix44_tpl<f32>		Matrix44;
typedef CRY_ALIGN(16) Matrix44_tpl<f32> Matrix44A;

struct AABB
{
	Vec3 min;
	Vec3 max;
	BOOL IsReset() { return min.x > max.x; }
	VOID Reset() { min = Vec3(1e35f);	max = Vec3(-1e35f); }
	VOID SetTransformedAABB(Matrix3x4& m34, AABB& aabb)
	{
		if (aabb.IsReset()) Reset();
		else
		{
			Matrix3x3 m33;
			m33.m00 = fabs_tpl(m34.m00);
			m33.m01 = fabs_tpl(m34.m01);
			m33.m02 = fabs_tpl(m34.m02);
			m33.m10 = fabs_tpl(m34.m10);
			m33.m11 = fabs_tpl(m34.m11);
			m33.m12 = fabs_tpl(m34.m12);
			m33.m20 = fabs_tpl(m34.m20);
			m33.m21 = fabs_tpl(m34.m21);
			m33.m22 = fabs_tpl(m34.m22);

			Vec3 sz = m33 * ((aabb.max - aabb.min)*0.5f);
			Vec3 pos = m34 * ((aabb.max + aabb.min)*0.5f);
			min = pos - sz;
			max = pos + sz;
		}
	}
};

#define RBPF_REVERSE_DEPTH (1 << 27)
inline void mathVec4Transform(f32 out[4], const f32 m[16], const f32 in[4])
{
#define M(row, col) m[col * 4 + row]
	out[0] = M(0, 0) * in[0] + M(0, 1) * in[1] + M(0, 2) * in[2] + M(0, 3) * in[3];
	out[1] = M(1, 0) * in[0] + M(1, 1) * in[1] + M(1, 2) * in[2] + M(1, 3) * in[3];
	out[2] = M(2, 0) * in[0] + M(2, 1) * in[1] + M(2, 2) * in[2] + M(2, 3) * in[3];
	out[3] = M(3, 0) * in[0] + M(3, 1) * in[1] + M(3, 2) * in[2] + M(3, 3) * in[3];
#undef M
}

ILINE f32 __mathVec3Project(Vec3* pvWin, const Vec3* pvObj, const int32 pViewport[4], const Matrix44* pProjection, const Matrix44* pView, const Matrix44* pWorld)
{
	Vec4 in, out;
	in.x = pvObj->x;
	in.y = pvObj->y;
	in.z = pvObj->z;
	in.w = 1.0f;
	mathVec4Transform((f32*)&out, (f32*)pWorld, (f32*)&in);
	mathVec4Transform((f32*)&in, (f32*)pView, (f32*)&out);
	mathVec4Transform((f32*)&out, (f32*)pProjection, (f32*)&in);
	if (out.w == 0.0f) return 0.f;
	out.x /= out.w;
	out.y /= out.w;
	out.z /= out.w;
	pvWin->x = pViewport[0] + (1 + out.x) * pViewport[2] / 2;
	pvWin->y = pViewport[1] + (1 - out.y) * pViewport[3] / 2;
	float fViewportMinZ = 0, fViewportMaxZ = 1.0f;
	pvWin->z = fViewportMinZ + out.z * (fViewportMaxZ - fViewportMinZ);
	return out.w;
}