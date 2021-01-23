// Copyright 2020 Vladislav Kravchenko <Kravchenko_vlad2001@bk.ru>

#include <gtest/gtest.h>

#include <SharedPtr.hpp>

class TestClass {
 public:
  int a;
};

TEST(testConstructor, pointNullptr) {
SharedPtr <int> pointer;
int* tmp = pointer.get();
EXPECT_EQ(tmp, nullptr);
}

TEST(testConstructor, TestMove){
  int* anyPointer = new int (25);
  SharedPtr <int> pointer(anyPointer);
  SharedPtr <int> sPointer(move(pointer));
  SharedPtr <int> thPointer;
  thPointer = std::move(pointer);
  SharedPtr <int> foPointer;
  foPointer = thPointer;
  EXPECT_EQ(25, *sPointer.get());
  EXPECT_FALSE(pointer);
}

TEST(testOperator, arrowTest) {
auto testClassPointer = new TestClass;
SharedPtr <TestClass> pointer(testClassPointer);
testClassPointer -> a = 25;
EXPECT_EQ(pointer -> a, testClassPointer -> a);
}

TEST(testOperator, StarTest) {
int* anyPointer = new int (25);
SharedPtr <int> pointer(anyPointer);
EXPECT_EQ(25, *pointer);
}
TEST(testOperator, equalityLvalueTest) {
  int* anyPointer = new int (25);
  SharedPtr <int> pointer(anyPointer);
  SharedPtr <int> sPointer = pointer;
  SharedPtr <int> thPointer = pointer;
  EXPECT_EQ(thPointer.get(), pointer.get());
}

TEST(testOperator, useCount){
  int* anyPointer = new int (25);
  SharedPtr <int> pointer(anyPointer);
  SharedPtr <int> sPointer = pointer;
  EXPECT_EQ(pointer.use_count(),2);
}

TEST(testOperator, boolTest) {
  int* anyPointer = new int (25);
  SharedPtr <int> pointer(anyPointer);
  SharedPtr <int> sPointer = pointer;
  bool isPointer = sPointer;
  EXPECT_EQ(isPointer, true);
}

TEST(testMethod, GetTest) {
int* anyPointer = nullptr;
SharedPtr <int> pointer(anyPointer);
int* tmp = pointer.get();
EXPECT_EQ(tmp, nullptr);
}

TEST(testMethod, GetIntTest) {
int* anyPointer = new int (25);
SharedPtr <int> pointer(anyPointer);
SharedPtr <int> sPointer = pointer;
EXPECT_EQ(pointer.get(), anyPointer);
}

TEST(testMethod, ResetTest) {
int* anyPointer = new int (25);
SharedPtr <int> pointer(anyPointer);
pointer.reset();
EXPECT_EQ(pointer.get(), nullptr);
}

TEST(testMethod, ResetTestElse){
int* anyPointer = new int (25);
SharedPtr <int> pointer(anyPointer);
SharedPtr <int> sPointer = pointer;
pointer.reset();
EXPECT_EQ(pointer.get(), nullptr);
}

TEST (testMethod, resetTestPoint) {
int* anyPointer = new int (25);
int* anotherPointer = new int (20);
SharedPtr <int> pointer(anyPointer);
pointer.reset(anotherPointer);
EXPECT_EQ(pointer.get(), anotherPointer);
}

TEST (testMethod, resetTestPointElse) {
int* anyPointer = new int (25);
int* anotherPointer = new int (20);
SharedPtr <int> pointer(anyPointer);
SharedPtr <int> sPointer = pointer;
pointer.reset(anotherPointer);
EXPECT_EQ(pointer.get(), anotherPointer);
}

TEST(testMethod, swapTest) {
int* anyPointer = new int (25);
int* anotherPointer = new int (20);
SharedPtr <int> pointer(anyPointer);
SharedPtr <int> sPointer(anotherPointer);
pointer.swap(sPointer);
EXPECT_EQ(pointer.get(), anotherPointer);
EXPECT_EQ(sPointer.get(), anyPointer);
}

TEST(testIsMove, assignConstTest) {
EXPECT_EQ(std::is_move_assignable<SharedPtr<int>>::value, true);
EXPECT_EQ(std::is_move_constructible<SharedPtr<int>>::value, true);
EXPECT_EQ(std::is_move_assignable<SharedPtr<double>>::value, true);
EXPECT_EQ(std::is_move_constructible<SharedPtr<double>>::value,true);
EXPECT_EQ(std::is_move_assignable<SharedPtr<TestClass>>::value,true);
EXPECT_EQ(std::is_move_constructible<SharedPtr<TestClass>>::value,true);
}

TEST(testIsCopy, assignConstTest) {
EXPECT_EQ(std::is_copy_assignable<SharedPtr<int>>::value, true);
EXPECT_EQ(std::is_copy_constructible<SharedPtr<int>>::value, true);
EXPECT_EQ(std::is_copy_assignable<SharedPtr<double>>::value, true);
EXPECT_EQ(std::is_copy_constructible<SharedPtr<double>>::value,true);
EXPECT_EQ(std::is_copy_assignable<SharedPtr<TestClass>>::value,true);
EXPECT_EQ(std::is_copy_constructible<SharedPtr<TestClass>>::value,true);
}