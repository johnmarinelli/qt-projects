#ifndef TILESHEETHANDLER_H
#define TILESHEETHANDLER_H

#include <memory>
#include <map>
#include "tilesheet.h"

/*
 * Uncopyable class to create, retrieve, and delete TileSheets
 */
class TileSheetHandler
{
private:
    typedef std::pair<std::string, std::shared_ptr<TileSheet>> TileSheetHandlerPair;

    std::map<std::string, std::shared_ptr<TileSheet>> mTileSheets;

public:
    TileSheetHandler();
    TileSheetHandler(const TileSheetHandler&) = delete;
    TileSheetHandler& operator=(const TileSheetHandler&) = delete;

    void add(const std::string& path, const QSize& tileSize);
    std::shared_ptr<TileSheet> get(const std::string& key);
    bool remove(const std::string& path);

};

#endif // TILESHEETHANDLER_H
