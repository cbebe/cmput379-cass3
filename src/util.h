#ifndef _UTIL_H_
#define _UTIL_H_

std::string getTime();
std::string getProcessName();

void checkArgc(int argc, int expected, char const *program);
int getPort(char const *arg);

void Trans(int n);
void Sleep(int n);

#endif /* _UTIL_H_ */
