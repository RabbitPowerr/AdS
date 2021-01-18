#include "Calculator.h"
#include <gtest.h>



TEST(Testes, Throw_exeption1){
	Calculator calc;
	ASSERT_ANY_THROW(calc.get_ans("5++5"));
}

TEST(Testes, Throw_exeption2) {
	Calculator calc;
	ASSERT_ANY_THROW(calc.get_ans("+++5"));
}

TEST(Testes, Throw_exeption3) {
	Calculator calc;
	ASSERT_ANY_THROW(calc.get_ans("3***"));
}

TEST(Testes, Throw_exeption4) {
	Calculator calc;
	ASSERT_ANY_THROW(calc.get_ans("(5+5"));
}

TEST(Testes, Throw_exeption4) {
	Calculator calc;
	ASSERT_ANY_THROW(calc.get_ans("5+5)"));
}


TEST(Testes, test1) {
	Calculator calc;
	EXPECT_EQ(1, calc.get_ans("5+5+5") == 15);
}

TEST(Testes, test2) {
	Calculator calc;
	EXPECT_EQ(1, calc.get_ans("5+10*5") == 55);
}

