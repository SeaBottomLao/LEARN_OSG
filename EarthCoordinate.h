#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/CoordinateSystemNode>
#include <osg/ShapeDrawable>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

// 绘制一个地球
osg::ref_ptr<osg::Node> createEarth()
{
	// 创建一个球体
	osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0, 0.0, 0.0), osg::WGS_84_RADIUS_POLAR));

	// 添加到叶节点
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(sd.get());

	// 设置纹理
	std::string filename("land_shallow_topo_2048.jpg");
	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::Texture2D(osgDB::readImageFile(filename)));

	// 创建坐标系节点
	osg::ref_ptr<osg::CoordinateSystemNode> csn = new osg::CoordinateSystemNode;
	// 设置椭圆体模型，默认的坐标系WGS_84
	csn->setEllipsoidModel(new osg::EllipsoidModel());
	// 添加子节点
	csn->addChild(geode.get());

	return csn.get();
}

void TestEarthCoordinate()
{
	// 创建Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 添加到场景
	root->addChild(createEarth());
	// 优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());
	viewer->realize();

	viewer->run();

	return;
}