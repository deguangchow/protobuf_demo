///    Copyright (C) 2019 DG.C, DGCHOW, deguangchow
///        deguangchow@qq.com
///
///    \brief    item_write : item 写
///
///    \author   deguangchow
///    \version  1.0
///    \2019/10/28

#pragma once
#pragma once
#ifndef ITEM_WRITE_H
#define ITEM_WRITE_H

#include "item.pb.h"

void PromptForItemProperty(::core::Item *it) {
    cout << "Edit Property to item ?(Y/n)";
    char c = getchar();
    if (c != 'Y' && c != 'y') {
        return;
    }

    auto *prop = it->mutable__props();

    cout << "Enter code: ";
    getline(cin, *prop->mutable_code());
    cin.ignore(256, '\n');

    cout << "Enter catagory: ";
    int catagory;
    cin >> catagory;
    prop->set_catagory(catagory);
    cin.ignore(256, '\n');

    cout << "Enter name: ";
    string name;
    getline(cin, name);
    if (!name.empty()) {
        prop->set_name(name);
    }

    cout << "Enter unit: ";
    string unit;
    getline(cin, unit);
    if (!unit.empty()) {
        prop->set_unit(unit);
    }

    cout << "Enter amount: ";
    double amount;
    cin >> amount;
    prop->set_amount(amount);

    cout << "Enter price: ";
    double price;
    cin >> price;
    prop->set_price(amount);

    prop->set_summary(prop->amount() * prop->price());
}

void PromptForItemRelation(::core::Item *it) {
    while (true) {
        cin.ignore(256, '\n');
        cout << "Enter a relation type (or leave blank to finish): ";
        string rel_type;
        getline(cin, rel_type);
        if (rel_type.empty()) {
            break;
        }

        auto *rel = it->add__relations();

        if (rel_type == "child") {
            rel->set__type(core::child);
        } else if (rel_type == "secondary") {
            rel->set__type(core::secondary);
        } else if (rel_type == "inherit") {
            rel->set__type(core::inherit);
        } else if (rel_type == "feetable") {
            rel->set__type(core::feetable);
        } else if (rel_type == "vartable") {
            rel->set__type(core::vartable);
        } else {
            break;
        }

        while (true) {
            cout << "Add an item to relation " << rel_type << " ?(Y/n)";
            char c = getchar();
            if (c != 'Y' && c != 'y') {
                break;
            }

            cin.ignore(256, '\n');
            auto *it = rel->add__relatives();
            PromptForItemProperty(it);
        }
    }
}

int test_item_write(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " ITEM_FILE" << endl;
        return -1;
    }

    core::Item item;

    {
        // Read the exsiting item.
        fstream input(argv[1], ios::in | ios::binary);
        if (!input) {
            cout <<argv[1] <<": File not found. Creating a new file." << endl;
        } else if (!item.ParseFromIstream(&input)) {
            cerr << "Failed to parse item" << endl;
            return -1;
        }
    }

    // Add an item.
    PromptForItemProperty(&item);
    PromptForItemRelation(&item);

    {
        // Write the new item back to disk.
        fstream output(argv[1], ios::out | ios::trunc | ios::binary);
        if (!item.SerializePartialToOstream(&output)) {
            cerr << "Failed to write item." << endl;
            return -1;
        }
    }

    // Optional : Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}

#endif  //ITEM_WRITE_H
