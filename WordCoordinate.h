#ifndef WORD_COORDINATE_H
#define WORD_COORDINATE_H

#include <osgViewer/Viewer>
#include <iostream>
#include <osg/NodeVisitor>
#include <osg/Matrix>
// 该访问类用于返回某个节点的世界坐标
// 从起点节点开始向根节点遍历，并将遍历的节点纪录到nodePath中
// 第一次到达根节点后，纪录起始点到根节点的节点路径
// 获得世界坐标矩阵之后，可以获得节点的世界坐标
class GetWorldCoordinateOfNodeVisitor :public osg::NodeVisitor
{
public:
	GetWorldCoordinateOfNodeVisitor() :osg::NodeVisitor(NodeVisitor::TRAVERSE_PARENTS), done(false)
	{
		wcMatrix = new osg::Matrix;
	}

	virtual void apply(osg::Node& node)
	{
		if (!done)
		{
			if (0 == node.getNumParents())
			{
				wcMatrix->set(osg::computeLocalToWorld(this->getNodePath()));
				done = true;
			}
			// 继续遍历
			traverse(node);
		}
	}

	// 返回世界坐标矩阵
	osg::Matrix* giveUpDaMat()
	{
		return wcMatrix;
	}
private:
	bool done;
	osg::Matrix* wcMatrix;
};



osg::Matrixd* getWorldCoords(osg::Node* node)
{
	GetWorldCoordinateOfNodeVisitor* nev = new GetWorldCoordinateOfNodeVisitor;

	if (node && nev)
	{
		// 启动访问器
		node->accept(*nev);
		 
		return nev->giveUpDaMat();
	}

	else
	{
		return NULL;
	}
}

osg::Vec3d WorldToScreen(osgViewer::View* view, osg::Vec3 worldPoint)
{
	double in[4], out[4];

	in[0] = worldPoint._v[0];
	in[1] = worldPoint._v[1];
	in[2] = worldPoint._v[2];
	in[3] = worldPoint._v[3];

	// 获得当前的投影矩阵和模型视图矩阵
	osg::Matrix projectMatrix = view->getCamera()->getProjectionMatrix();
	osg::Matrix viewprojectMatrix = view->getCamera()->getViewMatrix();

	// 变化模型视图矩阵
	double modelViewMatrix[16];
	memcpy(modelViewMatrix, viewprojectMatrix.ptr(), sizeof(GLdouble) * 16);
	Transform_Point(out, modelViewMatrix, in);

	// 变换投影矩阵
	double myprojectMatrix[16];
	memcpy(myprojectMatrix, projectMatrix.ptr(), sizeof(GLdouble) * 16);
	Transform_Point(in, myprojectMatrix, out);

	// 变换视口变换矩阵
	if (in[3] == 0.0)
		return osg::Vec3d(0, 0, 0);
	in[0] /= in[3];
	in[1] /= in[3];
	in[2] /= in[3];

	int viewPort[4];
	osg::Viewport* myViewPort = view->getCamera()->getViewport();
	viewPort[0] = myViewPort->x();
	viewPort[1] = myViewPort->y();
	viewPort[2] = myViewPort->width();
	viewPort[3] = myViewPort->height();

	// 计算二维屏幕投影点
	osg::Vec3d screenPoint;
	screenPoint._v[0] = (int)(viewPort[0] + (1 + in[0]) * viewPort[2] / 2 + 0.5);
	screenPoint._v[1] = (int)(viewPort[1] + (1 + in[0]) * viewPort[3] / 2 + 0.5);
	screenPoint._v[2] = 0;

	return screenPoint;
}

void Transform_Point(double out[4], double m[6], const double in[4])
{
#define M(row,col) m[col *4 +row]
	out[0] = M(0, 0) * in[0] + M(0, 1) * in[1] + M(0, 2) * in[2] + M(0, 3) * in[3];
	out[1] = M(1, 0) * in[1] + M(1, 1) * in[1] + M(1, 2) * in[2] + M(1, 3) * in[3];
	out[2] = M(2, 0) * in[2] + M(2, 1) * in[1] + M(2, 2) * in[2] + M(2, 3) * in[3];
	out[3] = M(3, 0) * in[0] + M(3, 1) * in[1] + M(3, 2) * in[2] + M(3, 3) * in[3];

#undef M
}
#endif // !WORD_COORDINATE_H
