/*
 * Unit tests:
 * Unit tests are useful for regression testing, meaning that when you make a change, they help prevent the introduction of new bugs.
 * Unit tests are short, independent and fast.
 * Unit testing is part of functional testing, i.e. the correctness of the code is checked. Individual functions/methods are usually tested.
 * A unit test is divided into three parts: Arrange (test setup), Act (call the method), Assert(check the result).
 * An assertion is where the test condition is checked. They are fatal (ASSERT) or non-fatal(EXPECT).
 * There are special assertions for strings.
 * Assertions can be used to check if an exception was thrown, or what type of exception was thrown.
 *
 * Test fixtures:
 * A fixture is useful for removing code duplication. It's used where the setup phase and cleanup phase are similar.
 * It's a class where the test setup is written in the SetUp() method and the cleanup is in TearDown().
 * Help you to write the tests by reusing the code in the setup and teardown phase.
 * The functions you can overwrite are:
 * - SetUp() : Called before each tests
 * - TearDown() : Called after each tests
 * - SetUpTestCase() : Called before entire test suite
 * - TearDownTestCase() : Called after entire test suite
 * The most common use for Setup and TearDown is when you use an object pointer. (see below)
 *
 * Parameterized tests:
 * Parameterized tests can be used to generate tests that have the same body, but different input values.
 * When you generate a test, the expected output values can be packed together with the input values using complex data structures.
 * Generators can be used to generate input values for the test.
 */

#include "gtest/gtest.h"
#include "../MyLibrary/MyLibrary.h"


// Basic Tests
TEST(Test_MyMathLib, Sqrt9)
{
    ASSERT_EQ(3, mySqrt(9));
}

TEST(Test_MyMathLib, TestSqrt25)
{
    EXPECT_EQ(5, mySqrt(25));
}

TEST(Test_MyMathLib, TestAdd_15_22)
{
    EXPECT_EQ(37, myAdd(15,22));
}

TEST(Test_MyMathLib, TestAdd_m5_7)
{
    EXPECT_EQ(2, myAdd(-5,7));
}

TEST(TestCountPositives, BasicTest)
{
    // Arrange (Setup)
    vector<int> inputVector{1,-2, 3, -4, 5, -6, -7};

    // Act & Assert
    EXPECT_EQ(3, countPositives(inputVector));
}

TEST(TestCountPositives, EmptyVector)
{
    // Arrange (Setup)
    vector<int> inputVector{};

    // Act & Assert
    EXPECT_EQ(0, countPositives(inputVector));
}

TEST(TestCountPositives, AllNegatives)
{
    // Arrange (Setup)
    vector<int> inputVector{-1,-2, -3};

    // Act & Assert
    EXPECT_EQ(0, countPositives(inputVector));
}


// String
TEST(TestToUpper, BasicTest)
{
    // Arrange (Setup)
    char inputString[] = "Hello World";

    // Act
    toUpper(inputString);

    // Assert
    //ASSERT_EQ("HELLO WORLD", inputString); // Wrong way to do it this will verify the pointer and not the content
    ASSERT_STREQ("HELLO WORLD", inputString);
}


// Exceptions
TEST(Test_MyMathLib, TestSqrt_TrowException)
{
    //ASSERT_ANY_THROW(mySqrt(-9));
    ASSERT_THROW(mySqrt(-9), std::runtime_error);
}

TEST(Test_MyMathLib, TestSqrt_NoException)
{
    ASSERT_NO_THROW(mySqrt(9));
}


// Test Fixtures
/*
 * The two lines used in each test were:
 *     Account account;
 *     account.deposit(100);
 */
class AccountTestFixture: public testing::Test
{
    public:
        AccountTestFixture();
        virtual ~AccountTestFixture();
        void SetUp() override;
        void TearDown() override;
        static void SetUpTestCase();
        static void TearDownTestCase();

    protected:
        Account *account;
};

AccountTestFixture::AccountTestFixture()
{
    std::cout << "Constructor called \n";
}

