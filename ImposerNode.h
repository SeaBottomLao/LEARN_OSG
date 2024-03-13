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
	// 创建Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 创建一个节点，读取牛模型
	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("cow.osg");

	// 创建一个替代节点
	osg::ref_ptr<osgSim::Impostor> imposter = new osgSim::Impostor();
	// 设置50.0f以后开始使用贴图
	imposter->setImpostorThreshold(50.0f);
	// 设置模型显示范围在0~10000内
	imposter->addChild(node1.get(), 0, 10000.0f);

	// 添加到场景
	root->addChild(imposter.get());

	// 优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();
}