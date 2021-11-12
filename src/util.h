#ifndef _UTIL_H_
#define _UTIL_H_

std::string getTime();
std::string getHost();

void checkArgc(int argc, int expected, char const *program);
void checkPort(int port);

void Trans(int n);
void Sleep(int n);

#endif /* _UTIL_H_ */
