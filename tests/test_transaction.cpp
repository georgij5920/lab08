#include "Account.h"
#include "Transaction.h"

#include <stdexcept>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;

class MockAccount : public Account {
 public:
  MockAccount(int id, int balance) : Account(id, balance) {}

  MOCK_METHOD(int, GetBalance, (), (const, override));
  MOCK_METHOD(void, ChangeBalance, (int diff), (override));
  MOCK_METHOD(void, Lock, (), (override));
  MOCK_METHOD(void, Unlock, (), (override));
};

class MockTransaction : public Transaction {
 public:
  MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum),
              (override));
};

TEST(Transaction, HasDefaultFeeAndAllowsChangingFee) {
  Transaction transaction;

  EXPECT_EQ(transaction.fee(), 1);
  transaction.set_fee(7);
  EXPECT_EQ(transaction.fee(), 7);
}

TEST(Transaction, ThrowsWhenAccountsAreSame) {
  Account account(1, 1000);
  Transaction transaction;

  EXPECT_THROW(transaction.Make(account, account, 100), std::logic_error);
}

TEST(Transaction, ThrowsWhenSumIsNegative) {
  Account from(1, 1000);
  Account to(2, 1000);
  Transaction transaction;

  EXPECT_THROW(transaction.Make(from, to, -1), std::invalid_argument);
}

TEST(Transaction, ThrowsWhenSumIsTooSmall) {
  Account from(1, 1000);
  Account to(2, 1000);
  Transaction transaction;

  EXPECT_THROW(transaction.Make(from, to, 99), std::logic_error);
}

TEST(Transaction, ReturnsFalseWhenFeeIsTooLarge) {
  Account from(1, 1000);
  Account to(2, 1000);
  Transaction transaction;
  transaction.set_fee(51);

  EXPECT_FALSE(transaction.Make(from, to, 100));
}

TEST(Transaction, SuccessfulTransferChangesBothBalancesAndWritesToOutput) {
  Account from(1, 1000);
  Account to(2, 200);
  Transaction transaction;

  testing::internal::CaptureStdout();
  EXPECT_TRUE(transaction.Make(from, to, 100));
  const std::string output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(from.GetBalance(), 899);
  EXPECT_EQ(to.GetBalance(), 300);
  EXPECT_THAT(output, testing::HasSubstr("1 send to 2 $100"));
  EXPECT_THAT(output, testing::HasSubstr("Balance 1 is 899"));
  EXPECT_THAT(output, testing::HasSubstr("Balance 2 is 300"));
}

TEST(Transaction, FailedDebitRollsBackReceiverCredit) {
  Account from(1, 50);
  Account to(2, 200);
  Transaction transaction;

  EXPECT_FALSE(transaction.Make(from, to, 100));
  EXPECT_EQ(from.GetBalance(), 50);
  EXPECT_EQ(to.GetBalance(), 200);
}

TEST(Transaction, UsesMockObjectsForSuccessfulTransaction) {
  MockAccount from(1, 1000);
  MockAccount to(2, 200);
  MockTransaction transaction;

  {
    InSequence sequence;
    EXPECT_CALL(from, Lock());
    EXPECT_CALL(to, Lock());
    EXPECT_CALL(to, ChangeBalance(150));
    EXPECT_CALL(from, GetBalance()).WillOnce(Return(1000));
    EXPECT_CALL(from, ChangeBalance(-151));
    EXPECT_CALL(transaction, SaveToDataBase(_, _, 150));
    EXPECT_CALL(to, Unlock());
    EXPECT_CALL(from, Unlock());
  }

  EXPECT_TRUE(transaction.Make(from, to, 150));
}
