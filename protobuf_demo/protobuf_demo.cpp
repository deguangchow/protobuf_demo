///    Copyright (C) 2019 DG.C, DGCHOW, deguangchow
///        deguangchow@qq.com
///
///    \brief    protobuf_demo : 定义控制台应用程序的入口点。
///
///    \author   deguangchow
///    \version  1.0
///    \2019/10/28

#include "stdafx.h"
#include "addressbook_read.h"
#include "addressbook_write.h"
#include "item_read.h"
#include "item_write.h"

int main(int argc, char* argv[]) {
#if 0
    test_addressbook_write(argc, argv);
    test_addressbook_read(argc, argv);

    test_item_write(argc, argv);
    test_item_read(argc, argv);
#endif

    test_item_read(argc, argv);

    return 0;
}

