#include "tests/test_vector_math.h"

#include "gtest/gtest.h"

//ALZ_RENDERER includes
#include "../../rendering_framework.h"

using namespace ALZ_RENDERER;

//3D Vector--------------------------------------------------------------------------------------------
Vector3D<float> testVector3DCross(Vector3D<float> v1, Vector3D<float> v2)
{
	return Cross(v1, v2);
}

Vector3D<float> testOperatorMinusEquals(Vector3D<float> v1, Vector3D<float> v2)
{
	return v1 -= v2;
}

Vector3D<float> testOperatorPlusEquals(Vector3D<float> v1, Vector3D<float> v2)
{
	return v1 += v2;
}

//Test Vector3D Cross-Product
TEST(VectorMathTest, Vector3dTestCross) {
	EXPECT_EQ(Vector3D<float>(0.0f, 0.0f, 1.0f),
		testVector3DCross(Vector3D<float>(1.0f, 0.0f, 0.0f), Vector3D<float>(0.0f, 1.0f, 0.0f)));
}
//---------------------------------------

//Test Vector3D Cross-Product reverse order
TEST(VectorMathTest, Vector3dTestCrossReverse) {
	EXPECT_EQ(Vector3D<float>(0.0f, 0.0f, -1.0f),
		testVector3DCross(Vector3D<float>(0.0f, 1.0f, 0.0f), Vector3D<float>(1.0f, 0.0f, 0.0f)));
}
//---------------------------------------

//Test Vector3D Dot-Product of perpendicular vectors
TEST(VectorMathTest, Vector3dTestDotPerpendicular) {
	EXPECT_EQ(0.0f,
		Vector3D<float>(1.0f, 0.0f, 0.0f) * Vector3D<float>(0.0f, 1.0f, 0.0f));
}
//---------------------------------------

//Test Vector3D Dot-Product of parallel vectors
TEST(VectorMathTest, Vector3dTestDotParallel) {
	EXPECT_EQ(1.0f,
		Vector3D<float>(0.0f, 1.0f, 0.0f) * Vector3D<float>(0.0f, 1.0f, 0.0f));
}
//---------------------------------------

//Test Vector3D Length
TEST(VectorMathTest, Vector3dTestLength) {
	EXPECT_EQ(5.0f, Vector3D<float>(4.0f, 3.0f, 0.0f).length());
}
//---------------------------------------

//Test Vector3D Zero-Length
TEST(VectorMathTest, Vector3dTestLengthZero) {
	EXPECT_EQ(0.0f, Vector3D<float>(0.0f, 0.0f, 0.0f).length());
}
//---------------------------------------

//Test Vector3D Negate operator
TEST(VectorMathTest, Vector3dTestNegate) {
	EXPECT_EQ(Vector3D<float>(-1.0f, -3.0f, -5.0f), -Vector3D<float>(1.0f, 3.0f, 5.0f));
}
//---------------------------------------

//Test Vector3D Scale operator up-scale
TEST(VectorMathTest, Vector3dScaleUp) {
	EXPECT_EQ(Vector3D<float>(20.0f, 105.0f, 25.0f), 5.0f * Vector3D<float>(4.0f, 21.0f, 5.0f));
}
//---------------------------------------

//Test Vector3D Scale operator down-scale
TEST(VectorMathTest, Vector3dScaleDown) {
	EXPECT_EQ(Vector3D<float>(2.0f, 11.0f, 2.5f), 0.5f * Vector3D<float>(4.0f, 22.0f, 5.0f));
}
//---------------------------------------

//Test Vector3D + operator
TEST(VectorMathTest, Vector3dOperatorPlus) {
	EXPECT_EQ(Vector3D<float>(29.0f, 24.0f, 106.0f), 
		Vector3D<float>(4.0f, 13.0f, 7.0f) + Vector3D<float>(25.0f, 11.0f, 99.0f));
}
//---------------------------------------

//Test Vector3D - operator
TEST(VectorMathTest, Vector3dOperatorMinus) {
	EXPECT_EQ(Vector3D<float>(4.0f, 13.0f, 7.0f),
		Vector3D<float>(29.0f, 24.0f, 106.0f) - Vector3D<float>(25.0f, 11.0f, 99.0f));
}
//---------------------------------------

//Test Vector3D -= operator
TEST(VectorMathTest, Vector3dOperatorMinusEquals) {
	EXPECT_EQ(Vector3D<float>(-5.0f, 4.0f, 4.0f),
		testOperatorMinusEquals(Vector3D<float>(1.0f, 5.0f, 7.0f), Vector3D<float>(6.0f, 1.0f, 3.0f)));
}
//---------------------------------------

//Test Vector3D -= operator
TEST(VectorMathTest, Vector3dOperatorPlusEquals) {
	EXPECT_EQ(Vector3D<float>(9.0f, 4.0f, 20.8f),
		testOperatorPlusEquals(Vector3D<float>(5.0f, 1.0f, 15.6f), Vector3D<float>(4.0f, 3.0f, 5.2f)));
}
//---------------------------------------

//3D Vector-------------------------------------------------------------------------

//4D Vector--------------------------------------------------------------------------------------------
Vector4D<float> testVector4DCross(Vector4D<float> v1, Vector4D<float> v2)
{
	return Cross(v1, v2);
}

