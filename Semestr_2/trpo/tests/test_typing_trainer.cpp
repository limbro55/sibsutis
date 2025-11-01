#include "../include/typing_trainer.hpp"
#include <gtest/gtest.h>
#include <string>
#include <fstream>

#include <fstream>

TEST(TypingTrainerTest, GenerateRandomStringTest) {
    std::string str1 = generateRandomString(10);
    std::string str2 = generateRandomString(10);
    EXPECT_EQ(str1.length(), 10);
    EXPECT_EQ(str2.length(), 10);
    EXPECT_NE(str1, str2); 
}

TEST(TypingTrainerTest, SaveResultTest) {

    std::ofstream outFile("typing_results.txt");
    outFile.close();

    
    saveResult(60.0, 5, 10.0);

    
    std::ifstream inFile("typing_results.txt");
    std::string line;
    ASSERT_TRUE(std::getline(inFile, line));
    EXPECT_EQ(line, "Time: 60s, Errors: 5, WPM: 10");
    inFile.close();
}

TEST(TypingTrainerTest, ViewResultsTest) {

    std::ofstream outFile("typing_results.txt");
    outFile << "Time: 60s, Errors: 5, WPM: 10" << std::endl;
    outFile.close();


    std::streambuf* orig_buf = std::cout.rdbuf();
    std::ostringstream capture_output;
    std::cout.rdbuf(capture_output.rdbuf());


    viewResults();

    std::cout.rdbuf(orig_buf);

    std::string expected_output = "Результаты предыдущих тестов:\nTime: 60s, Errors: 5, WPM: 10\n";
    EXPECT_EQ(capture_output.str(), expected_output);
}

TEST(TypingTrainerTest, SaveResultEdgeCasesTest) {

    EXPECT_NO_THROW(saveResult(0.0, 0, 0.0)); 
    EXPECT_NO_THROW(saveResult(9999.9, 9999, 9999.9)); 
}

TEST(TypingTrainerTest, GenerateRandomStringEdgeCaseTest) {

    std::string str = generateRandomString(0);
    EXPECT_EQ(str.length(), 0);
}


TEST(TypingTrainerTest, StartTypingTestIntegrationTest) {

    std::string testString = "teststring";
    std::string userInput = "teststring";

    std::istringstream input(userInput);
    std::cin.rdbuf(input.rdbuf());

    std::streambuf* orig_buf = std::cout.rdbuf();
    std::ostringstream capture_output;
    std::cout.rdbuf(capture_output.rdbuf());

    startTypingTest(testString.length());

    std::cout.rdbuf(orig_buf);
    std::cin.rdbuf(nullptr);

    std::string output = capture_output.str();
    EXPECT_NE(output.find("Ваше время"), std::string::npos);
    EXPECT_NE(output.find("Количество ошибок"), std::string::npos);
    EXPECT_NE(output.find("Скорость печати"), std::string::npos);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}