#include<gtest/gtest.h>
#include "cmd.h"

Dictionary dictionary;

TEST(ISVALID, ISVALIDBOOL){
	EXPECT_EQ(true, dictionary.isNotValid(true));
}

TEST(LOFAS, LOFASZ) {
	EXPECT_EQ(1, 1);
}

int main(int argc, char*argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
