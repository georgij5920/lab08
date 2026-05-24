#include "Account.h"

#include <stdexcept>

#include <gtest/gtest.h>

TEST(Account, ConstructorStoresIdAndBalance) {
  Account account(10, 250);

  EXPECT_EQ(account.id(), 10);
  EXPECT_EQ(account.GetBalance(), 250);
}

TEST(Account, ChangeBalanceRequiresLock) {
  Account account(1, 100);

  EXPECT_THROW(account.ChangeBalance(50), std::runtime_error);
}

TEST(Account, ChangeBalanceWhenLockedUpdatesBalance) {
  Account account(1, 100);

  account.Lock();
  account.ChangeBalance(50);
  account.ChangeBalance(-20);
  account.Unlock();

  EXPECT_EQ(account.GetBalance(), 130);
}

TEST(Account, LockTwiceThrowsAndUnlockAllowsLockAgain) {
  Account account(1, 100);

  account.Lock();
  EXPECT_THROW(account.Lock(), std::runtime_error);
  account.Unlock();
  EXPECT_NO_THROW(account.Lock());
  account.Unlock();
}
