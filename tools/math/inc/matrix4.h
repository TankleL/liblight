/* ****************************************************************************
matrix4.h
-------------------------------------------------------------------------------

Copyright (c) 2017, Tain L.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

**************************************************************************** */

#if !defined(LIGHT_MATHINC_MATRIX_H)
#define LIGHT_MATHINC_MATRIX_H

#include "my-prerequisites.h"
#include "vector3.h"
#include "point3.h"


namespace Light
{
	namespace Math
	{
		class Matrix4
		{
		public:
			Matrix4(decimal mm00 = 1.f, decimal mm01 = 0.f, decimal mm02 = 0.f, decimal mm03 = 0.f,
				decimal mm10 = 0.f, decimal mm11 = 1.f, decimal mm12 = 0.f, decimal mm13 = 0.f,
				decimal mm20 = 0.f, decimal mm21 = 0.f, decimal mm22 = 1.f, decimal mm23 = 0.f,
				decimal mm30 = 0.f, decimal mm31 = 0.f, decimal mm32 = 0.f, decimal mm33 = 1.f);
			Matrix4(const Matrix4& rhs);
			Matrix4(Matrix4&& rhs);

			Matrix4& operator = (const Matrix4& rhs);
			Matrix4& operator = (Matrix4&& rhs);
			bool operator == (const Matrix4& rhs) const;
			Matrix4 operator-() const;
			Matrix4 transpose() const;
			Matrix4& operator += (const Matrix4& rhs);
			Matrix4& operator -= (const Matrix4& rhs);
			Matrix4& operator *= (const Matrix4& rhs);
			Matrix4& operator *= (decimal times);

			union
			{
				decimal m_mat[4][4];
				struct
				{
					decimal m00, m01, m02, m03;
					decimal m10, m11, m12, m13;
					decimal m20, m21, m22, m23;
					decimal m30, m31, m32, m33;
				};
			};
		}; // class Matrix4

		inline Matrix4::Matrix4(decimal mm00, decimal mm01, decimal mm02, decimal mm03,
			decimal mm10, decimal mm11, decimal mm12, decimal mm13,
			decimal mm20, decimal mm21, decimal mm22, decimal mm23,
			decimal mm30, decimal mm31, decimal mm32, decimal mm33)
			: m00(mm00), m01(mm01), m02(mm02), m03(mm03)
			, m10(mm10), m11(mm11), m12(mm12), m13(mm13)
			, m20(mm20), m21(mm21), m22(mm22), m23(mm23)
			, m30(mm30), m31(mm31), m32(mm32), m33(mm33)
		{}

		inline Matrix4::Matrix4(const Matrix4& rhs)
			: m00(rhs.m00), m01(rhs.m01), m02(rhs.m02), m03(rhs.m03)
			, m10(rhs.m10), m11(rhs.m11), m12(rhs.m12), m13(rhs.m13)
			, m20(rhs.m20), m21(rhs.m21), m22(rhs.m22), m23(rhs.m23)
			, m30(rhs.m30), m31(rhs.m31), m32(rhs.m32), m33(rhs.m33)
		{}

		inline Matrix4::Matrix4(Matrix4&& rhs)
			: m00(std::move(rhs.m00)), m01(std::move(rhs.m01)), m02(std::move(rhs.m02)), m03(std::move(rhs.m03))
			, m10(std::move(rhs.m10)), m11(std::move(rhs.m11)), m12(std::move(rhs.m12)), m13(std::move(rhs.m13))
			, m20(std::move(rhs.m20)), m21(std::move(rhs.m21)), m22(std::move(rhs.m22)), m23(std::move(rhs.m23))
			, m30(std::move(rhs.m30)), m31(std::move(rhs.m31)), m32(std::move(rhs.m32)), m33(std::move(rhs.m33))
		{}

		inline Matrix4& Matrix4::operator=(const Matrix4& rhs)
		{
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					m_mat[i][j] = rhs.m_mat[i][j];
			return *this;
		}

		inline Matrix4& Matrix4::operator=(Matrix4&& rhs)
		{
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					m_mat[i][j] = std::move(rhs.m_mat[i][j]);
			return *this;
		}

