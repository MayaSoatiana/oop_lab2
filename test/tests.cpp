#include <gtest/gtest.h>
#include "BitString.h"
#include <stdexcept>

// ==================== CONSTRUCTOR TESTS ====================
TEST(BitStringTest, EmptyStringConstructorThrowsException) {
    ASSERT_THROW(BitString bs(""), std::invalid_argument);
}

TEST(BitStringTest, DefaultConstructorCreatesEmptyString) {
    BitString bs;  
    ASSERT_EQ(bs.toString(), "");  
    ASSERT_EQ(bs.getSize(), 0);
}

TEST(BitStringTest, SizeConstructorWithZeros) {
    BitString bs(5, '0');
    ASSERT_EQ(bs.toString(), "00000");
}

TEST(BitStringTest, SizeConstructorWithOnes) {
    BitString bs(3, '1');
    ASSERT_EQ(bs.toString(), "111");
}

TEST(BitStringTest, StringConstructorValidInput) {
    BitString bs("101010");
    BitString expected("101010");
    ASSERT_TRUE(bs.equals(expected));
}

TEST(BitStringTest, InitializerListConstructorValid) {
    BitString bs{'1', '0', '1', '0'};
    ASSERT_EQ(bs.toString(), "1010");
}

TEST(BitStringTest, InitializerListConstructorSingleElement) {
    BitString bs{'1'};
    BitString expected("1");
    ASSERT_EQ(bs.toString(), "1");
}

TEST(BitStringTest, CopyConstructorCreatesIndependentCopy) {
    BitString original("1100");
    BitString copy(original);
    ASSERT_TRUE(copy.equals(original));
    
    BitString modified = original.notOperation();
    ASSERT_EQ(copy.toString(), "1100"); // Copy should still be "1100"
}

// ==================== INVALID INPUT TESTS ====================

TEST(BitStringTest, StringConstructorThrowsOnInvalidCharacter) {
    try {
        BitString bs("1020");
        FAIL() << "Expected std::invalid_argument for character '2'";
    } catch (const std::invalid_argument& e) {
        SUCCEED();
    } catch (...) {
        FAIL() << "Expected std::invalid_argument but got different exception";
    }
}

TEST(BitStringTest, StringConstructorThrowsOnSpaceCharacter) {
    try {
        BitString bs("1 0");
        FAIL() << "Expected std::invalid_argument for space character";
    } catch (const std::invalid_argument& e) {
        SUCCEED();
    }
}

TEST(BitStringTest, InitializerListThrowsOnInvalidCharacter) {
    try {
        BitString bs{'1', '0', 'a', '1'};
        FAIL() << "Expected std::invalid_argument for character 'a'";
    } catch (const std::invalid_argument& e) {
        SUCCEED();
    }
}

TEST(BitStringTest, SizeConstructorThrowsOnInvalidDefaultValue) {
    try {
        BitString bs(5, '5');
        FAIL() << "Expected std::invalid_argument for default value '5'";
    } catch (const std::invalid_argument& e) {
        SUCCEED();
    }
}

// ==================== AND OPERATION TESTS ====================

TEST(BitStringTest, AndOperationSameLengthAllOnes) {
    BitString bs1("1111");
    BitString bs2("1010");
    BitString result = bs1.andOperation(bs2); // 1111 & 1010 = 1010

    ASSERT_EQ(result.toString(), "1010");
}

TEST(BitStringTest, AndOperationSameLengthAllZeros) {
    BitString bs1("0000");
    BitString bs2("1010");
    BitString result = bs1.andOperation(bs2); // 0000 & 1010 = 0000

    ASSERT_EQ(result.toString(), "0000");
}

TEST(BitStringTest, AndOperationSameLengthMixed) {
    BitString bs1("1010");
    BitString bs2("1100");
    BitString result = bs1.andOperation(bs2); // 1010 & 1100 = 1000
   
    ASSERT_EQ(result.toString(), "1000");
}

TEST(BitStringTest, AndOperationFirstStringShorter) {
    BitString bs1("101");
    BitString bs2("1100");
    BitString result = bs1.andOperation(bs2); // 0101 & 1100 = 0100 (padded with zeros)
  
    ASSERT_EQ(result.toString(), "0100");
}

TEST(BitStringTest, AndOperationSecondStringShorter) {
    BitString bs1("1101");
    BitString bs2("10");
    BitString result = bs1.andOperation(bs2); // 1101 & 0010 = 0000 (padded with zeros)

    ASSERT_EQ(result.toString(), "0000");
}

// ==================== OR OPERATION TESTS ====================

