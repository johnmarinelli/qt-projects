#include "tilesheethandler.h"

TileSheetHandler::TileSheetHandler()
{
}

void TileSheetHandler::add(const std::string& path, const QSize& tileSize)
{
    if(!get(path)) {
        std::shared_ptr<TileSheet> ts =
            std::make_shared<TileSheet>(QString(path.c_str()), tileSize);

        mTileSheets[path] = ts;
    }
}

std::shared_ptr<TileSheet> TileSheetHandler::get(const std::string& key)
{
    auto ts = mTileSheets.find(key);
    if(ts != mTileSheets.end()) {
        return ts->second;
    }
    else return nullptr;
}

bool TileSheetHandler::remove(const std::string& path)
{
    auto ts = mTileSheets.find(path);
    if(ts != mTileSheets.end()) {
        mTileSheets.erase(ts);
        return true;
    }
    else return false;
}