		inline bool Matrix4::operator==(const Matrix4& rhs) const
		{
			return decimal_equal(m00, rhs.m00) && decimal_equal(m01, rhs.m01) && decimal_equal(m02, rhs.m02) && decimal_equal(m03, rhs.m03) &&
				decimal_equal(m10, rhs.m10) && decimal_equal(m11, rhs.m11) && decimal_equal(m12, rhs.m12) && decimal_equal(m13, rhs.m13) &&
				decimal_equal(m20, rhs.m20) && decimal_equal(m21, rhs.m21) && decimal_equal(m22, rhs.m22) && decimal_equal(m23, rhs.m23) &&
				decimal_equal(m30, rhs.m30) && decimal_equal(m31, rhs.m31) && decimal_equal(m32, rhs.m32) && decimal_equal(m33, rhs.m33);
		}

		inline Matrix4 Matrix4::operator-() const
		{
			Matrix4 res = *this;
			for (int i = 0; i<4; ++i)
				for (int j = 0; j<4; ++j)
					res.m_mat[i][j] = -m_mat[i][j];
			return res;
		}

		inline Matrix4 Matrix4::transpose() const
		{
			Matrix4 res;
			for (int i = 0; i<4; ++i)
				for (int j = 0; j<4; ++j)
					res.m_mat[j][i] = m_mat[i][j];
			return std::move(res);
		}

		inline Matrix4& Matrix4::operator += (const Matrix4& rhs)
		{
			for (int i = 0; i<4; ++i)
				for (int j = 0; j<4; ++j)
					m_mat[i][j] += rhs.m_mat[i][j];
			return *this;
		}

		inline Matrix4& Matrix4::operator -= (const Matrix4& rhs)
		{
			for (int i = 0; i<4; ++i)
				for (int j = 0; j<4; ++j)
					m_mat[i][j] -= rhs.m_mat[i][j];
			return *this;
		}

		inline Matrix4& Matrix4::operator *= (const Matrix4& rhs)
		{
			Matrix4 temp;
			for (int i = 0; i<4; ++i)
			{
				for (int j = 0; j<4; ++j)
				{
					temp.m_mat[i][j] = 0.f;
					for (int k = 0; k<4; ++k)
						temp.m_mat[i][j] += m_mat[i][k] * rhs.m_mat[k][j];
				}
			}
			*this = temp;
			return *this;
		}

		inline Matrix4& Matrix4::operator *= (decimal times)
		{
			for (int i = 0; i<4; ++i)
				for (int j = 0; j<4; ++j)
					m_mat[i][j] *= times;
			return *this;
		}

		inline Matrix4 operator+(Matrix4 const& m1, Matrix4 const& m2)
		{
			Matrix4 res = m1;
			return res += m2;
		}

		inline Matrix4 operator-(Matrix4 const& m1, Matrix4 const& m2)
		{
			Matrix4 res = m1;
			return res -= m2;
		}

		inline Matrix4 operator*(Matrix4 const& m1, Matrix4 const& m2)
		{
			Matrix4 res;
			for (int i = 0; i<4; ++i)
			{
				for (int j = 0; j<4; ++j)
				{
					res.m_mat[i][j] = 0.f;
					for (int k = 0; k<4; ++k)
						res.m_mat[i][j] += m1.m_mat[i][k] * m2.m_mat[k][j];
				}
			}
			return res;
		}

		inline Matrix4 operator*(const Matrix4& mat, decimal c)
		{
			Matrix4 res = mat;
			return res *= c;
		}

		inline Matrix4 operator*(decimal c, const Matrix4& mat)
		{
			Matrix4 res = mat;
			return res *= c;
		}

		inline Vector3 operator * (const Matrix4& mat, const Vector3& v)
		{
			Vector3 res;
			for (int i = 0; i<4; ++i)
			{
				res[i] = 0.f;
				for (int j = 0; j<4; ++j)
					res[i] += mat.m_mat[i][j] * v[j];
			}
			res.m_w = 0.0f;
			return res;
		}

		inline Vector3 operator* (const Vector3& v, const Matrix4& mat)
		{
			Vector3 res;
			for (int i = 0; i < 4; ++i)
			{
				res[i] = 0.0f;
				for (int j = 0; j < 4; ++j)
				{
					res[i] += mat.m_mat[i][j] * v[j];
				}
			}
			res.m_w = 0.0f;
			return res;
		}

