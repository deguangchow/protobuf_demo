ECHO ======== Check CppCheck Start ========

cppcheck --enable=warning,performance --inconclusive protobuf_demo test > cppcheck.log

ECHO ======== Check CppCheck Result ========