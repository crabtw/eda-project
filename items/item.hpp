#ifndef ITEM_HPP
#define ITEM_HPP

#include <boost/shared_ptr.hpp>

#include <list>
#include <string>

struct item;
typedef boost::shared_ptr<item> item_ptr;
typedef std::list<item_ptr> item_list;

struct item {
    item(): value(-1) { }

    virtual void eval() = 0;

    std::string id;
    int value;

    item_list input;
    item_list output;

protected:
    template <class Function>
    int op(Function f) {
        item_list::iterator iter = input.begin();

        int val = (*iter)->value;
        for(; iter != input.end(); ++iter) {
            val = f(val, (*iter)->value);
        }

        return val;
    }
};

#endif