		inline Point3 operator * (const Matrix4& mat, const Point3& p)
		{
			Point3 res;
			for (int i = 0; i<4; ++i)
			{
				res[i] = 0.f;
				for (int j = 0; j<4; ++j)
					res[i] += mat.m_mat[i][j] * p[j];
			}
			res *= res.m_w;
			res.m_w = 1.0f;
			return res;
		}

		inline Point3 operator*(const Point3& p, const Matrix4& mat)
		{
			Point3 res;
			for (int i = 0; i<4; ++i)
			{
				res[i] = 0.f;
				for (int j = 0; j<4; ++j)
					res[i] += mat.m_mat[i][j] * p[j];
			}
			res *= res.m_w;
			res.m_w = 1.0f;
			return res;
		}

		class Matrix4Utils
		{
		public:
			static inline void rotate_axis(Matrix4& out, const Vector3& axis, const decimal& theta)
			{
				Vector3	vec_axis(axis);
				vec_axis.normalize();

				const decimal&	u = vec_axis.m_x;
				const decimal&	v = vec_axis.m_y;
				const decimal&	w = vec_axis.m_z;

				out.m00 = cos(theta) + (u * u) * (1 - cos(theta));
				out.m10 = u * v * (1 - cos(theta)) + w * sin(theta);
				out.m20 = u * w * (1 - cos(theta)) - v * sin(theta);
				out.m30 = 0.0f;

				out.m01 = u * v * (1 - cos(theta)) - w * sin(theta);
				out.m11 = cos(theta) + v * v * (1 - cos(theta));
				out.m21 = w * v * (1 - cos(theta)) + u * sin(theta);
				out.m31 = 0.0f;

				out.m02 = u * w * (1 - cos(theta)) + v * sin(theta);
				out.m12 = v * w * (1 - cos(theta)) - u * sin(theta);
				out.m22 = cos(theta) + w * w * (1 - cos(theta));
				out.m32 = 0.0f;

				out.m03 = 0.0f;
				out.m13 = 0.0f;
				out.m23 = 0.0f;
				out.m33 = 1.0f;
			}

			static inline Matrix4 inverse(const Matrix4& m_mat)
			{
				int indxc[4], indxr[4];
				int ipiv[4] = { 0, 0, 0, 0 };
				decimal minv[4][4];
				memcpy(minv, m_mat.m_mat, 4 * 4 * sizeof(decimal));
				for (int i = 0; i < 4; i++) {
					int irow = -1, icol = -1;
					decimal big = 0.;
					// Choose pivot
					for (int j = 0; j < 4; j++) {
						if (ipiv[j] != 1) {
							for (int k = 0; k < 4; k++) {
								if (ipiv[k] == 0) {
									if (abs(minv[j][k]) >= big) {
										big = abs(minv[j][k]);
										irow = j;
										icol = k;
									}
								}
								else if (ipiv[k] > 1)
									return Matrix4();
							}
						}
					}
					++ipiv[icol];
					// Swap rows _irow_ and _icol_ for pivot
					if (irow != icol) {
						for (int k = 0; k < 4; ++k)
							std::swap(minv[irow][k], minv[icol][k]);
					}
					indxr[i] = irow;
					indxc[i] = icol;
					if (minv[icol][icol] == 0.)
						return Matrix4();

					// Set $m[icol][icol]$ to one by scaling row _icol_ appropriately
					decimal pivinv = 1.f / minv[icol][icol];
					minv[icol][icol] = 1.f;
					for (int j = 0; j < 4; j++)
						minv[icol][j] *= pivinv;

					// Subtract this row from others to zero out their columns
					for (int j = 0; j < 4; j++) {
						if (j != icol) {
							decimal save = minv[j][icol];
							minv[j][icol] = 0;
							for (int k = 0; k < 4; k++)
								minv[j][k] -= minv[icol][k] * save;
						}
					}
				}
				// Swap columns to reflect permutation
				for (int j = 3; j >= 0; j--) {
					if (indxr[j] != indxc[j]) {
						for (int k = 0; k < 4; k++)
							std::swap(minv[k][indxr[j]], minv[k][indxc[j]]);
					}
				}

				Matrix4 result;
				std::memcpy(result.m_mat, minv, 4 * 4 * sizeof(decimal));
				return result;
			}
		};
	} // namespace Math
} // namespace Spears

#endif // LIGHT_MATHINC_MATRIX_H