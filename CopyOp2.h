#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geometry>
#include <osg/Image>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Notify>
#include <osg/Texture>
#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>
#include <iostream>

// 自定义copy类，用于输出拷贝信息
class GraphCopyOp :public osg::CopyOp
{
public:
	inline GraphCopyOp(CopyFlags flags = SHALLOW_COPY) :osg::CopyOp(flags)
	{
		_nodeCopyMap.clear();
	}
	// 节点的copy
	virtual osg::Node* operator()(const osg::Node* node)const
	{
		// 判断是否为深拷贝
		if (node && _flags & DEEP_COPY_NODES)
		{
			// 判断节点的父节点是否有多个，如果只有一个，则直接深拷贝
			if (node->getNumParents() > 1)
			{
				// 判断是否已经拷贝
				if (_nodeCopyMap.find(node) != _nodeCopyMap.end())
				{
					std::cout << "Copy of node" << node << " " <<
						node->getName() << "," << _nodeCopyMap[node] << ",will be reused"
						<< std::endl;
				}
				else
				{
					// 进行拷贝并在映射表中保存拷贝对象
					osg::Node* newNode = dynamic_cast<osg::Node*>(node->clone(*this));
					_nodeCopyMap[node] = newNode;
					// 返回地址
					return newNode;
				}
			}

			else
			{
				return dynamic_cast<osg::Node*>(node->clone(*this));
			}
		}
	}

protected:
	// 节点映射表，用来保护child和拷贝，分别作为原象和象
	mutable std::map<const osg::Node*, osg::Node*> _nodeCopyMap;
};