TEST(BitStringTest, OrOperationSameLengthAllOnes) {
    BitString bs1("1111");
    BitString bs2("1010");
    BitString result = bs1.orOperation(bs2);// 1111 | 1010 = 1111

    ASSERT_EQ(result.toString(), "1111");
}

TEST(BitStringTest, OrOperationSameLengthAllZeros) {
    BitString bs1("0000");
    BitString bs2("1010");
    BitString result = bs1.orOperation(bs2); // 0000 | 1010 = 1010

    ASSERT_EQ(result.toString(), "1010");
}

TEST(BitStringTest, OrOperationSameLengthMixed) {
    BitString bs1("1010");
    BitString bs2("1100");
    BitString result = bs1.orOperation(bs2); // 1010 | 1100 = 1110

    ASSERT_EQ(result.toString(), "1110");
}

TEST(BitStringTest, OrOperationFirstStringShorter) {
    BitString bs1("101");
    BitString bs2("1100");
    BitString result = bs1.orOperation(bs2); // 0101 | 1100 = 1101 (padded with zeros)
 
    ASSERT_EQ(result.toString(), "1101");
}

TEST(BitStringTest, OrOperationSecondStringShorter) {
    BitString bs1("1101");
    BitString bs2("10");
    BitString result = bs1.orOperation(bs2); // 1101 | 0010 = 1111 (padded with zeros)
    
    ASSERT_EQ(result.toString(), "1111");
}

// ==================== XOR OPERATION TESTS ====================

TEST(BitStringTest, XorOperationSameLengthAllOnes) {
    BitString bs1("1111");
    BitString bs2("1111");
    BitString result = bs1.xorOperation(bs2); // 1111 ^ 1111 = 0000
   
    ASSERT_EQ(result.toString(), "0000");
}

TEST(BitStringTest, XorOperationSameLengthMixed) {
    BitString bs1("1010");
    BitString bs2("1100");
    BitString result = bs1.xorOperation(bs2); // 1010 ^ 1100 = 0110

    ASSERT_EQ(result.toString(), "0110");
}

TEST(BitStringTest, XorOperationFirstStringShorter) {
    BitString bs1("101");
    BitString bs2("1100");
    BitString result = bs1.xorOperation(bs2); // 0101 ^ 1100 = 1001 (padded with zeros)

    ASSERT_EQ(result.toString(), "1001");
}

// ==================== NOT OPERATION TESTS ====================

TEST(BitStringTest, NotOperationMixedBits) {
    BitString bs("1010");
    BitString result = bs.notOperation(); // ~1010 = 0101

    ASSERT_EQ(result.toString(), "0101");
}

TEST(BitStringTest, NotOperationAllOnes) {
    BitString bs("1111");
    BitString result = bs.notOperation(); // ~1111 = 0000
   
    ASSERT_EQ(result.toString(), "0000");
}

TEST(BitStringTest, NotOperationAllZeros) {
    BitString bs("0000");
    BitString result = bs.notOperation(); // ~0000 = 1111

    ASSERT_EQ(result.toString(), "1111");
}

// ==================== EDGE CASE TESTS ====================

TEST(BitStringTest, StringOperations) {
    BitString first("100001110111000");
    BitString second("101110011");
    
    BitString andResult = first.andOperation(second);
    BitString orResult = first.orOperation(second);
    BitString xorResult = first.xorOperation(second);
    
    ASSERT_EQ(andResult.toString(), "000000100110000");
    ASSERT_EQ(orResult.toString(), "100001111111011");
    ASSERT_EQ(xorResult.toString(), "100001011001011");
}

TEST(BitStringTest, SingleBitOperations) {
    BitString single1("1");
    BitString single0("0");
    
    BitString andResult = single1.andOperation(single0);
    BitString orResult = single1.orOperation(single0);
    BitString xorResult = single1.xorOperation(single0);
    
    ASSERT_EQ(andResult.toString(), "0");
    ASSERT_EQ(orResult.toString(), "1");
    ASSERT_EQ(xorResult.toString(), "1");
}

// ==================== COMPLEX OPERATION TESTS ====================

TEST(BitStringTest, MultipleChainedOperations) {
    BitString bs1("101");
    BitString bs2("1100");
    BitString bs3("111");
    
    // ((101 & 1100) | 111) = (0100 | 111) = (0100 | 0111) = 0111
    BitString result = bs1.andOperation(bs2).orOperation(bs3);
    ASSERT_EQ(result.toString(), "0111");
}

TEST(BitStringTest, NotOfAndOperation) {
    BitString bs1("1010");
    BitString bs2("1100");
    
    // ~(1010 & 1100) = ~(1000) = 0111
    BitString result = bs1.andOperation(bs2).notOperation();
    ASSERT_EQ(result.toString(), "0111");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}