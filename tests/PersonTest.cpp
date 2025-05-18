#include "Person.hpp"
#include "MergeSortStrategy.hpp"
#include "InsertionSortStrategy.hpp"
#include <gtest/gtest.h>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

// Helper function to build a large test team
unique_ptr<Person> buildLargeTestTeam(size_t size) {
    unique_ptr<Person> team = nullptr;
    for (size_t i = 0; i < size; ++i) {
        auto person = make_unique<Person>("Person" + to_string(size - i), rand() % 100, "cake");
        person->next = move(team);
        team = move(person);
    }
    return team;
}

// Helper function to build a team for testing
std::unique_ptr<Person> buildTestTeam() {
    auto team = std::make_unique<Person>("Alice", 30, "cake");
    team->next = std::make_unique<Person>("Bob", 25, "cookie");
    team->next->next = std::make_unique<Person>("Charlie", 35, "cake");
    return team;
}

// Test for building a team
TEST(PersonTest, BuildTeam) {
    std::unique_ptr<Person> team = nullptr;
    Person::buildTeam(team);

    ASSERT_NE(team, nullptr);
    ASSERT_NE(team->next, nullptr);
}

// Test for showing a team
TEST(PersonTest, ShowTeam) {
    auto team = buildTestTeam();

    std::ostringstream output;
    std::streambuf* oldCoutBuf = std::cout.rdbuf(output.rdbuf());

    Person::showTeam(team);

    std::cout.rdbuf(oldCoutBuf);

    std::string expectedOutput =
        "name: Alice age: 30 choice: cake\n"
        "name: Bob age: 25 choice: cookie\n"
        "name: Charlie age: 35 choice: cake\n";

    ASSERT_EQ(output.str(), expectedOutput);
}

// Test: sortByAge should not modify the input list
TEST(PersonTest, SortByAgeDoesNotModifyInput) {
    auto team = buildTestTeam();
    auto originalTeam = buildTestTeam(); // Keep a copy of the original team for comparison

    auto sortedTeam = Person::sortByAge(team);

    // Verify the input list remains unchanged
    Person* currentOriginal = originalTeam.get();
    Person* currentInput = team.get();
    while (currentOriginal && currentInput) {
        EXPECT_EQ(currentOriginal->data->name, currentInput->data->name);
        EXPECT_EQ(currentOriginal->data->age, currentInput->data->age);
        EXPECT_EQ(currentOriginal->data->cake_or_cookie, currentInput->data->cake_or_cookie);
        currentOriginal = currentOriginal->next.get();
        currentInput = currentInput->next.get();
    }
    EXPECT_EQ(currentOriginal, nullptr);
    EXPECT_EQ(currentInput, nullptr);
}

// Test: sortByAge should return a correctly sorted list
TEST(PersonTest, SortByAgeReturnsSortedList) {
    auto team = buildTestTeam();

    auto sortedTeam = Person::sortByAge(team);

    // Verify the sorted list
    ASSERT_NE(sortedTeam, nullptr);
    EXPECT_EQ(sortedTeam->data->name, "Bob");
    EXPECT_EQ(sortedTeam->data->age, 25);

    ASSERT_NE(sortedTeam->next, nullptr);
    EXPECT_EQ(sortedTeam->next->data->name, "Alice");
    EXPECT_EQ(sortedTeam->next->data->age, 30);

    ASSERT_NE(sortedTeam->next->next, nullptr);
    EXPECT_EQ(sortedTeam->next->next->data->name, "Charlie");
    EXPECT_EQ(sortedTeam->next->next->data->age, 35);

    EXPECT_EQ(sortedTeam->next->next->next, nullptr);
}

// Test: sortByAge should handle an empty list
TEST(PersonTest, SortByAgeHandlesEmptyList) {
    unique_ptr<Person> team = nullptr;

    auto sortedTeam = Person::sortByAge(team);

    // Verify the sorted list is nullptr
    EXPECT_EQ(sortedTeam, nullptr);
}

// Test: sortByAge should handle a single-node list
TEST(PersonTest, SortByAgeHandlesSingleNodeList) {
    auto team = make_unique<Person>("Alice", 30, "cake");

    auto sortedTeam = Person::sortByAge(team);

    // Verify the sorted list is identical to the input
    ASSERT_NE(sortedTeam, nullptr);
    EXPECT_EQ(sortedTeam->data->name, "Alice");
    EXPECT_EQ(sortedTeam->data->age, 30);
    EXPECT_EQ(sortedTeam->data->cake_or_cookie, "cake");
    EXPECT_EQ(sortedTeam->next, nullptr);
}

TEST(PersonTest, MergeSortStrategyWorks) {
    auto team = buildTestTeam();
    MergeSortStrategy mergeSort;
    auto sortedTeam = mergeSort.sort(team);

    ASSERT_NE(sortedTeam, nullptr);
    EXPECT_EQ(sortedTeam->data->name, "Bob");
    EXPECT_EQ(sortedTeam->next->data->name, "Alice");
    EXPECT_EQ(sortedTeam->next->next->data->name, "Charlie");
}

TEST(PersonTest, InsertionSortStrategyWorks) {
    auto team = buildTestTeam();
    InsertionSortStrategy insertionSort;
    auto sortedTeam = insertionSort.sort(team);

    ASSERT_NE(sortedTeam, nullptr);
    EXPECT_EQ(sortedTeam->data->name, "Bob");
    EXPECT_EQ(sortedTeam->next->data->name, "Alice");
    EXPECT_EQ(sortedTeam->next->next->data->name, "Charlie");
}

// Test: Performance comparison of MergeSortStrategy and InsertionSortStrategy
TEST(PersonTest, SortStrategyPerformance) {
    const size_t teamSize = 10000; // Adjust size for performance testing
    auto team = buildLargeTestTeam(teamSize);

    // Measure performance of MergeSortStrategy
    MergeSortStrategy mergeSort;
    auto startMerge = high_resolution_clock::now();
    auto sortedMerge = mergeSort.sort(team);
    auto endMerge = high_resolution_clock::now();
    auto mergeDuration = duration_cast<milliseconds>(endMerge - startMerge).count();
    cout << "MergeSortStrategy took " << mergeDuration << " ms for " << teamSize << " elements." << endl;

    // Measure performance of InsertionSortStrategy
    auto teamCopy = buildLargeTestTeam(teamSize); // Rebuild the team for a fair comparison
    InsertionSortStrategy insertionSort;
    auto startInsertion = high_resolution_clock::now();
    auto sortedInsertion = insertionSort.sort(teamCopy);
    auto endInsertion = high_resolution_clock::now();
    auto insertionDuration = duration_cast<milliseconds>(endInsertion - startInsertion).count();
    cout << "InsertionSortStrategy took " << insertionDuration << " ms for " << teamSize << " elements." << endl;

    // Ensure both strategies produce sorted results
    ASSERT_NE(sortedMerge, nullptr);
    ASSERT_NE(sortedInsertion, nullptr);

    Person* mergeCurrent = sortedMerge.get();
    Person* insertionCurrent = sortedInsertion.get();
    while (mergeCurrent && insertionCurrent) {
        EXPECT_EQ(mergeCurrent->data->age, insertionCurrent->data->age);
        mergeCurrent = mergeCurrent->next.get();
        insertionCurrent = insertionCurrent->next.get();
    }
    EXPECT_EQ(mergeCurrent, nullptr);
    EXPECT_EQ(insertionCurrent, nullptr);
}