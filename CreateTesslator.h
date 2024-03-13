#include "stadfx.h"

// 使用分隔化绘制凹多边形
osg::ref_ptr<osg::Geode> tesslatorGeometry()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	geode->addDrawable(geom.get());

	// 以下是一些顶点数据
	// 墙
	const float wall[5][3] =
	{
		{2200.0f,0.0f,1130.0f},
		{2600.0f,0.0f,1130.0f},
		{2600.0f,0.0f,1340.0f},
		{2400.0f,0.0f,1440.0f},
		{2200.0f,0.0f,1340.0f}
	};

	// 设置顶点数据
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array();
	geom->setVertexArray(coords);

	// 设置法线
	osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array();
	normal->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	geom->setNormalArray(normal.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	// 添加墙
	for (int i = 0; i < 5; i++)
	{
		coords->push_back(osg::Vec3(wall[i][0], wall[i][1], wall[i][2]));
	}

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POLYGON, 0, 5));

	// 创建分格化对象
	osg::ref_ptr<osgUtil::Tessellator> tscx = new osgUtil::Tessellator();
	// 设置分格类型为几何体
	tscx->setTessellationType(osgUtil::Tessellator::TESS_TYPE_GEOMETRY);
	// 设置不仅仅显示轮廓线
	tscx->setBoundaryOnly(false);
	// 设置环绕规则
	tscx->setWindingType(osgUtil::Tessellator::TESS_WINDING_ODD);

	// 使用分格化
	tscx->retessellatePolygons(*geom.get());


	return geode.get();
}

int TestCreateTesslator()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 添加绘制的多边形
	osg::ref_ptr<osg::Geode> geode = tesslatorGeometry();
	root->addChild(geode.get());

	// 优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());

	return viewer->run();
}