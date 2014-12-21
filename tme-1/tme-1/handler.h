#ifndef HANDLER_H
#define HANDLER_H

#include <map>

template <typename Key, typename Value>
class Handler
{
private:
    std::map<Key, Value> mItems;

public:
    Handler();

    virtual ~Handler();
};

#endif // HANDLER_H
