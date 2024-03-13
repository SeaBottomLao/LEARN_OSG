#ifndef WORD_COORDINATE_H
#define WORD_COORDINATE_H

#include <osgViewer/Viewer>
#include <iostream>
#include <osg/NodeVisitor>
#include <osg/Matrix>
// �÷��������ڷ���ĳ���ڵ����������
// �����ڵ㿪ʼ����ڵ���������������Ľڵ��¼��nodePath��
// ��һ�ε�����ڵ�󣬼�¼��ʼ�㵽���ڵ�Ľڵ�·��
// ��������������֮�󣬿��Ի�ýڵ����������
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
			// ��������
			traverse(node);
		}
	}

	// ���������������
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
		// ����������
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

	// ��õ�ǰ��ͶӰ�����ģ����ͼ����
	osg::Matrix projectMatrix = view->getCamera()->getProjectionMatrix();
	osg::Matrix viewprojectMatrix = view->getCamera()->getViewMatrix();

	// �仯ģ����ͼ����
	double modelViewMatrix[16];
	memcpy(modelViewMatrix, viewprojectMatrix.ptr(), sizeof(GLdouble) * 16);
	Transform_Point(out, modelViewMatrix, in);

	// �任ͶӰ����
	double myprojectMatrix[16];
	memcpy(myprojectMatrix, projectMatrix.ptr(), sizeof(GLdouble) * 16);
	Transform_Point(in, myprojectMatrix, out);

	// �任�ӿڱ任����
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

	// �����ά��ĻͶӰ��
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
