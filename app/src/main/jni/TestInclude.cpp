//
// Created by yanghai on 17/4/4.
//

#include "TestInclude.h"
#include <mutex>
//实现该方法时，类名+"::"+方法名
int TestInclude::add(int a, int b) {
    return a + b;
}

int TestInclude::addV(int a, int b, int c) {
    return a + b + c;
}