// protobuf - demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "addressbook_read.h"
#include "addressbook_write.h"

int main(int argc, char* argv[]) {

#if 0
	test_write_message(argc, argv);
#endif

	test_read_message(argc, argv);

	return 0;
}