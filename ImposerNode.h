#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgSim/Impostor>
#include <osgUtil/Optimizer>

void TestImpostor()
{
	// ����Viewer���󣬳��������
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	osg::ref_ptr<osg::Group> root = new osg::Group();

	// ����һ���ڵ㣬��ȡţģ��
	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("cow.osg");

	// ����һ������ڵ�
	osg::ref_ptr<osgSim::Impostor> imposter = new osgSim::Impostor();
	// ����50.0f�Ժ�ʼʹ����ͼ
	imposter->setImpostorThreshold(50.0f);
	// ����ģ����ʾ��Χ��0~10000��
	imposter->addChild(node1.get(), 0, 10000.0f);

	// ��ӵ�����
	root->addChild(imposter.get());

	// �Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();
}