#include "gtest/gtest.h"

#include "tests/test_vector_math.h"

//CORE_LIB includes
#include "core/containers/string.h"
#include "core/containers/vector.h"
#include "core/containers/list.h"
#include "core/containers/map.h"
#include "core/containers/stack.h"

//ALZ_RENDERER includes
#include "../../rendering_framework.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();
	system("pause");
	return result;
}