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

// �Զ���copy�࣬�������������Ϣ
class GraphCopyOp :public osg::CopyOp
{
public:
	inline GraphCopyOp(CopyFlags flags = SHALLOW_COPY) :osg::CopyOp(flags)
	{
		_nodeCopyMap.clear();
	}
	// �ڵ��copy
	virtual osg::Node* operator()(const osg::Node* node)const
	{
		// �ж��Ƿ�Ϊ���
		if (node && _flags & DEEP_COPY_NODES)
		{
			// �жϽڵ�ĸ��ڵ��Ƿ��ж�������ֻ��һ������ֱ�����
			if (node->getNumParents() > 1)
			{
				// �ж��Ƿ��Ѿ�����
				if (_nodeCopyMap.find(node) != _nodeCopyMap.end())
				{
					std::cout << "Copy of node" << node << " " <<
						node->getName() << "," << _nodeCopyMap[node] << ",will be reused"
						<< std::endl;
				}
				else
				{
					// ���п�������ӳ����б��濽������
					osg::Node* newNode = dynamic_cast<osg::Node*>(node->clone(*this));
					_nodeCopyMap[node] = newNode;
					// ���ص�ַ
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
	// �ڵ�ӳ�����������child�Ϳ������ֱ���Ϊԭ�����
	mutable std::map<const osg::Node*, osg::Node*> _nodeCopyMap;
};