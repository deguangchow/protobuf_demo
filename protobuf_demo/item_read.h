///    Copyright (C) 2019 DG.C, DGCHOW, deguangchow
///        deguangchow@qq.com
///
///    \brief    item_read : item 读
///
///    \author   deguangchow
///    \version  1.0
///    \2019/10/28

#pragma once
#ifndef ITEM_READ_H
#define ITEM_READ_H

#include "item.pb.h"

void ListItem(const core::Item &it) {
    const auto &prop = it._props();
    cout << "_props : "
        << "{ name = " << prop.name()
        << ", code = " << prop.code()
        << ", unit = " << prop.unit()
        << ", amount = " << prop.amount()
        << ", price = " << prop.price()
        << ", summary = " << prop.summary()
        << ", catagory = " << prop.catagory()
        << "}";

    auto const &rel_size = it._relations_size();
    if (rel_size > 0) {
        cout << endl << "_relations : " << endl;
    }

    for (auto i = 0U; i < rel_size; ++i) {
        const auto &rel = it._relations(i);
        cout << "{" << endl << "_type: ";
        switch (rel._type()) {
        case core::child:
            cout << "child";
            break;
        case core::secondary:
            cout << "secondary";
            break;
        case core::inherit:
            cout << "inherit";
            break;
        case core::feetable:
            cout << "feetable";
            break;
        case core::vartable:
            cout << "vartable";
            break;
        default:
            break;
        }
        cout << ", _relatives : {";
        for (auto j = 0U; j < rel._relatives_size(); ++j) {
            auto const &child = rel._relatives(j);
            ListItem(child);
        }
        cout << "}" << endl << "}" << endl;
    }
}

int test_item_read(int argc, char *argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        cerr << "Usage :" << argv[0] << " ITEM_FILE" << endl;
        return -1;
    }

    core::Item item;
    {
        // Read the exsiting Item.
        fstream input(argv[1], ios::in | ios::binary);
        if (!item.ParseFromIstream(&input)) {
            cerr << "Failed to parse item." << endl;
            return -1;
        }
    }

    ListItem(item);

    return 0;
}

#endif  //ITEM_READ_H
