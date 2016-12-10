#ifndef RE_TILEKEY
#define RE_TILEKEY 1

#include <string>

//using namespace rx;
namespace rxtiler{
	//一个TileKey确定一个瓦片
class TileKey
{
public:
	inline TileKey():x(0),y(0),lod(0){}
	inline TileKey(unsigned int vx,unsigned int vy,unsigned int vz):x(vx),y(vy),lod(vz){}
	inline bool operator == (TileKey& key)
	{
		return this->lod == key.lod && x == key.x && y == key.y;
	}
	//创建一个子节点 pos为0,1,2,3之一
	inline TileKey createChild(int pos)
	{
		return createChild(pos / 2,pos % 2);
	}
	//创建一个子节点
	inline TileKey createChild(int x,int y)
	{
		TileKey key;
		key.x = this->x * 2 + x;
		key.y = this->y * 2 + y;
		key.lod = this->lod  +1;
		return key;
	}

    std::string str();

public:
    int lod;
    int x;
    int y;
};

}
#endif