AccountTestFixture::~AccountTestFixture()
{
    std::cout << "Destructor called \n";
}

void AccountTestFixture::SetUp()
{
    std::cout << "SetUp called \n";
    account = new Account();
    account->deposit(100.5);
}

void AccountTestFixture::TearDown()
{
    std::cout << "TearDown called \n";
    delete account;
}

void AccountTestFixture::SetUpTestCase()
{
    std::cout << "SetUpTestCase called \n";
}

void AccountTestFixture::TearDownTestCase()
{
    std::cout << "TearDownTestCase called \n";
}

TEST(TestAccount, EmptyAccount)
{
    Account account;
    double balance = account.getBalance();

    ASSERT_EQ(0, balance);
}

TEST_F(AccountTestFixture, TestDeposit)
{
    ASSERT_EQ(100.5, account->getBalance());
}

TEST_F(AccountTestFixture, TestWithdrawOK)
{
    account->withdraw(50);
    ASSERT_EQ(50.5, account->getBalance());
}

TEST_F(AccountTestFixture, WithdrawInsufficientFunds)
{
    ASSERT_THROW(account->withdraw(500), std::runtime_error);
}

TEST_F(AccountTestFixture, TransferOK)
{
    Account account2;
    account->transfer(account2, 60);

    ASSERT_EQ(40.5, account->getBalance());
    ASSERT_EQ(60, account2.getBalance());
}

TEST_F(AccountTestFixture, TransferInsufficientFunds)
{
    Account account2;
    ASSERT_THROW(account->transfer(account2, 200), std::runtime_error);
}


// Parameterized Tests
// For the class validator, we test if a value is in the interval
// We would like to test one value inside, one lower edge, one higher edge, one outside lower part
// and one outside higher part. Example: Validator(5,10) Tests -> 4,5,6,7,10,11
// Too many tests identical code only different parameters

class ValidatorFixture: public testing::TestWithParam<std::tuple<int,bool>>
{
    public:
    protected:
        Validator mValidator{5, 10};
};

TEST_P(ValidatorFixture, InRange)
{
    std::tuple<int, bool> tuple = GetParam();

    int param = std::get<0>(tuple);
    bool expectedValue = std::get<1>(tuple);

    std::cout << "Param = " << param << " expected value = " << expectedValue << "\n";

    bool isInside = mValidator.inRange(param);
    ASSERT_EQ(expectedValue, isInside);
}

INSTANTIATE_TEST_SUITE_P(InRangeTrue, ValidatorFixture, testing::Values(
        std::make_tuple(-100, false),
        std::make_tuple(4, false),
        std::make_tuple(5, true),
        std::make_tuple(6, true),
        std::make_tuple(7, true),
        std::make_tuple(9, true),
        std::make_tuple(10, true),
        std::make_tuple(11, false),
        std::make_tuple(100, false)));


// Main who runs all test suites
int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}



/*
 * Here is the long way for parameterized tests:
 * class ValidatorFixture: public testing::TestWithParam<int>
{
    public:
    protected:
        Validator mValidator{5, 10};
};

TEST_P(ValidatorFixture, InRange)
{
    int param = GetParam();
    std::cout << "Param = " << param << "\n";

    bool isInside = mValidator.inRange(param);
    ASSERT_TRUE(isInside);
}

INSTANTIATE_TEST_SUITE_P(InRangeTrue, ValidatorFixture, testing::Values(5,6,7,9,10));

class ValidatorNegativeFixture: public testing::TestWithParam<int>
{
public:
protected:
    Validator mValidator{5, 10};
};

TEST_P(ValidatorNegativeFixture, NotInRange)
{
    int param = GetParam();
    std::cout << "Param (not in range) = " << param << "\n";

    bool isInside = mValidator.inRange(param);
    ASSERT_FALSE(isInside);
}

INSTANTIATE_TEST_SUITE_P(InRangeFalse, ValidatorNegativeFixture, testing::Values(-100,4,11,100));
 */