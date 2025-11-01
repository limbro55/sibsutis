#ifndef TYPING_TRAINER_HPP
#define TYPING_TRAINER_HPP

#include <string>

std::string generateRandomString(int length);
void saveResult(double time, int errors, double wpm);
void viewResults();
void startTypingTest(int stringLength);


#endif // TYPING_TRAINER_HPP
