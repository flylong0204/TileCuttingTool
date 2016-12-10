#include "TileKey.h"
#include <sstream>

using namespace rxtiler;


//rxtiler::TileKey::TileKey()
//{
//
//}

//rxtiler::TileKey rxtiler::TileKey::createChild( int x,int y )
//{
//	TileKey key;
//	key.x = this->x * 2 + x;
//	key.y = this->y * 2 + y;
//	key.lod = this->lod  +1;
//	return key;
//}


std::string TileKey::str(){
    std::stringstream ss;
    ss << "lod:";
    ss << this->lod;
    ss << " x:";
    ss << this->x;
    ss << " y:";
    ss << this->y;
    return ss.str();

}
