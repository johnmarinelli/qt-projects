#include "tilesheethandler.h"

unsigned short TileSheetHandler::IDCounter = 0;

TileSheetHandler::TileSheetHandler()
{
}

/*
 * returns a handle to the created TileSheet
 */
unsigned short TileSheetHandler::add(const std::string& path, const QSize& tileSize)
{
    std::shared_ptr<TileSheet> ts =
        std::make_shared<TileSheet>(QString(path.c_str()), tileSize);

    auto id = IDCounter++;
    mTileSheets[id] = ts;

    return id;
}

std::shared_ptr<TileSheet> TileSheetHandler::get(unsigned short key) const
{
    auto ts = mTileSheets.find(key);
    if(ts != mTileSheets.end()) {
        return ts->second;
    }
    else return nullptr;
}

bool TileSheetHandler::remove(unsigned short key)
{
    auto ts = mTileSheets.find(key);
    if(ts != mTileSheets.end()) {
        mTileSheets.erase(ts);
        return true;
    }
    else return false;
}
