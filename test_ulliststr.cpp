#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cassert>

#include "ulliststr.h"

//Use this file to test your ulliststr implementation before running the test suite


void check(bool cond, const std::string& msg){
    ++numChecks; 

    if(!cond){
        ++numFailed; 
        cout << "Failed: " << msg << endl; 
    }
}

int main(int argc, char* argv[])
{

    //empty list test
    ULListStr list1; 
    check(list1.empty(), "new list should be empty");
    check(list1.size() == 0, "new list size should be 0");


    //call pushback 
    ULListStr list2; 
    list2.push_back("a");
    check(!list2.empty(), "list with 1 element not empty");
    check(list2.size() == 1, "size after one call of push_back");
    check(list2.get(0) == "a", "get (0) are one call");

    list2.push_back("b"); 
    check(list2.size() == 2, "size after second call");
    check(list2.get(0) == "a" && list2.get(1) == "b", "order preserved after call"); 


    //call pushback on full list 
    ULListStr list3; 
    for(size_t i = 0; i < ARRSIZE; ++i){
        list3.push_back(to_string(i));
    }
    check(list3.size() == ARRSIZE, "size filling one node exactly from push front");

    //should allocate brand new had 

    list3.push_back("over");
    check(list3.size() == ARRSIZE + 1, "size after adding new node");
    check(list3.get(ARRSIZE) == "over", "value correctly newly allocated in back node");
    for(size_t i = 0; i < ARRSIZE; ++i)
    {
      check(list3.get(i) == to_string(i), "earlier values intact after new node alloc");
    }
    
    //push_front on empty list 
    ULListStr list4; 
    list4.push_front("z");
    check(list4.size() == 1, "size after one call"); 
    check(list4.get(0) == "z", "get(0) after one call"); 

    list4.push_front("y");
    check(list4.size() == 1, "size after second call");
    check(list4.get(1) == "y", "get(1) after one call, order preserved after call");


    //push front when list full 

    ULListStr list5; 
    for(size_t i = 0; i < ARRSIZE; ++i)
    {
      list5.push_front(to_string(i));
    }
    check(list5.size() == ARRSIZE, "size after filling one node exactly via push_front");

    list5.push_front("over");
    check(list5.size() == ARRSIZE + 1, "size after forcing new node on push_front");
    check(list5.get(0) == "over", "value correct in newly allocated front node");
    check(list5.get(1) == to_string(ARRSIZE - 1), "prior front value now at index 1");

    
    //multiple calls of pushback and front

    ULListStr list6;
    list6.push_back("mid");
    list6.push_front("left");
    list6.push_back("right");
    vector<string> expected = {"left", "mid", "right"};
    for(size_t i = 0; i < expected.size(); ++i)
    {
      check(list6.get(i) == expected[i], "mixed push front/back order");
    }

    // clear()
    ULListStr list7;
    for(int i = 0; i < 25; ++i)
    {
      list7.push_back(to_string(i));
    }
    list7.clear();
    check(list7.empty(), "list empty after clear()");
    check(list7.size() == 0, "size 0 after clear()");
 
    // list should still be usable after clear()
    list7.push_back("reused");
    check(list7.size() == 1, "list usable after clear() and a new push_back");
    check(list7.get(0) == "reused", "value correct after clear() and reuse");

    cout << "\n" << (numChecks - numFailed) << "/" << numChecks << " checks passed." << std::endl;
    return numFailed == 0 ? 0 : 1;


}