Vector4D<float> testOperatorMinusEquals(Vector4D<float> v1, Vector4D<float> v2)
{
	return v1 -= v2;
}

Vector4D<float> testOperatorPlusEquals(Vector4D<float> v1, Vector4D<float> v2)
{
	return v1 += v2;
}

//Test Vector4D Cross-Product
TEST(VectorMathTest, Vector4DTestCross) {
	EXPECT_EQ(Vector4D<float>(0.0f, 0.0f, 1.0f, 0.0f),
		testVector4DCross(Vector4D<float>(1.0f, 0.0f, 0.0f, 0.0f), Vector4D<float>(0.0f, 1.0f, 0.0f, 0.0f)));
}
//---------------------------------------

//Test Vector4D Cross-Product reverse order
TEST(VectorMathTest, Vector4DTestCrossReverse) {
	EXPECT_EQ(Vector4D<float>(0.0f, 0.0f, -1.0f, 0.0f),
		testVector4DCross(Vector4D<float>(0.0f, 1.0f, 0.0f, 0.0f), Vector4D<float>(1.0f, 0.0f, 0.0f, 0.0f)));
}
//---------------------------------------

//Test Vector4D Dot-Product of perpendicular vectors
TEST(VectorMathTest, Vector4DTestDotPerpendicular) {
	EXPECT_EQ(0.0f,
		Vector4D<float>(1.0f, 0.0f, 0.0f, 0.0f) * Vector4D<float>(0.0f, 1.0f, 0.0f, 0.0f));
}
//---------------------------------------

//Test Vector4D Dot-Product of parallel vectors
TEST(VectorMathTest, Vector4DTestDotParallel) {
	EXPECT_EQ(1.0f,
		Vector4D<float>(0.0f, 1.0f, 0.0f, 0.0f) * Vector4D<float>(0.0f, 1.0f, 0.0f, 0.0f));
}
//---------------------------------------

//Test Vector4D Length
TEST(VectorMathTest, Vector4DTestLength) {
	EXPECT_EQ(5.0f, Vector4D<float>(4.0f, 3.0f, 0.0f, 0.0f).length());
}
//---------------------------------------

//Test Vector4D Zero-Length
TEST(VectorMathTest, Vector4DTestLengthZero) {
	EXPECT_EQ(0.0f, Vector4D<float>(0.0f, 0.0f, 0.0f, 0.0f).length());
}
//---------------------------------------

//Test Vector4D Negate operator
TEST(VectorMathTest, Vector4DTestNegate) {
	EXPECT_EQ(Vector4D<float>(-1.0f, -3.0f, -5.0f, 0.0f), -Vector4D<float>(1.0f, 3.0f, 5.0f, 0.0f));
}
//---------------------------------------

//Test Vector4D Scale operator up-scale
TEST(VectorMathTest, Vector4DScaleUp) {
	EXPECT_EQ(Vector4D<float>(20.0f, 105.0f, 25.0f, 0.0f), 5.0f * Vector4D<float>(4.0f, 21.0f, 5.0f, 0.0f));
}
//---------------------------------------

//Test Vector4D Scale operator down-scale
TEST(VectorMathTest, Vector4DScaleDown) {
	EXPECT_EQ(Vector4D<float>(2.0f, 11.0f, 2.5f, 0.0f), 0.5f * Vector4D<float>(4.0f, 22.0f, 5.0f, 0.0f));
}
//---------------------------------------

//Test Vector4D + operator
TEST(VectorMathTest, Vector4DOperatorPlus) {
	EXPECT_EQ(Vector4D<float>(29.0f, 24.0f, 106.0f, 0.0f),
		Vector4D<float>(4.0f, 13.0f, 7.0f, 0.0f) + Vector4D<float>(25.0f, 11.0f, 99.0, 0.0f));
}
//---------------------------------------

//Test Vector4D - operator
TEST(VectorMathTest, Vector4DOperatorMinus) {
	EXPECT_EQ(Vector4D<float>(4.0f, 13.0f, 7.0f, 0.0f),
		Vector4D<float>(29.0f, 24.0f, 106.0f, 0.0f) - Vector4D<float>(25.0f, 11.0f, 99.0f, 0.0f));
}
//---------------------------------------

//Test Vector4D -= operator
TEST(VectorMathTest, Vector4DOperatorMinusEquals) {
	EXPECT_EQ(Vector4D<float>(-5.0f, 4.0f, 4.0f, 0.0f),
		testOperatorMinusEquals(Vector4D<float>(1.0f, 5.0f, 7.0f, 0.0f), Vector4D<float>(6.0f, 1.0f, 3.0f, 0.0f)));
}
//---------------------------------------

//Test Vector4D -= operator
TEST(VectorMathTest, Vector4DOperatorPlusEquals) {
	EXPECT_EQ(Vector4D<float>(9.0f, 4.0f, 20.8f, 0.0f),
		testOperatorPlusEquals(Vector4D<float>(5.0f, 1.0f, 15.6f, 0.0f), Vector4D<float>(4.0f, 3.0f, 5.2f, 0.0f)));
}
//---------------------------------------

//4D Vector-------------------------------------------------------------------------
