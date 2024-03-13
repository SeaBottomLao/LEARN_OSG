#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

osg::ref_ptr<osg::Geode> createShape()
{
	// 创建一个叶节点
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	// 设置半径和高度
	float radius = 0.8f;
	float height = 1.0f;

	// 创建精细度对象，精细度越高，细分就越多
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	// 设置精细度为0.5f
	hints->setDetailRatio(0.5f);

	// 添加一个球体，第一个参数是预定几何体对象，第二个是精细度
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), radius), hints));

	// 添加一个正方体
	geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(2.0f, 0.0f, 0.0f), 2 * radius), hints));
	// 添加一个圆锥
	geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(4.0f, 0.0f, 0.0f), radius, height), hints));

	// 添加一个太空舱
	geode->addDrawable(new osg::ShapeDrawable(new osg::Capsule(osg::Vec3(8.0f, 0.0f, 0.0f), radius, height)));

	return geode.get();
}

int TestCreateShape()
{
	// 创还能Viewer对象，尝尽浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 添加到场景
	root->addChild(createShape());
	// 优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());

	return viewer->run();
}